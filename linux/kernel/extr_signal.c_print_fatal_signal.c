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
struct pt_regs {int ip; } ;

/* Variables and functions */
 scalar_t__ get_user (unsigned char,unsigned char*) ; 
 int /*<<< orphan*/  pr_cont (char*,...) ; 
 int /*<<< orphan*/  pr_info (char*,int) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int /*<<< orphan*/  show_regs (struct pt_regs*) ; 
 struct pt_regs* signal_pt_regs () ; 

__attribute__((used)) static void print_fatal_signal(int signr)
{
	struct pt_regs *regs = signal_pt_regs();
	pr_info("potentially unexpected fatal signal %d.\n", signr);

#if defined(__i386__) && !defined(__arch_um__)
	pr_info("code at %08lx: ", regs->ip);
	{
		int i;
		for (i = 0; i < 16; i++) {
			unsigned char insn;

			if (get_user(insn, (unsigned char *)(regs->ip + i)))
				break;
			pr_cont("%02x ", insn);
		}
	}
	pr_cont("\n");
#endif
	preempt_disable();
	show_regs(regs);
	preempt_enable();
}