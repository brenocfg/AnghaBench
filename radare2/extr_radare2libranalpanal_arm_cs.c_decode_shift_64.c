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
typedef  int arm64_shifter ;

/* Variables and functions */
#define  ARM64_SFT_ASR 132 
#define  ARM64_SFT_LSL 131 
#define  ARM64_SFT_LSR 130 
#define  ARM64_SFT_MSL 129 
#define  ARM64_SFT_ROR 128 

__attribute__((used)) static const char *decode_shift_64(arm64_shifter shift) {
	static const char *E_OP_SR = ">>";
	static const char *E_OP_SL = "<<";
	static const char *E_OP_RR = ">>>";
	static const char *E_OP_VOID = "";

	switch (shift) {
	case ARM64_SFT_ASR:
	case ARM64_SFT_LSR:
		return E_OP_SR;

	case ARM64_SFT_LSL:
	case ARM64_SFT_MSL:
		return E_OP_SL;

	case ARM64_SFT_ROR:
		return E_OP_RR;

	default:
		break;
	}
	return E_OP_VOID;
}