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
#define  HEX_SUB_REGPAIR_R17_R16 135 
#define  HEX_SUB_REGPAIR_R19_R18 134 
#define  HEX_SUB_REGPAIR_R1_R0 133 
#define  HEX_SUB_REGPAIR_R21_R20 132 
#define  HEX_SUB_REGPAIR_R23_R22 131 
#define  HEX_SUB_REGPAIR_R3_R2 130 
#define  HEX_SUB_REGPAIR_R5_R4 129 
#define  HEX_SUB_REGPAIR_R7_R6 128 

char* hex_get_sub_regpair(int opreg)
{
	switch (opreg) {
		case HEX_SUB_REGPAIR_R1_R0:
			return "R1:R0";
		case HEX_SUB_REGPAIR_R3_R2:
			return "R3:R2";
		case HEX_SUB_REGPAIR_R5_R4:
			return "R5:R4";
		case HEX_SUB_REGPAIR_R7_R6:
			return "R7:R6";
		case HEX_SUB_REGPAIR_R17_R16:
			return "R17:R16";
		case HEX_SUB_REGPAIR_R19_R18:
			return "R19:R18";
		case HEX_SUB_REGPAIR_R21_R20:
			return "R21:R20";
		case HEX_SUB_REGPAIR_R23_R22:
			return "R23:R22";
		default:
			return "<err>";
	}
}