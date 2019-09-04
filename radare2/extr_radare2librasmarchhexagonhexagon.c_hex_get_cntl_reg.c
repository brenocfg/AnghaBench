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
#define  HEX_REG_CS0 148 
#define  HEX_REG_CS1 147 
#define  HEX_REG_FRAMEKEY 146 
#define  HEX_REG_FRAMELIMIT 145 
#define  HEX_REG_GP 144 
#define  HEX_REG_LC0 143 
#define  HEX_REG_LC1 142 
#define  HEX_REG_M0 141 
#define  HEX_REG_M1 140 
#define  HEX_REG_P 139 
#define  HEX_REG_PC 138 
#define  HEX_REG_PKTCOUNTHI 137 
#define  HEX_REG_PKTCOUNTLO 136 
#define  HEX_REG_SA0 135 
#define  HEX_REG_SA1 134 
#define  HEX_REG_UGP 133 
#define  HEX_REG_UPCYCLEHI 132 
#define  HEX_REG_UPCYCLELO 131 
#define  HEX_REG_USR 130 
#define  HEX_REG_UTIMERHI 129 
#define  HEX_REG_UTIMERLO 128 

char* hex_get_cntl_reg(int opreg){
	switch (opreg) {
		case HEX_REG_SA0:
			return "SA0";
		case HEX_REG_LC0:
			return "LC0";
		case HEX_REG_SA1:
			return "SA1";
		case HEX_REG_LC1:
			return "LC1";
		case HEX_REG_P:
			return "P";
		case HEX_REG_M0:
			return "M0";
		case HEX_REG_M1:
			return "M1";
		case HEX_REG_USR:
			return "USR";
		case HEX_REG_PC:
			return "PC";
		case HEX_REG_UGP:
			return "UGP";
		case HEX_REG_GP:
			return "GP";
		case HEX_REG_CS0:
			return "CS0";
		case HEX_REG_CS1:
			return "CS1";
		case HEX_REG_UPCYCLELO:
			return "UPCYCLELO";
		case HEX_REG_UPCYCLEHI:
			return "UPCYCLEHI";
		case HEX_REG_FRAMELIMIT:
			return "FRAMELIMIT";
		case HEX_REG_FRAMEKEY:
			return "FRAMEKEY";
		case HEX_REG_PKTCOUNTLO:
			return "PKTCOUNTLO";
		case HEX_REG_PKTCOUNTHI:
			return "PKTCOUNTHI";
		case HEX_REG_UTIMERLO:
			return "UTIMERLO";
		case HEX_REG_UTIMERHI:
			return "UTIMERHI";
		default:
			return "<CRerr>";
	}
}