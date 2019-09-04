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
#define  ARM64_REG_W0 158 
#define  ARM64_REG_W1 157 
#define  ARM64_REG_W10 156 
#define  ARM64_REG_W11 155 
#define  ARM64_REG_W12 154 
#define  ARM64_REG_W13 153 
#define  ARM64_REG_W14 152 
#define  ARM64_REG_W15 151 
#define  ARM64_REG_W16 150 
#define  ARM64_REG_W17 149 
#define  ARM64_REG_W18 148 
#define  ARM64_REG_W19 147 
#define  ARM64_REG_W2 146 
#define  ARM64_REG_W20 145 
#define  ARM64_REG_W21 144 
#define  ARM64_REG_W22 143 
#define  ARM64_REG_W23 142 
#define  ARM64_REG_W24 141 
#define  ARM64_REG_W25 140 
#define  ARM64_REG_W26 139 
#define  ARM64_REG_W27 138 
#define  ARM64_REG_W28 137 
#define  ARM64_REG_W29 136 
#define  ARM64_REG_W3 135 
#define  ARM64_REG_W30 134 
#define  ARM64_REG_W4 133 
#define  ARM64_REG_W5 132 
#define  ARM64_REG_W6 131 
#define  ARM64_REG_W7 130 
#define  ARM64_REG_W8 129 
#define  ARM64_REG_W9 128 

__attribute__((used)) static int arm64_reg_width(int reg) {
	switch (reg) {
	case ARM64_REG_W0:
	case ARM64_REG_W1:
	case ARM64_REG_W2:
	case ARM64_REG_W3:
	case ARM64_REG_W4:
	case ARM64_REG_W5:
	case ARM64_REG_W6:
	case ARM64_REG_W7:
	case ARM64_REG_W8:
	case ARM64_REG_W9:
	case ARM64_REG_W10:
	case ARM64_REG_W11:
	case ARM64_REG_W12:
	case ARM64_REG_W13:
	case ARM64_REG_W14:
	case ARM64_REG_W15:
	case ARM64_REG_W16:
	case ARM64_REG_W17:
	case ARM64_REG_W18:
	case ARM64_REG_W19:
	case ARM64_REG_W20:
	case ARM64_REG_W21:
	case ARM64_REG_W22:
	case ARM64_REG_W23:
	case ARM64_REG_W24:
	case ARM64_REG_W25:
	case ARM64_REG_W26:
	case ARM64_REG_W27:
	case ARM64_REG_W28:
	case ARM64_REG_W29:
	case ARM64_REG_W30:
		return 32;
		break;
	default:
		break;
	}
	return 64;
}