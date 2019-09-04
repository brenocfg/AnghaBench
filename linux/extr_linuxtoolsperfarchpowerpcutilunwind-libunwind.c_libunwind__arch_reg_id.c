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
 int PERF_REG_POWERPC_CTR ; 
 int PERF_REG_POWERPC_LINK ; 
 int PERF_REG_POWERPC_NIP ; 
 int PERF_REG_POWERPC_R0 ; 
 int PERF_REG_POWERPC_R1 ; 
 int PERF_REG_POWERPC_R10 ; 
 int PERF_REG_POWERPC_R11 ; 
 int PERF_REG_POWERPC_R12 ; 
 int PERF_REG_POWERPC_R13 ; 
 int PERF_REG_POWERPC_R14 ; 
 int PERF_REG_POWERPC_R15 ; 
 int PERF_REG_POWERPC_R16 ; 
 int PERF_REG_POWERPC_R17 ; 
 int PERF_REG_POWERPC_R18 ; 
 int PERF_REG_POWERPC_R19 ; 
 int PERF_REG_POWERPC_R2 ; 
 int PERF_REG_POWERPC_R20 ; 
 int PERF_REG_POWERPC_R21 ; 
 int PERF_REG_POWERPC_R22 ; 
 int PERF_REG_POWERPC_R23 ; 
 int PERF_REG_POWERPC_R24 ; 
 int PERF_REG_POWERPC_R25 ; 
 int PERF_REG_POWERPC_R26 ; 
 int PERF_REG_POWERPC_R27 ; 
 int PERF_REG_POWERPC_R28 ; 
 int PERF_REG_POWERPC_R29 ; 
 int PERF_REG_POWERPC_R3 ; 
 int PERF_REG_POWERPC_R30 ; 
 int PERF_REG_POWERPC_R31 ; 
 int PERF_REG_POWERPC_R4 ; 
 int PERF_REG_POWERPC_R5 ; 
 int PERF_REG_POWERPC_R6 ; 
 int PERF_REG_POWERPC_R7 ; 
 int PERF_REG_POWERPC_R8 ; 
 int PERF_REG_POWERPC_R9 ; 
 int PERF_REG_POWERPC_XER ; 
#define  UNW_PPC64_CTR 163 
#define  UNW_PPC64_LR 162 
#define  UNW_PPC64_NIP 161 
#define  UNW_PPC64_R0 160 
#define  UNW_PPC64_R1 159 
#define  UNW_PPC64_R10 158 
#define  UNW_PPC64_R11 157 
#define  UNW_PPC64_R12 156 
#define  UNW_PPC64_R13 155 
#define  UNW_PPC64_R14 154 
#define  UNW_PPC64_R15 153 
#define  UNW_PPC64_R16 152 
#define  UNW_PPC64_R17 151 
#define  UNW_PPC64_R18 150 
#define  UNW_PPC64_R19 149 
#define  UNW_PPC64_R2 148 
#define  UNW_PPC64_R20 147 
#define  UNW_PPC64_R21 146 
#define  UNW_PPC64_R22 145 
#define  UNW_PPC64_R23 144 
#define  UNW_PPC64_R24 143 
#define  UNW_PPC64_R25 142 
#define  UNW_PPC64_R26 141 
#define  UNW_PPC64_R27 140 
#define  UNW_PPC64_R28 139 
#define  UNW_PPC64_R29 138 
#define  UNW_PPC64_R3 137 
#define  UNW_PPC64_R30 136 
#define  UNW_PPC64_R31 135 
#define  UNW_PPC64_R4 134 
#define  UNW_PPC64_R5 133 
#define  UNW_PPC64_R6 132 
#define  UNW_PPC64_R7 131 
#define  UNW_PPC64_R8 130 
#define  UNW_PPC64_R9 129 
#define  UNW_PPC64_XER 128 
 int /*<<< orphan*/  pr_err (char*,int) ; 

int libunwind__arch_reg_id(int regnum)
{
	switch (regnum) {
	case UNW_PPC64_R0:
		return PERF_REG_POWERPC_R0;
	case UNW_PPC64_R1:
		return PERF_REG_POWERPC_R1;
	case UNW_PPC64_R2:
		return PERF_REG_POWERPC_R2;
	case UNW_PPC64_R3:
		return PERF_REG_POWERPC_R3;
	case UNW_PPC64_R4:
		return PERF_REG_POWERPC_R4;
	case UNW_PPC64_R5:
		return PERF_REG_POWERPC_R5;
	case UNW_PPC64_R6:
		return PERF_REG_POWERPC_R6;
	case UNW_PPC64_R7:
		return PERF_REG_POWERPC_R7;
	case UNW_PPC64_R8:
		return PERF_REG_POWERPC_R8;
	case UNW_PPC64_R9:
		return PERF_REG_POWERPC_R9;
	case UNW_PPC64_R10:
		return PERF_REG_POWERPC_R10;
	case UNW_PPC64_R11:
		return PERF_REG_POWERPC_R11;
	case UNW_PPC64_R12:
		return PERF_REG_POWERPC_R12;
	case UNW_PPC64_R13:
		return PERF_REG_POWERPC_R13;
	case UNW_PPC64_R14:
		return PERF_REG_POWERPC_R14;
	case UNW_PPC64_R15:
		return PERF_REG_POWERPC_R15;
	case UNW_PPC64_R16:
		return PERF_REG_POWERPC_R16;
	case UNW_PPC64_R17:
		return PERF_REG_POWERPC_R17;
	case UNW_PPC64_R18:
		return PERF_REG_POWERPC_R18;
	case UNW_PPC64_R19:
		return PERF_REG_POWERPC_R19;
	case UNW_PPC64_R20:
		return PERF_REG_POWERPC_R20;
	case UNW_PPC64_R21:
		return PERF_REG_POWERPC_R21;
	case UNW_PPC64_R22:
		return PERF_REG_POWERPC_R22;
	case UNW_PPC64_R23:
		return PERF_REG_POWERPC_R23;
	case UNW_PPC64_R24:
		return PERF_REG_POWERPC_R24;
	case UNW_PPC64_R25:
		return PERF_REG_POWERPC_R25;
	case UNW_PPC64_R26:
		return PERF_REG_POWERPC_R26;
	case UNW_PPC64_R27:
		return PERF_REG_POWERPC_R27;
	case UNW_PPC64_R28:
		return PERF_REG_POWERPC_R28;
	case UNW_PPC64_R29:
		return PERF_REG_POWERPC_R29;
	case UNW_PPC64_R30:
		return PERF_REG_POWERPC_R30;
	case UNW_PPC64_R31:
		return PERF_REG_POWERPC_R31;
	case UNW_PPC64_LR:
		return PERF_REG_POWERPC_LINK;
	case UNW_PPC64_CTR:
		return PERF_REG_POWERPC_CTR;
	case UNW_PPC64_XER:
		return PERF_REG_POWERPC_XER;
	case UNW_PPC64_NIP:
		return PERF_REG_POWERPC_NIP;
	default:
		pr_err("unwind: invalid reg id %d\n", regnum);
		return -EINVAL;
	}
	return -EINVAL;
}