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
struct RangeList {size_t count; int is_sorted; int /*<<< orphan*/ * list; } ;

/* Variables and functions */
 int /*<<< orphan*/  qsort (int /*<<< orphan*/ *,size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  range_combine (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  range_compare ; 
 scalar_t__ range_is_overlap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rangelist_remove_at (struct RangeList*,size_t) ; 

void
rangelist_sort(struct RangeList *targets)
{
    size_t i;

    if (targets->count == 0)
        return;

    /* First, sort the list */
    qsort(  targets->list,              /* the array to sort */
            targets->count,             /* number of elements to sort */
            sizeof(targets->list[0]),   /* size of element */
            range_compare);

    /* Second, combine all overlapping ranges*/
    for (i=0; i<targets->count; i++) {
        while (i+1<targets->count && range_is_overlap(targets->list[i], targets->list[i+1])) {
            range_combine(&targets->list[i], targets->list[i+1]);
            rangelist_remove_at(targets, i+1);
        }
    }

    targets->is_sorted = 1;
}