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
 int /*<<< orphan*/  LOCKDEP_NOW_UNRELIABLE ; 
 int /*<<< orphan*/  TAINT_BAD_PAGE ; 
 int /*<<< orphan*/  add_taint (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kasan_enable_current () ; 
 int /*<<< orphan*/  panic (char*) ; 
 scalar_t__ panic_on_warn ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  report_lock ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void end_report(unsigned long *flags)
{
	pr_err("==================================================================\n");
	add_taint(TAINT_BAD_PAGE, LOCKDEP_NOW_UNRELIABLE);
	spin_unlock_irqrestore(&report_lock, *flags);
	if (panic_on_warn)
		panic("panic_on_warn set ...\n");
	kasan_enable_current();
}