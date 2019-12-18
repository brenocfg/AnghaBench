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
 int ossl_trace_get_category (int) ; 
 TYPE_1__* trace_channels ; 

int OSSL_trace_enabled(int category)
{
    int ret = 0;
#ifndef OPENSSL_NO_TRACE
    category = ossl_trace_get_category(category);
    if (category >= 0)
        ret = trace_channels[category].bio != NULL;
#endif
    return ret;
}