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

__attribute__((used)) static void the_hook(void *_hook_flags)
{
	int *hook_flags = _hook_flags;
	int *p = NULL;

	*hook_flags = 1234;

	/* Generate a segfault, test perf_hooks__recover */
	*p = 0;
}