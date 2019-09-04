#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct RangeList {unsigned int count; TYPE_1__* list; } ;
struct TYPE_2__ {int /*<<< orphan*/  end; int /*<<< orphan*/  begin; } ;

/* Variables and functions */
 int /*<<< orphan*/  rangelist_add_range (struct RangeList*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rangelist_sort (struct RangeList*) ; 

void
rangelist_merge(struct RangeList *list1, const struct RangeList *list2)
{
    unsigned i;
    
    for (i=0; i<list2->count; i++) {
        rangelist_add_range(list1, list2->list[i].begin, list2->list[i].end);
    }
    rangelist_sort(list1);
}