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
struct regs_dump {int dummy; } ;
struct TYPE_2__ {struct regs_dump user_regs; } ;
typedef  int /*<<< orphan*/  Dwfl_Thread ;
typedef  int /*<<< orphan*/  Dwarf_Word ;

/* Variables and functions */
 int /*<<< orphan*/  PERF_REG_ARM64_LR ; 
 int PERF_REG_ARM64_MAX ; 
 int /*<<< orphan*/  PERF_REG_ARM64_PC ; 
 int /*<<< orphan*/  PERF_REG_ARM64_SP ; 
 int /*<<< orphan*/  PERF_REG_ARM64_X0 ; 
 int /*<<< orphan*/  PERF_REG_ARM64_X1 ; 
 int /*<<< orphan*/  PERF_REG_ARM64_X10 ; 
 int /*<<< orphan*/  PERF_REG_ARM64_X11 ; 
 int /*<<< orphan*/  PERF_REG_ARM64_X12 ; 
 int /*<<< orphan*/  PERF_REG_ARM64_X13 ; 
 int /*<<< orphan*/  PERF_REG_ARM64_X14 ; 
 int /*<<< orphan*/  PERF_REG_ARM64_X15 ; 
 int /*<<< orphan*/  PERF_REG_ARM64_X16 ; 
 int /*<<< orphan*/  PERF_REG_ARM64_X17 ; 
 int /*<<< orphan*/  PERF_REG_ARM64_X18 ; 
 int /*<<< orphan*/  PERF_REG_ARM64_X19 ; 
 int /*<<< orphan*/  PERF_REG_ARM64_X2 ; 
 int /*<<< orphan*/  PERF_REG_ARM64_X20 ; 
 int /*<<< orphan*/  PERF_REG_ARM64_X21 ; 
 int /*<<< orphan*/  PERF_REG_ARM64_X22 ; 
 int /*<<< orphan*/  PERF_REG_ARM64_X23 ; 
 int /*<<< orphan*/  PERF_REG_ARM64_X24 ; 
 int /*<<< orphan*/  PERF_REG_ARM64_X25 ; 
 int /*<<< orphan*/  PERF_REG_ARM64_X26 ; 
 int /*<<< orphan*/  PERF_REG_ARM64_X27 ; 
 int /*<<< orphan*/  PERF_REG_ARM64_X28 ; 
 int /*<<< orphan*/  PERF_REG_ARM64_X29 ; 
 int /*<<< orphan*/  PERF_REG_ARM64_X3 ; 
 int /*<<< orphan*/  PERF_REG_ARM64_X4 ; 
 int /*<<< orphan*/  PERF_REG_ARM64_X5 ; 
 int /*<<< orphan*/  PERF_REG_ARM64_X6 ; 
 int /*<<< orphan*/  PERF_REG_ARM64_X7 ; 
 int /*<<< orphan*/  PERF_REG_ARM64_X8 ; 
 int /*<<< orphan*/  PERF_REG_ARM64_X9 ; 
 int /*<<< orphan*/  dwfl_thread_state_register_pc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwfl_thread_state_registers (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perf_reg_value (int /*<<< orphan*/ *,struct regs_dump*,int /*<<< orphan*/ ) ; 

bool libdw__arch_set_initial_registers(Dwfl_Thread *thread, void *arg)
{
	struct unwind_info *ui = arg;
	struct regs_dump *user_regs = &ui->sample->user_regs;
	Dwarf_Word dwarf_regs[PERF_REG_ARM64_MAX], dwarf_pc;

#define REG(r) ({						\
	Dwarf_Word val = 0;					\
	perf_reg_value(&val, user_regs, PERF_REG_ARM64_##r);	\
	val;							\
})

	dwarf_regs[0]  = REG(X0);
	dwarf_regs[1]  = REG(X1);
	dwarf_regs[2]  = REG(X2);
	dwarf_regs[3]  = REG(X3);
	dwarf_regs[4]  = REG(X4);
	dwarf_regs[5]  = REG(X5);
	dwarf_regs[6]  = REG(X6);
	dwarf_regs[7]  = REG(X7);
	dwarf_regs[8]  = REG(X8);
	dwarf_regs[9]  = REG(X9);
	dwarf_regs[10] = REG(X10);
	dwarf_regs[11] = REG(X11);
	dwarf_regs[12] = REG(X12);
	dwarf_regs[13] = REG(X13);
	dwarf_regs[14] = REG(X14);
	dwarf_regs[15] = REG(X15);
	dwarf_regs[16] = REG(X16);
	dwarf_regs[17] = REG(X17);
	dwarf_regs[18] = REG(X18);
	dwarf_regs[19] = REG(X19);
	dwarf_regs[20] = REG(X20);
	dwarf_regs[21] = REG(X21);
	dwarf_regs[22] = REG(X22);
	dwarf_regs[23] = REG(X23);
	dwarf_regs[24] = REG(X24);
	dwarf_regs[25] = REG(X25);
	dwarf_regs[26] = REG(X26);
	dwarf_regs[27] = REG(X27);
	dwarf_regs[28] = REG(X28);
	dwarf_regs[29] = REG(X29);
	dwarf_regs[30] = REG(LR);
	dwarf_regs[31] = REG(SP);

	if (!dwfl_thread_state_registers(thread, 0, PERF_REG_ARM64_MAX,
					 dwarf_regs))
		return false;

	dwarf_pc = REG(PC);
	dwfl_thread_state_register_pc(thread, dwarf_pc);

	return true;
}