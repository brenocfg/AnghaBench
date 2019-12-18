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
 int /*<<< orphan*/  backtrace_tasklet ; 
 int /*<<< orphan*/  backtrace_work ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void backtrace_test_irq(void)
{
	pr_info("Testing a backtrace from irq context.\n");
	pr_info("The following trace is a kernel self test and not a bug!\n");

	init_completion(&backtrace_work);
	tasklet_schedule(&backtrace_tasklet);
	wait_for_completion(&backtrace_work);
}