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
struct pt_regs {int* uregs; int ARM_pc; } ;

/* Variables and functions */
 scalar_t__ instruction_pointer (struct pt_regs*) ; 

__attribute__((used)) static int keystone_pcie_fault(unsigned long addr, unsigned int fsr,
				struct pt_regs *regs)
{
	unsigned long instr = *(unsigned long *) instruction_pointer(regs);

	if ((instr & 0x0e100090) == 0x00100090) {
		int reg = (instr >> 12) & 15;

		regs->uregs[reg] = -1;
		regs->ARM_pc += 4;
	}

	return 0;
}