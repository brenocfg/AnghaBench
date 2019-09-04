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
struct pt_regs {unsigned long* uregs; int ARM_pc; } ;

/* Variables and functions */
 unsigned long instruction_pointer (struct pt_regs*) ; 

__attribute__((used)) static int imx6q_pcie_abort_handler(unsigned long addr,
		unsigned int fsr, struct pt_regs *regs)
{
	unsigned long pc = instruction_pointer(regs);
	unsigned long instr = *(unsigned long *)pc;
	int reg = (instr >> 12) & 15;

	/*
	 * If the instruction being executed was a read,
	 * make it look like it read all-ones.
	 */
	if ((instr & 0x0c100000) == 0x04100000) {
		unsigned long val;

		if (instr & 0x00400000)
			val = 255;
		else
			val = -1;

		regs->uregs[reg] = val;
		regs->ARM_pc += 4;
		return 0;
	}

	if ((instr & 0x0e100090) == 0x00100090) {
		regs->uregs[reg] = -1;
		regs->ARM_pc += 4;
		return 0;
	}

	return 1;
}