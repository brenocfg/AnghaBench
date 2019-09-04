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
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PERF_REG_S390_FP0 ; 
 int /*<<< orphan*/  PERF_REG_S390_FP1 ; 
 int /*<<< orphan*/  PERF_REG_S390_FP10 ; 
 int /*<<< orphan*/  PERF_REG_S390_FP11 ; 
 int /*<<< orphan*/  PERF_REG_S390_FP12 ; 
 int /*<<< orphan*/  PERF_REG_S390_FP13 ; 
 int /*<<< orphan*/  PERF_REG_S390_FP14 ; 
 int /*<<< orphan*/  PERF_REG_S390_FP15 ; 
 int /*<<< orphan*/  PERF_REG_S390_FP2 ; 
 int /*<<< orphan*/  PERF_REG_S390_FP3 ; 
 int /*<<< orphan*/  PERF_REG_S390_FP4 ; 
 int /*<<< orphan*/  PERF_REG_S390_FP5 ; 
 int /*<<< orphan*/  PERF_REG_S390_FP6 ; 
 int /*<<< orphan*/  PERF_REG_S390_FP7 ; 
 int /*<<< orphan*/  PERF_REG_S390_FP8 ; 
 int /*<<< orphan*/  PERF_REG_S390_FP9 ; 
 int /*<<< orphan*/  PERF_REG_S390_MASK ; 
 int /*<<< orphan*/  PERF_REG_S390_PC ; 
 int /*<<< orphan*/  PERF_REG_S390_R0 ; 
 int /*<<< orphan*/  PERF_REG_S390_R1 ; 
 int /*<<< orphan*/  PERF_REG_S390_R10 ; 
 int /*<<< orphan*/  PERF_REG_S390_R11 ; 
 int /*<<< orphan*/  PERF_REG_S390_R12 ; 
 int /*<<< orphan*/  PERF_REG_S390_R13 ; 
 int /*<<< orphan*/  PERF_REG_S390_R14 ; 
 int /*<<< orphan*/  PERF_REG_S390_R15 ; 
 int /*<<< orphan*/  PERF_REG_S390_R2 ; 
 int /*<<< orphan*/  PERF_REG_S390_R3 ; 
 int /*<<< orphan*/  PERF_REG_S390_R4 ; 
 int /*<<< orphan*/  PERF_REG_S390_R5 ; 
 int /*<<< orphan*/  PERF_REG_S390_R6 ; 
 int /*<<< orphan*/  PERF_REG_S390_R7 ; 
 int /*<<< orphan*/  PERF_REG_S390_R8 ; 
 int /*<<< orphan*/  PERF_REG_S390_R9 ; 
 int /*<<< orphan*/  dwfl_thread_state_register_pc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int dwfl_thread_state_registers (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perf_reg_value (int /*<<< orphan*/ *,struct regs_dump*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s390_dwarf_regs ; 

bool libdw__arch_set_initial_registers(Dwfl_Thread *thread, void *arg)
{
	struct unwind_info *ui = arg;
	struct regs_dump *user_regs = &ui->sample->user_regs;
	Dwarf_Word dwarf_regs[ARRAY_SIZE(s390_dwarf_regs)];

#define REG(r) ({						\
	Dwarf_Word val = 0;					\
	perf_reg_value(&val, user_regs, PERF_REG_S390_##r);	\
	val;							\
})
	/*
	 * For DWARF register mapping details,
	 * see also perf/arch/s390/include/dwarf-regs-table.h
	 */
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
	dwarf_regs[11] = REG(R11);
	dwarf_regs[12] = REG(R12);
	dwarf_regs[13] = REG(R13);
	dwarf_regs[14] = REG(R14);
	dwarf_regs[15] = REG(R15);

	dwarf_regs[16] = REG(FP0);
	dwarf_regs[17] = REG(FP2);
	dwarf_regs[18] = REG(FP4);
	dwarf_regs[19] = REG(FP6);
	dwarf_regs[20] = REG(FP1);
	dwarf_regs[21] = REG(FP3);
	dwarf_regs[22] = REG(FP5);
	dwarf_regs[23] = REG(FP7);
	dwarf_regs[24] = REG(FP8);
	dwarf_regs[25] = REG(FP10);
	dwarf_regs[26] = REG(FP12);
	dwarf_regs[27] = REG(FP14);
	dwarf_regs[28] = REG(FP9);
	dwarf_regs[29] = REG(FP11);
	dwarf_regs[30] = REG(FP13);
	dwarf_regs[31] = REG(FP15);

	dwarf_regs[64] = REG(MASK);
	dwarf_regs[65] = REG(PC);

	dwfl_thread_state_register_pc(thread, dwarf_regs[65]);
	return dwfl_thread_state_registers(thread, 0, 32, dwarf_regs);
}