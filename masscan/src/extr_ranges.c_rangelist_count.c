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
typedef  scalar_t__ uint64_t ;
struct RangeList {unsigned int count; TYPE_1__* list; } ;
struct TYPE_2__ {scalar_t__ begin; scalar_t__ end; } ;

/* Variables and functions */

uint64_t
rangelist_count(const struct RangeList *targets)
{
    unsigned i;
    uint64_t result = 0;

    for (i=0; i<targets->count; i++) {
        result += (uint64_t)targets->list[i].end - (uint64_t)targets->list[i].begin + 1UL;
    }

    return result;
}