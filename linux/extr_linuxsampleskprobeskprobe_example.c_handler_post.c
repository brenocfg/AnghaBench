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
struct kprobe {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void handler_post(struct kprobe *p, struct pt_regs *regs,
				unsigned long flags)
{
#ifdef CONFIG_X86
	pr_info("<%s> post_handler: p->addr = 0x%p, flags = 0x%lx\n",
		p->symbol_name, p->addr, regs->flags);
#endif
#ifdef CONFIG_PPC
	pr_info("<%s> post_handler: p->addr = 0x%p, msr = 0x%lx\n",
		p->symbol_name, p->addr, regs->msr);
#endif
#ifdef CONFIG_MIPS
	pr_info("<%s> post_handler: p->addr = 0x%p, status = 0x%lx\n",
		p->symbol_name, p->addr, regs->cp0_status);
#endif
#ifdef CONFIG_ARM64
	pr_info("<%s> post_handler: p->addr = 0x%p, pstate = 0x%lx\n",
		p->symbol_name, p->addr, (long)regs->pstate);
#endif
#ifdef CONFIG_S390
	pr_info("<%s> pre_handler: p->addr, 0x%p, flags = 0x%lx\n",
		p->symbol_name, p->addr, regs->flags);
#endif
}