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
 int /*<<< orphan*/  kasan_disable_current () ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  report_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void start_report(unsigned long *flags)
{
	/*
	 * Make sure we don't end up in loop.
	 */
	kasan_disable_current();
	spin_lock_irqsave(&report_lock, *flags);
	pr_err("==================================================================\n");
}