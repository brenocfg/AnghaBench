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
typedef  int arm_shifter ;

/* Variables and functions */
#define  ARM_SFT_ASR 137 
#define  ARM_SFT_ASR_REG 136 
#define  ARM_SFT_LSL 135 
#define  ARM_SFT_LSL_REG 134 
#define  ARM_SFT_LSR 133 
#define  ARM_SFT_LSR_REG 132 
#define  ARM_SFT_ROR 131 
#define  ARM_SFT_ROR_REG 130 
#define  ARM_SFT_RRX 129 
#define  ARM_SFT_RRX_REG 128 

__attribute__((used)) static const char *shift_type_name(arm_shifter type) {
	switch (type) {
	case ARM_SFT_ASR:
		return "asr";
	case ARM_SFT_LSL:
		return "lsl";
	case ARM_SFT_LSR:
		return "lsr";
	case ARM_SFT_ROR:
		return "ror";
	case ARM_SFT_RRX:
		return "rrx";
	case ARM_SFT_ASR_REG:
		return "asr_reg";
	case ARM_SFT_LSL_REG:
		return "lsl_reg";
	case ARM_SFT_LSR_REG:
		return "lsr_reg";
	case ARM_SFT_ROR_REG:
		return "ror_reg";
	case ARM_SFT_RRX_REG:
		return "rrx_reg";
	default:
		return "";
	}
}