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

/* Variables and functions */
 int EINVAL ; 
 int PERF_REG_ARM_FP ; 
 int PERF_REG_ARM_IP ; 
 int PERF_REG_ARM_LR ; 
 int PERF_REG_ARM_PC ; 
 int PERF_REG_ARM_R0 ; 
 int PERF_REG_ARM_R1 ; 
 int PERF_REG_ARM_R10 ; 
 int PERF_REG_ARM_R2 ; 
 int PERF_REG_ARM_R3 ; 
 int PERF_REG_ARM_R4 ; 
 int PERF_REG_ARM_R5 ; 
 int PERF_REG_ARM_R6 ; 
 int PERF_REG_ARM_R7 ; 
 int PERF_REG_ARM_R8 ; 
 int PERF_REG_ARM_R9 ; 
 int PERF_REG_ARM_SP ; 
#define  UNW_ARM_R0 143 
#define  UNW_ARM_R1 142 
#define  UNW_ARM_R10 141 
#define  UNW_ARM_R11 140 
#define  UNW_ARM_R12 139 
#define  UNW_ARM_R13 138 
#define  UNW_ARM_R14 137 
#define  UNW_ARM_R15 136 
#define  UNW_ARM_R2 135 
#define  UNW_ARM_R3 134 
#define  UNW_ARM_R4 133 
#define  UNW_ARM_R5 132 
#define  UNW_ARM_R6 131 
#define  UNW_ARM_R7 130 
#define  UNW_ARM_R8 129 
#define  UNW_ARM_R9 128 
 int /*<<< orphan*/  pr_err (char*,int) ; 

int libunwind__arch_reg_id(int regnum)
{
	switch (regnum) {
	case UNW_ARM_R0:
		return PERF_REG_ARM_R0;
	case UNW_ARM_R1:
		return PERF_REG_ARM_R1;
	case UNW_ARM_R2:
		return PERF_REG_ARM_R2;
	case UNW_ARM_R3:
		return PERF_REG_ARM_R3;
	case UNW_ARM_R4:
		return PERF_REG_ARM_R4;
	case UNW_ARM_R5:
		return PERF_REG_ARM_R5;
	case UNW_ARM_R6:
		return PERF_REG_ARM_R6;
	case UNW_ARM_R7:
		return PERF_REG_ARM_R7;
	case UNW_ARM_R8:
		return PERF_REG_ARM_R8;
	case UNW_ARM_R9:
		return PERF_REG_ARM_R9;
	case UNW_ARM_R10:
		return PERF_REG_ARM_R10;
	case UNW_ARM_R11:
		return PERF_REG_ARM_FP;
	case UNW_ARM_R12:
		return PERF_REG_ARM_IP;
	case UNW_ARM_R13:
		return PERF_REG_ARM_SP;
	case UNW_ARM_R14:
		return PERF_REG_ARM_LR;
	case UNW_ARM_R15:
		return PERF_REG_ARM_PC;
	default:
		pr_err("unwind: invalid reg id %d\n", regnum);
		return -EINVAL;
	}

	return -EINVAL;
}