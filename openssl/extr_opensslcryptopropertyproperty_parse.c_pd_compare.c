#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ name_idx; } ;
typedef  TYPE_1__ PROPERTY_DEFINITION ;

/* Variables and functions */

__attribute__((used)) static int pd_compare(const PROPERTY_DEFINITION *const *p1,
                      const PROPERTY_DEFINITION *const *p2)
{
    const PROPERTY_DEFINITION *pd1 = *p1;
    const PROPERTY_DEFINITION *pd2 = *p2;

    if (pd1->name_idx < pd2->name_idx)
        return -1;
    if (pd1->name_idx > pd2->name_idx)
        return 1;
    return 0;
}