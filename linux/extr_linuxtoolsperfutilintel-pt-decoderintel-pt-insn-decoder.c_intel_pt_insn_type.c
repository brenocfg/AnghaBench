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
typedef  enum intel_pt_insn_op { ____Placeholder_intel_pt_insn_op } intel_pt_insn_op ;

/* Variables and functions */
#define  INTEL_PT_OP_CALL 137 
#define  INTEL_PT_OP_INT 136 
#define  INTEL_PT_OP_IRET 135 
#define  INTEL_PT_OP_JCC 134 
#define  INTEL_PT_OP_JMP 133 
#define  INTEL_PT_OP_LOOP 132 
#define  INTEL_PT_OP_OTHER 131 
#define  INTEL_PT_OP_RET 130 
#define  INTEL_PT_OP_SYSCALL 129 
#define  INTEL_PT_OP_SYSRET 128 
 int PERF_IP_FLAG_BRANCH ; 
 int PERF_IP_FLAG_CALL ; 
 int PERF_IP_FLAG_CONDITIONAL ; 
 int PERF_IP_FLAG_INTERRUPT ; 
 int PERF_IP_FLAG_RETURN ; 
 int PERF_IP_FLAG_SYSCALLRET ; 

int intel_pt_insn_type(enum intel_pt_insn_op op)
{
	switch (op) {
	case INTEL_PT_OP_OTHER:
		return 0;
	case INTEL_PT_OP_CALL:
		return PERF_IP_FLAG_BRANCH | PERF_IP_FLAG_CALL;
	case INTEL_PT_OP_RET:
		return PERF_IP_FLAG_BRANCH | PERF_IP_FLAG_RETURN;
	case INTEL_PT_OP_JCC:
		return PERF_IP_FLAG_BRANCH | PERF_IP_FLAG_CONDITIONAL;
	case INTEL_PT_OP_JMP:
		return PERF_IP_FLAG_BRANCH;
	case INTEL_PT_OP_LOOP:
		return PERF_IP_FLAG_BRANCH | PERF_IP_FLAG_CONDITIONAL;
	case INTEL_PT_OP_IRET:
		return PERF_IP_FLAG_BRANCH | PERF_IP_FLAG_RETURN |
		       PERF_IP_FLAG_INTERRUPT;
	case INTEL_PT_OP_INT:
		return PERF_IP_FLAG_BRANCH | PERF_IP_FLAG_CALL |
		       PERF_IP_FLAG_INTERRUPT;
	case INTEL_PT_OP_SYSCALL:
		return PERF_IP_FLAG_BRANCH | PERF_IP_FLAG_CALL |
		       PERF_IP_FLAG_SYSCALLRET;
	case INTEL_PT_OP_SYSRET:
		return PERF_IP_FLAG_BRANCH | PERF_IP_FLAG_RETURN |
		       PERF_IP_FLAG_SYSCALLRET;
	default:
		return 0;
	}
}