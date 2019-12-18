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
 int /*<<< orphan*/  dwfl_thread_getframes (void*,void*,int /*<<< orphan*/ *) ; 

int main(void)
{
	/*
	 * This function is guarded via: __nonnull_attribute__ (1, 2).
	 * Passing '1' as arguments value. This code is never executed,
	 * only compiled.
	 */
	dwfl_thread_getframes((void *) 1, (void *) 1, NULL);
	return 0;
}