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

/* Variables and functions */
 int OSSL_TRACE_CATEGORY_NUM ; 
 int set_trace_data (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_attach_cb ; 
 int /*<<< orphan*/  trace_detach_cb ; 

int OSSL_trace_set_suffix(int category, const char *suffix)
{
#ifndef OPENSSL_NO_TRACE
    if (category >= 0 && category < OSSL_TRACE_CATEGORY_NUM)
        return set_trace_data(category, 0, NULL, NULL, &suffix,
                              trace_attach_cb, trace_detach_cb);
#endif
    return 0;
}