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
 int PERF_REG_ARM64_LR ; 
 int PERF_REG_ARM64_PC ; 
 int PERF_REG_ARM64_SP ; 
 int PERF_REG_ARM64_X0 ; 
 int PERF_REG_ARM64_X1 ; 
 int PERF_REG_ARM64_X10 ; 
 int PERF_REG_ARM64_X11 ; 
 int PERF_REG_ARM64_X12 ; 
 int PERF_REG_ARM64_X13 ; 
 int PERF_REG_ARM64_X14 ; 
 int PERF_REG_ARM64_X15 ; 
 int PERF_REG_ARM64_X16 ; 
 int PERF_REG_ARM64_X17 ; 
 int PERF_REG_ARM64_X18 ; 
 int PERF_REG_ARM64_X19 ; 
 int PERF_REG_ARM64_X2 ; 
 int PERF_REG_ARM64_X20 ; 
 int PERF_REG_ARM64_X21 ; 
 int PERF_REG_ARM64_X22 ; 
 int PERF_REG_ARM64_X23 ; 
 int PERF_REG_ARM64_X24 ; 
 int PERF_REG_ARM64_X25 ; 
 int PERF_REG_ARM64_X26 ; 
 int PERF_REG_ARM64_X27 ; 
 int PERF_REG_ARM64_X28 ; 
 int PERF_REG_ARM64_X29 ; 
 int PERF_REG_ARM64_X3 ; 
 int PERF_REG_ARM64_X4 ; 
 int PERF_REG_ARM64_X5 ; 
 int PERF_REG_ARM64_X6 ; 
 int PERF_REG_ARM64_X7 ; 
 int PERF_REG_ARM64_X8 ; 
 int PERF_REG_ARM64_X9 ; 
#define  UNW_AARCH64_PC 160 
#define  UNW_AARCH64_SP 159 
#define  UNW_AARCH64_X0 158 
#define  UNW_AARCH64_X1 157 
#define  UNW_AARCH64_X10 156 
#define  UNW_AARCH64_X11 155 
#define  UNW_AARCH64_X12 154 
#define  UNW_AARCH64_X13 153 
#define  UNW_AARCH64_X14 152 
#define  UNW_AARCH64_X15 151 
#define  UNW_AARCH64_X16 150 
#define  UNW_AARCH64_X17 149 
#define  UNW_AARCH64_X18 148 
#define  UNW_AARCH64_X19 147 
#define  UNW_AARCH64_X2 146 
#define  UNW_AARCH64_X20 145 
#define  UNW_AARCH64_X21 144 
#define  UNW_AARCH64_X22 143 
#define  UNW_AARCH64_X23 142 
#define  UNW_AARCH64_X24 141 
#define  UNW_AARCH64_X25 140 
#define  UNW_AARCH64_X26 139 
#define  UNW_AARCH64_X27 138 
#define  UNW_AARCH64_X28 137 
#define  UNW_AARCH64_X29 136 
#define  UNW_AARCH64_X3 135 
#define  UNW_AARCH64_X30 134 
#define  UNW_AARCH64_X4 133 
#define  UNW_AARCH64_X5 132 
#define  UNW_AARCH64_X6 131 
#define  UNW_AARCH64_X7 130 
#define  UNW_AARCH64_X8 129 
#define  UNW_AARCH64_X9 128 
 int /*<<< orphan*/  pr_err (char*,int) ; 

int LIBUNWIND__ARCH_REG_ID(int regnum)
{
	switch (regnum) {
	case UNW_AARCH64_X0:
		return PERF_REG_ARM64_X0;
	case UNW_AARCH64_X1:
		return PERF_REG_ARM64_X1;
	case UNW_AARCH64_X2:
		return PERF_REG_ARM64_X2;
	case UNW_AARCH64_X3:
		return PERF_REG_ARM64_X3;
	case UNW_AARCH64_X4:
		return PERF_REG_ARM64_X4;
	case UNW_AARCH64_X5:
		return PERF_REG_ARM64_X5;
	case UNW_AARCH64_X6:
		return PERF_REG_ARM64_X6;
	case UNW_AARCH64_X7:
		return PERF_REG_ARM64_X7;
	case UNW_AARCH64_X8:
		return PERF_REG_ARM64_X8;
	case UNW_AARCH64_X9:
		return PERF_REG_ARM64_X9;
	case UNW_AARCH64_X10:
		return PERF_REG_ARM64_X10;
	case UNW_AARCH64_X11:
		return PERF_REG_ARM64_X11;
	case UNW_AARCH64_X12:
		return PERF_REG_ARM64_X12;
	case UNW_AARCH64_X13:
		return PERF_REG_ARM64_X13;
	case UNW_AARCH64_X14:
		return PERF_REG_ARM64_X14;
	case UNW_AARCH64_X15:
		return PERF_REG_ARM64_X15;
	case UNW_AARCH64_X16:
		return PERF_REG_ARM64_X16;
	case UNW_AARCH64_X17:
		return PERF_REG_ARM64_X17;
	case UNW_AARCH64_X18:
		return PERF_REG_ARM64_X18;
	case UNW_AARCH64_X19:
		return PERF_REG_ARM64_X19;
	case UNW_AARCH64_X20:
		return PERF_REG_ARM64_X20;
	case UNW_AARCH64_X21:
		return PERF_REG_ARM64_X21;
	case UNW_AARCH64_X22:
		return PERF_REG_ARM64_X22;
	case UNW_AARCH64_X23:
		return PERF_REG_ARM64_X23;
	case UNW_AARCH64_X24:
		return PERF_REG_ARM64_X24;
	case UNW_AARCH64_X25:
		return PERF_REG_ARM64_X25;
	case UNW_AARCH64_X26:
		return PERF_REG_ARM64_X26;
	case UNW_AARCH64_X27:
		return PERF_REG_ARM64_X27;
	case UNW_AARCH64_X28:
		return PERF_REG_ARM64_X28;
	case UNW_AARCH64_X29:
		return PERF_REG_ARM64_X29;
	case UNW_AARCH64_X30:
		return PERF_REG_ARM64_LR;
	case UNW_AARCH64_SP:
		return PERF_REG_ARM64_SP;
	case UNW_AARCH64_PC:
		return PERF_REG_ARM64_PC;
	default:
		pr_err("unwind: invalid reg id %d\n", regnum);
		return -EINVAL;
	}

	return -EINVAL;
}