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
 scalar_t__ current_perf_hook ; 
 int /*<<< orphan*/  jmpbuf ; 
 int /*<<< orphan*/  siglongjmp (int /*<<< orphan*/ ,int) ; 

void perf_hooks__recover(void)
{
	if (current_perf_hook)
		siglongjmp(jmpbuf, 1);
}