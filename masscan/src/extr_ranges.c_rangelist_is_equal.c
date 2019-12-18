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
struct TYPE_2__ {scalar_t__ begin; scalar_t__ end; } ;

/* Variables and functions */

__attribute__((used)) static bool
rangelist_is_equal(const struct RangeList *lhs, const struct RangeList *rhs)
{
    unsigned i;
    
    if (lhs->count != rhs->count)
        return false;
    for (i=0; i<lhs->count; i++) {
        if (lhs->list[i].begin != rhs->list[i].begin) {
            return false;
        }
        if (lhs->list[i].end != rhs->list[i].end) {
            return false;
        }
    }
    
    return true;
}