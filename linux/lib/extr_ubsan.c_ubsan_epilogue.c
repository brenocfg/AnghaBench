#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  in_ubsan; } ;

/* Variables and functions */
 TYPE_1__* current ; 
 int /*<<< orphan*/  dump_stack () ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  report_lock ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void ubsan_epilogue(unsigned long *flags)
{
	dump_stack();
	pr_err("========================================"
		"========================================\n");
	spin_unlock_irqrestore(&report_lock, *flags);
	current->in_ubsan--;
}