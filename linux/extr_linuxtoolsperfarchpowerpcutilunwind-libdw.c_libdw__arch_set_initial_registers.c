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
 size_t ARRAY_SIZE (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  PERF_REG_POWERPC_NIP ; 
 int /*<<< orphan*/  PERF_REG_POWERPC_R0 ; 
 int /*<<< orphan*/  PERF_REG_POWERPC_R1 ; 
 int /*<<< orphan*/  PERF_REG_POWERPC_R10 ; 
 int /*<<< orphan*/  PERF_REG_POWERPC_R11 ; 
 int /*<<< orphan*/  PERF_REG_POWERPC_R12 ; 
 int /*<<< orphan*/  PERF_REG_POWERPC_R13 ; 
 int /*<<< orphan*/  PERF_REG_POWERPC_R14 ; 
 int /*<<< orphan*/  PERF_REG_POWERPC_R15 ; 
 int /*<<< orphan*/  PERF_REG_POWERPC_R16 ; 
 int /*<<< orphan*/  PERF_REG_POWERPC_R17 ; 
 int /*<<< orphan*/  PERF_REG_POWERPC_R18 ; 
 int /*<<< orphan*/  PERF_REG_POWERPC_R19 ; 
 int /*<<< orphan*/  PERF_REG_POWERPC_R2 ; 
 int /*<<< orphan*/  PERF_REG_POWERPC_R20 ; 
 int /*<<< orphan*/  PERF_REG_POWERPC_R21 ; 
 int /*<<< orphan*/  PERF_REG_POWERPC_R22 ; 
 int /*<<< orphan*/  PERF_REG_POWERPC_R23 ; 
 int /*<<< orphan*/  PERF_REG_POWERPC_R24 ; 
 int /*<<< orphan*/  PERF_REG_POWERPC_R25 ; 
 int /*<<< orphan*/  PERF_REG_POWERPC_R26 ; 
 int /*<<< orphan*/  PERF_REG_POWERPC_R27 ; 
 int /*<<< orphan*/  PERF_REG_POWERPC_R28 ; 
 int /*<<< orphan*/  PERF_REG_POWERPC_R29 ; 
 int /*<<< orphan*/  PERF_REG_POWERPC_R3 ; 
 int /*<<< orphan*/  PERF_REG_POWERPC_R30 ; 
 int /*<<< orphan*/  PERF_REG_POWERPC_R31 ; 
 int /*<<< orphan*/  PERF_REG_POWERPC_R4 ; 
 int /*<<< orphan*/  PERF_REG_POWERPC_R5 ; 
 int /*<<< orphan*/  PERF_REG_POWERPC_R6 ; 
 int /*<<< orphan*/  PERF_REG_POWERPC_R7 ; 
 int /*<<< orphan*/  PERF_REG_POWERPC_R8 ; 
 int /*<<< orphan*/  PERF_REG_POWERPC_R9 ; 
 int /*<<< orphan*/  dwfl_thread_state_register_pc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwfl_thread_state_registers (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perf_reg_value (int /*<<< orphan*/ *,struct regs_dump*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ ** special_regs ; 

bool libdw__arch_set_initial_registers(Dwfl_Thread *thread, void *arg)
{
	struct unwind_info *ui = arg;
	struct regs_dump *user_regs = &ui->sample->user_regs;
	Dwarf_Word dwarf_regs[32], dwarf_nip;
	size_t i;

#define REG(r) ({						\
	Dwarf_Word val = 0;					\
	perf_reg_value(&val, user_regs, PERF_REG_POWERPC_##r);	\
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
	dwarf_regs[11] = REG(R11);
	dwarf_regs[12] = REG(R12);
	dwarf_regs[13] = REG(R13);
	dwarf_regs[14] = REG(R14);
	dwarf_regs[15] = REG(R15);
	dwarf_regs[16] = REG(R16);
	dwarf_regs[17] = REG(R17);
	dwarf_regs[18] = REG(R18);
	dwarf_regs[19] = REG(R19);
	dwarf_regs[20] = REG(R20);
	dwarf_regs[21] = REG(R21);
	dwarf_regs[22] = REG(R22);
	dwarf_regs[23] = REG(R23);
	dwarf_regs[24] = REG(R24);
	dwarf_regs[25] = REG(R25);
	dwarf_regs[26] = REG(R26);
	dwarf_regs[27] = REG(R27);
	dwarf_regs[28] = REG(R28);
	dwarf_regs[29] = REG(R29);
	dwarf_regs[30] = REG(R30);
	dwarf_regs[31] = REG(R31);
	if (!dwfl_thread_state_registers(thread, 0, 32, dwarf_regs))
		return false;

	dwarf_nip = REG(NIP);
	dwfl_thread_state_register_pc(thread, dwarf_nip);
	for (i = 0; i < ARRAY_SIZE(special_regs); i++) {
		Dwarf_Word val = 0;
		perf_reg_value(&val, user_regs, special_regs[i][1]);
		if (!dwfl_thread_state_registers(thread,
						 special_regs[i][0], 1,
						 &val))
			return false;
	}

	return true;
}