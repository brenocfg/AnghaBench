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
struct Range {unsigned int begin; unsigned int end; } ;

/* Variables and functions */

int
rangelist_is_contains(const struct RangeList *targets, unsigned number)
{
    unsigned i;
    for (i=0; i<targets->count; i++) {
        struct Range *range = &targets->list[i];

        if (range->begin <= number && number <= range->end)
            return 1;
    }
    return 0;
}