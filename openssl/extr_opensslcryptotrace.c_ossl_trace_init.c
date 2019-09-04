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
 int /*<<< orphan*/ * CRYPTO_THREAD_lock_new () ; 
 int /*<<< orphan*/ * trace_lock ; 

int ossl_trace_init(void)
{
#ifndef OPENSSL_NO_TRACE
    trace_lock = CRYPTO_THREAD_lock_new();
    if (trace_lock == NULL)
        return 0;
#endif

    return 1;
}