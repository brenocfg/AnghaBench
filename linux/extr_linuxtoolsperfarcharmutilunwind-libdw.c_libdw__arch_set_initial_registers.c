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
 int /*<<< orphan*/  PERF_REG_ARM_FP ; 
 int /*<<< orphan*/  PERF_REG_ARM_IP ; 
 int /*<<< orphan*/  PERF_REG_ARM_LR ; 
 int PERF_REG_ARM_MAX ; 
 int /*<<< orphan*/  PERF_REG_ARM_PC ; 
 int /*<<< orphan*/  PERF_REG_ARM_R0 ; 
 int /*<<< orphan*/  PERF_REG_ARM_R1 ; 
 int /*<<< orphan*/  PERF_REG_ARM_R10 ; 
 int /*<<< orphan*/  PERF_REG_ARM_R2 ; 
 int /*<<< orphan*/  PERF_REG_ARM_R3 ; 
 int /*<<< orphan*/  PERF_REG_ARM_R4 ; 
 int /*<<< orphan*/  PERF_REG_ARM_R5 ; 
 int /*<<< orphan*/  PERF_REG_ARM_R6 ; 
 int /*<<< orphan*/  PERF_REG_ARM_R7 ; 
 int /*<<< orphan*/  PERF_REG_ARM_R8 ; 
 int /*<<< orphan*/  PERF_REG_ARM_R9 ; 
 int /*<<< orphan*/  PERF_REG_ARM_SP ; 
 int dwfl_thread_state_registers (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perf_reg_value (int /*<<< orphan*/ *,struct regs_dump*,int /*<<< orphan*/ ) ; 

bool libdw__arch_set_initial_registers(Dwfl_Thread *thread, void *arg)
{
	struct unwind_info *ui = arg;
	struct regs_dump *user_regs = &ui->sample->user_regs;
	Dwarf_Word dwarf_regs[PERF_REG_ARM_MAX];

#define REG(r) ({						\
	Dwarf_Word val = 0;					\
	perf_reg_value(&val, user_regs, PERF_REG_ARM_##r);	\
	val;							\
})

	dwarf_regs[0]  = REG(R0);
	dwarf_regs[1]  = REG(R1);
	dwarf_regs[2]  = REG(R2);
	dwarf_regs[3]  = REG(R3);
	dwarf_regs[4]  = REG(R4);
	dwarf_regs[5]  = REG(R5);
	dwarf_regs[6]  = REG(R6);
	dwarf_regs[7]  = REG(R7);
	dwarf_regs[8]  = REG(R8);
	dwarf_regs[9]  = REG(R9);
	dwarf_regs[10] = REG(R10);
	dwarf_regs[11] = REG(FP);
	dwarf_regs[12] = REG(IP);
	dwarf_regs[13] = REG(SP);
	dwarf_regs[14] = REG(LR);
	dwarf_regs[15] = REG(PC);

	return dwfl_thread_state_registers(thread, 0, PERF_REG_ARM_MAX,
					   dwarf_regs);
}