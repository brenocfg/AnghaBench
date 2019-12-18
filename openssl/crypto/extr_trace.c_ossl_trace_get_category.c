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
struct TYPE_2__ {int /*<<< orphan*/ * bio; } ;

/* Variables and functions */
 int OSSL_TRACE_CATEGORY_ALL ; 
 int OSSL_TRACE_CATEGORY_NUM ; 
 TYPE_1__* trace_channels ; 

__attribute__((used)) static int ossl_trace_get_category(int category)
{
    if (category < 0 || category >= OSSL_TRACE_CATEGORY_NUM)
        return -1;
    if (trace_channels[category].bio != NULL)
        return category;
    return OSSL_TRACE_CATEGORY_ALL;
}