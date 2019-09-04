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
struct task_struct {int dummy; } ;

/* Variables and functions */
 int CONSOLE_LOGLEVEL_MOTORMOUTH ; 
 int console_loglevel ; 
 scalar_t__ kdb_current_regs ; 
 int /*<<< orphan*/  kdb_set_current_task (struct task_struct*) ; 
 int /*<<< orphan*/  kdb_trap_printk ; 
 int /*<<< orphan*/  show_stack (struct task_struct*,void*) ; 

__attribute__((used)) static void kdb_show_stack(struct task_struct *p, void *addr)
{
	int old_lvl = console_loglevel;
	console_loglevel = CONSOLE_LOGLEVEL_MOTORMOUTH;
	kdb_trap_printk++;
	kdb_set_current_task(p);
	if (addr) {
		show_stack((struct task_struct *)p, addr);
	} else if (kdb_current_regs) {
#ifdef CONFIG_X86
		show_stack(p, &kdb_current_regs->sp);
#else
		show_stack(p, NULL);
#endif
	} else {
		show_stack(p, NULL);
	}
	console_loglevel = old_lvl;
	kdb_trap_printk--;
}