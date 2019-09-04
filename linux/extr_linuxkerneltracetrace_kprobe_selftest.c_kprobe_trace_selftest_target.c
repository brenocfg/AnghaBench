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

int kprobe_trace_selftest_target(int a1, int a2, int a3, int a4, int a5, int a6)
{
	return a1 + a2 + a3 + a4 + a5 + a6;
}