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
struct pt_regs {int dummy; } ;

/* Variables and functions */
 int CONSOLE_LOGLEVEL_MOTORMOUTH ; 
 int console_loglevel ; 
 int /*<<< orphan*/  kdb_printf (char*) ; 
 int /*<<< orphan*/  kdb_trap_printk ; 
 int /*<<< orphan*/  show_regs (struct pt_regs*) ; 

__attribute__((used)) static void kdb_dumpregs(struct pt_regs *regs)
{
	int old_lvl = console_loglevel;
	console_loglevel = CONSOLE_LOGLEVEL_MOTORMOUTH;
	kdb_trap_printk++;
	show_regs(regs);
	kdb_trap_printk--;
	kdb_printf("\n");
	console_loglevel = old_lvl;
}