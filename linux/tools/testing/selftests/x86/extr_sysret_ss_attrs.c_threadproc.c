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

__attribute__((used)) static void *threadproc(void *ctx)
{
	/*
	 * Do our best to cause sleeps on this CPU to exit the kernel and
	 * re-enter with SS = 0.
	 */
	while (true)
		;

	return NULL;
}