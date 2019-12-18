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
struct RangeList {unsigned int count; struct Range* list; } ;
struct Range {int /*<<< orphan*/  end; int /*<<< orphan*/  begin; } ;

/* Variables and functions */
 int /*<<< orphan*/  rangelist_remove_range (struct RangeList*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rangelist_sort (struct RangeList*) ; 

__attribute__((used)) static void
rangelist_exclude2(  struct RangeList *targets,
                  const struct RangeList *excludes)
{
    unsigned i;
    
    for (i=0; i<excludes->count; i++) {
        struct Range range = excludes->list[i];
        rangelist_remove_range(targets, range.begin, range.end);
    }
    
    /* Since chopping up large ranges can split ranges, this can
     * grow the list so we need to re-sort it */
    rangelist_sort(targets);

}