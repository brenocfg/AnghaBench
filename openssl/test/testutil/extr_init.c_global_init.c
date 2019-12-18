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
 int /*<<< orphan*/  getenv (char*) ; 
 int /*<<< orphan*/  setup_trace (int /*<<< orphan*/ ) ; 

int global_init(void)
{
#ifndef OPENSSL_NO_TRACE
    setup_trace(getenv("OPENSSL_TRACE"));
#endif

    return 1;
}