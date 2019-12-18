#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct RangeList {int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int lcgrand (unsigned int*) ; 
 int /*<<< orphan*/  rangelist_add_range (struct RangeList*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  rangelist_copy (struct RangeList*,struct RangeList*) ; 
 int /*<<< orphan*/  rangelist_exclude (struct RangeList*,struct RangeList*) ; 
 int /*<<< orphan*/  rangelist_exclude2 (struct RangeList*,struct RangeList*) ; 
 int /*<<< orphan*/  rangelist_is_equal (struct RangeList*,struct RangeList*) ; 
 int /*<<< orphan*/  rangelist_sort (struct RangeList*) ; 

__attribute__((used)) static int
exclude_selftest(void)
{
    unsigned seed = 0;
    struct RangeList includes1 = {0};
    struct RangeList includes2 = {0};
    struct RangeList excludes = {0};
    unsigned addr = 0;
    size_t i;
    
    /* In my initial tests, simply using 10 as the count seems to
     * catch all the combinations. On the other hand, 100,000 takes
     * a long time to complete, because it's O(n2) quadratic time.
     * Therefore, I pick a thousand as a compromise, likely to catch
     * any possibility, yet fast enough to complete quickly even on
     * a Raspberry Pi */
    static const unsigned MAXCOUNT = 1000;
    
    /* Fill the include list. This is designed to make short ranges
     * that are a short distance apart. We'll do the same for the
     * same for the excludes, using a different random seed. This
     * should create two lists that have lots and lots of overlapping
     * and non-overlapping ranges.
     */
    seed = 0;
    addr = 0;
    for (i=0; i<MAXCOUNT; i++) {
        unsigned begin;
        unsigned end;
        
        addr += lcgrand(&seed) & 0xF;
        begin = addr;
        addr += lcgrand(&seed) & 0xF;
        end = addr;
        
        rangelist_add_range(&includes1, begin, end);
    }
    rangelist_sort(&includes1);
    
    /* Fill the exlcude list, using the same algorithm as above for
     * includes, but now with a different seed. This creates lots of
     * conflicts. */
    seed = 1;
    addr = 0;
    for (i=0; i<MAXCOUNT; i++) {
        unsigned begin;
        unsigned end;
        
        addr += lcgrand(&seed) & 0xF;
        begin = addr;
        addr += lcgrand(&seed) & 0xF;
        end = addr;
        
        rangelist_add_range(&excludes, begin, end);
    }
    rangelist_sort(&excludes);
    
    /* Now create a copy of the include list, because we want to
     * apply excludes using two different algorithms to see if the
     * results match */
    rangelist_copy(&includes2, &includes1);
    if (!rangelist_is_equal(&includes1, &includes2))
        return 1;

    
    /* Now apply the exclude alogirthms, both new and old, to the
     * the include lists. */
    rangelist_exclude(&includes1, &excludes);
    rangelist_exclude2(&includes2, &excludes);
    if (!rangelist_is_equal(&includes1, &includes2))
        return 1; /* fail */
    
    /* If we reach this point, the selftest has succeeded */
    return 0;

}