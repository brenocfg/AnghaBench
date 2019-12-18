#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct RangeList {unsigned int count; int is_sorted; TYPE_1__* list; int /*<<< orphan*/  member_0; } ;
struct TYPE_3__ {int /*<<< orphan*/  end; int /*<<< orphan*/  begin; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG (int,char*,...) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  qsort (TYPE_1__*,unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  range_compare ; 
 int /*<<< orphan*/  rangelist_add_range (struct RangeList*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
rangelist_sort(struct RangeList *targets)
{
    size_t i;
    struct RangeList newlist = {0};
    unsigned original_count = targets->count;

    /* Empty lists are, of course, sorted. We need to set this
     * to avoid an error later on in the code which asserts that
     * the lists are sorted */
    if (targets->count == 0) {
        targets->is_sorted = 1;
        return;
    }
    
    /* If it's already sorted, then skip this */
    if (targets->is_sorted) {
        return;
    }
    
    
    /* First, sort the list */
    LOG(3, "[+] range:sort: sorting...\n");
    qsort(  targets->list,              /* the array to sort */
            targets->count,             /* number of elements to sort */
            sizeof(targets->list[0]),   /* size of element */
            range_compare);
    
    
    /* Second, combine all overlapping ranges. We do this by simply creating
     * a new list from a sorted list, so we don't have to remove things in the
     * middle when collapsing overlapping entries together, which is painfully
     * slow. */
    LOG(3, "[+] range:sort: combining...\n");
    for (i=0; i<targets->count; i++) {
        rangelist_add_range(&newlist, targets->list[i].begin, targets->list[i].end);
    }
    
    LOG(3, "[+] range:sort: combined from %u elements to %u elements\n", original_count, newlist.count);
    free(targets->list);
    targets->list = newlist.list;
    targets->count = newlist.count;
    newlist.list = 0;

    LOG(2, "[+] range:sort: done...\n");

    targets->is_sorted = 1;
}