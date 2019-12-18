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
#define  HEX_SUB_REG_R0 143 
#define  HEX_SUB_REG_R1 142 
#define  HEX_SUB_REG_R16 141 
#define  HEX_SUB_REG_R17 140 
#define  HEX_SUB_REG_R18 139 
#define  HEX_SUB_REG_R19 138 
#define  HEX_SUB_REG_R2 137 
#define  HEX_SUB_REG_R20 136 
#define  HEX_SUB_REG_R21 135 
#define  HEX_SUB_REG_R22 134 
#define  HEX_SUB_REG_R23 133 
#define  HEX_SUB_REG_R3 132 
#define  HEX_SUB_REG_R4 131 
#define  HEX_SUB_REG_R5 130 
#define  HEX_SUB_REG_R6 129 
#define  HEX_SUB_REG_R7 128 

char* hex_get_sub_reg(int opreg)
{
	switch (opreg) {
		case HEX_SUB_REG_R0:
			return "R0";
		case HEX_SUB_REG_R1:
			return "R1";
		case HEX_SUB_REG_R2:
			return "R2";
		case HEX_SUB_REG_R3:
			return "R3";
		case HEX_SUB_REG_R4:
			return "R4";
		case HEX_SUB_REG_R5:
			return "R5";
		case HEX_SUB_REG_R6:
			return "R6";
		case HEX_SUB_REG_R7:
			return "R7";
		case HEX_SUB_REG_R16:
			return "R16";
		case HEX_SUB_REG_R17:
			return "R17";
		case HEX_SUB_REG_R18:
			return "R18";
		case HEX_SUB_REG_R19:
			return "R19";
		case HEX_SUB_REG_R20:
			return "R20";
		case HEX_SUB_REG_R21:
			return "R21";
		case HEX_SUB_REG_R22:
			return "R22";
		case HEX_SUB_REG_R23:
			return "R23";
		default:
			return "<err>";
	}
}