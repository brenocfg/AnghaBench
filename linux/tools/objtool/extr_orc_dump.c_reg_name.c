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
#define  ORC_REG_BP 136 
#define  ORC_REG_BP_INDIRECT 135 
#define  ORC_REG_DI 134 
#define  ORC_REG_DX 133 
#define  ORC_REG_PREV_SP 132 
#define  ORC_REG_R10 131 
#define  ORC_REG_R13 130 
#define  ORC_REG_SP 129 
#define  ORC_REG_SP_INDIRECT 128 

__attribute__((used)) static const char *reg_name(unsigned int reg)
{
	switch (reg) {
	case ORC_REG_PREV_SP:
		return "prevsp";
	case ORC_REG_DX:
		return "dx";
	case ORC_REG_DI:
		return "di";
	case ORC_REG_BP:
		return "bp";
	case ORC_REG_SP:
		return "sp";
	case ORC_REG_R10:
		return "r10";
	case ORC_REG_R13:
		return "r13";
	case ORC_REG_BP_INDIRECT:
		return "bp(ind)";
	case ORC_REG_SP_INDIRECT:
		return "sp(ind)";
	default:
		return "?";
	}
}