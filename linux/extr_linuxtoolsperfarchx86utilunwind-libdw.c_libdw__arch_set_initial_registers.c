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
struct unwind_info {TYPE_1__* sample; } ;
struct regs_dump {scalar_t__ abi; } ;
struct TYPE_2__ {struct regs_dump user_regs; } ;
typedef  int /*<<< orphan*/  Dwfl_Thread ;
typedef  int /*<<< orphan*/  Dwarf_Word ;

/* Variables and functions */
 int /*<<< orphan*/  PERF_REG_X86_AX ; 
 int /*<<< orphan*/  PERF_REG_X86_BP ; 
 int /*<<< orphan*/  PERF_REG_X86_BX ; 
 int /*<<< orphan*/  PERF_REG_X86_CX ; 
 int /*<<< orphan*/  PERF_REG_X86_DI ; 
 int /*<<< orphan*/  PERF_REG_X86_DX ; 
 int /*<<< orphan*/  PERF_REG_X86_IP ; 
 int /*<<< orphan*/  PERF_REG_X86_R10 ; 
 int /*<<< orphan*/  PERF_REG_X86_R11 ; 
 int /*<<< orphan*/  PERF_REG_X86_R12 ; 
 int /*<<< orphan*/  PERF_REG_X86_R13 ; 
 int /*<<< orphan*/  PERF_REG_X86_R14 ; 
 int /*<<< orphan*/  PERF_REG_X86_R15 ; 
 int /*<<< orphan*/  PERF_REG_X86_R8 ; 
 int /*<<< orphan*/  PERF_REG_X86_R9 ; 
 int /*<<< orphan*/  PERF_REG_X86_SI ; 
 int /*<<< orphan*/  PERF_REG_X86_SP ; 
 scalar_t__ PERF_SAMPLE_REGS_ABI_32 ; 
 int dwfl_thread_state_registers (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perf_reg_value (int /*<<< orphan*/ *,struct regs_dump*,int /*<<< orphan*/ ) ; 

bool libdw__arch_set_initial_registers(Dwfl_Thread *thread, void *arg)
{
	struct unwind_info *ui = arg;
	struct regs_dump *user_regs = &ui->sample->user_regs;
	Dwarf_Word dwarf_regs[17];
	unsigned nregs;

#define REG(r) ({						\
	Dwarf_Word val = 0;					\
	perf_reg_value(&val, user_regs, PERF_REG_X86_##r);	\
	val;							\
})

	if (user_regs->abi == PERF_SAMPLE_REGS_ABI_32) {
		dwarf_regs[0] = REG(AX);
		dwarf_regs[1] = REG(CX);
		dwarf_regs[2] = REG(DX);
		dwarf_regs[3] = REG(BX);
		dwarf_regs[4] = REG(SP);
		dwarf_regs[5] = REG(BP);
		dwarf_regs[6] = REG(SI);
		dwarf_regs[7] = REG(DI);
		dwarf_regs[8] = REG(IP);
		nregs = 9;
	} else {
		dwarf_regs[0]  = REG(AX);
		dwarf_regs[1]  = REG(DX);
		dwarf_regs[2]  = REG(CX);
		dwarf_regs[3]  = REG(BX);
		dwarf_regs[4]  = REG(SI);
		dwarf_regs[5]  = REG(DI);
		dwarf_regs[6]  = REG(BP);
		dwarf_regs[7]  = REG(SP);
		dwarf_regs[8]  = REG(R8);
		dwarf_regs[9]  = REG(R9);
		dwarf_regs[10] = REG(R10);
		dwarf_regs[11] = REG(R11);
		dwarf_regs[12] = REG(R12);
		dwarf_regs[13] = REG(R13);
		dwarf_regs[14] = REG(R14);
		dwarf_regs[15] = REG(R15);
		dwarf_regs[16] = REG(IP);
		nregs = 17;
	}

	return dwfl_thread_state_registers(thread, 0, nregs, dwarf_regs);
}