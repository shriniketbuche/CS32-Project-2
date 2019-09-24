#include <iostream>
#include<cassert>
#include<string>
#include "Sequence.h"
using namespace std;

#define CHECKTYPE(f, t) { auto p = static_cast<t>(f); (void)p; }

static_assert(std::is_default_constructible<Sequence>::value,
              "Sequence must be default-constructible.");
static_assert(std::is_copy_constructible<Sequence>::value,
              "Sequence must be copy-constructible.");
static_assert(std::is_copy_assignable<Sequence>::value,
              "Sequence must be assignable.");

void thisFunctionWillNeverBeCalled()
{
    CHECKTYPE(&Sequence::empty,      bool (Sequence::*)() const);
    CHECKTYPE(&Sequence::size,       int  (Sequence::*)() const);
    CHECKTYPE(&Sequence::insert,     int (Sequence::*)(int, const ItemType&));
    CHECKTYPE(&Sequence::insert,     int (Sequence::*)(const ItemType&));
    CHECKTYPE(&Sequence::erase,      bool (Sequence::*)(int));
    CHECKTYPE(&Sequence::remove,     int  (Sequence::*)(const ItemType&));
    CHECKTYPE(&Sequence::get,     bool (Sequence::*)(int, ItemType&) const);
    CHECKTYPE(&Sequence::set,     bool (Sequence::*)(int, const ItemType&));
    CHECKTYPE(&Sequence::find,       int  (Sequence::*)(const ItemType&) const);
    CHECKTYPE(&Sequence::swap,       void (Sequence::*)(Sequence&));
    CHECKTYPE(subsequence, int  (*)(const Sequence&, const Sequence&));
    CHECKTYPE(interleave,  void (*)(const Sequence&, const Sequence&, Sequence&));
}


int main()
{
    Sequence s;
    assert(s.insert(-6, "f") == -1);
    assert(s.insert(0, "a") == 0);
    s.insert(1, "b");
    s.insert(2, "c");
    s.insert(3, "b");
    s.insert(4, "e");
    assert(s.remove("b") == 2);
    assert(s.size() == 3);
    string x;
    s.insert("q");
    assert(s.get(0, x)  &&  x == "a");
    assert(s.get(1, x)  &&  x == "c");
    assert(s.get(2, x)  &&  x == "e");
    assert(s.get(3, x) && x == "q");
    assert(s.set(1, "f"));
    assert(!s.set(7, "X"));
    assert(!s.set(-1, "x"));
    assert(s.find("f") == 1);
    assert(!s.erase(-1));
    
    Sequence q;
    q.insert("bbb");
    assert(q.size() == 1);
    q.erase(0);
    assert(q.size() == 0);
    assert(!q.erase(0));
    
    s.swap(q);
    
    Sequence a;
    a.insert(0, "a");
    a.insert(1, "b");
    a.insert(2, "c");
    a.insert(3, "b");
    a.insert(4, "e");
    
    Sequence f = a;
    f = q;
    
    s.insert(0, "lalal");
    s.insert(1, "lalalalala");
    interleave(a, q, s);
    interleave(a, q, a);
    assert(!(a.erase(a.size())));
    assert(a.erase(a.size()-1));
    
    assert(subsequence(a, a) == 0);
    assert(subsequence(a, q) == -1);
    
    Sequence l;
    l.insert(0, "f");
    l.insert(1, "c");
    l.insert(2, "e");

    assert(subsequence(a, l) == 3);
    
    Sequence empty;
    Sequence testEmpty = empty;
    assert(testEmpty.empty());
    
    f = testEmpty;
    assert(f.empty());
    
    Sequence testResult;
    Sequence interleaveTest;
    interleaveTest.insert(0, "a");
    interleaveTest.insert(1, "b");
    interleaveTest.insert(2, "c");
    
    interleave(interleaveTest, testResult, testResult);
    interleave(interleaveTest, interleaveTest, testResult);
    assert(testResult.size() == 6);
    assert(subsequence(interleaveTest, f) == -1);
    
    Sequence testSwap;
    testSwap.insert(0, "f");
    testSwap.insert(1, "c");
    testSwap.insert(2, "e");
    testSwap.insert(1, "k");
    
    testSwap.swap(f);
    assert(testSwap.size() == 0);
    assert(testSwap.empty());
    assert(f.size() == 4);
    assert(!f.empty());
    
    
    f.insert("test");
    f.swap(testSwap);
    assert(testSwap.size() == 5);
    
    
    
    return 0;
    
}
