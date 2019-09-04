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

__attribute__((used)) static const char *decode_shift(arm_shifter shift) {
	static const char *E_OP_SR = ">>";
	static const char *E_OP_SL = "<<";
	static const char *E_OP_RR = ">>>";
	static const char *E_OP_ASR = ">>>>";
	static const char *E_OP_VOID = "";

	switch (shift) {
	case ARM_SFT_ASR:
	case ARM_SFT_ASR_REG:
		return E_OP_ASR;

	case ARM_SFT_LSR:
	case ARM_SFT_LSR_REG:
		return E_OP_SR;

	case ARM_SFT_LSL:
	case ARM_SFT_LSL_REG:
		return E_OP_SL;

	case ARM_SFT_ROR:
	case ARM_SFT_RRX:
	case ARM_SFT_ROR_REG:
	case ARM_SFT_RRX_REG:
		return E_OP_RR;

	default:
		break;
	}
	return E_OP_VOID;
}