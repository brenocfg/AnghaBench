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
 int /*<<< orphan*/  console_lock_dep_map ; 
 int /*<<< orphan*/  console_sem ; 
 int /*<<< orphan*/  mutex_release (int /*<<< orphan*/ *,int,unsigned long) ; 
 int /*<<< orphan*/  printk_safe_enter_irqsave (unsigned long) ; 
 int /*<<< orphan*/  printk_safe_exit_irqrestore (unsigned long) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __up_console_sem(unsigned long ip)
{
	unsigned long flags;

	mutex_release(&console_lock_dep_map, 1, ip);

	printk_safe_enter_irqsave(flags);
	up(&console_sem);
	printk_safe_exit_irqrestore(flags);
}