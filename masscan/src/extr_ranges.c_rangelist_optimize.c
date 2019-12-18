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
struct RangeList {size_t count; unsigned int* picker; int picker_mask; TYPE_1__* list; int /*<<< orphan*/  is_sorted; } ;
struct TYPE_2__ {scalar_t__ begin; scalar_t__ end; } ;

/* Variables and functions */
 unsigned int* REALLOCARRAY (int /*<<< orphan*/ *,size_t,int) ; 
 int /*<<< orphan*/  free (unsigned int*) ; 
 int /*<<< orphan*/  rangelist_sort (struct RangeList*) ; 

void
rangelist_optimize(struct RangeList *targets)
{
    unsigned *picker;
    unsigned i;
    unsigned total = 0;
    unsigned bit_count = 0;
    size_t count = targets->count;

    if (!targets->is_sorted)
        rangelist_sort(targets);

    if (targets->picker)
        free(targets->picker);

    picker = REALLOCARRAY(NULL, targets->count, sizeof(*picker));

    for (i=0; i<targets->count; i++) {
        picker[i] = total;
        total += targets->list[i].end - targets->list[i].begin + 1;
    }
    targets->picker = picker;


    for (;;) {
        count >>= 1;
        bit_count++;
        if (count == 0)
            break;
    }

    targets->picker_mask = (1 << bit_count) - 1;

    
}