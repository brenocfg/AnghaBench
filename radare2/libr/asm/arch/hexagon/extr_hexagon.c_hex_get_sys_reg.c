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
#define  HEX_REG_BADVA 168 
#define  HEX_REG_BADVA0 167 
#define  HEX_REG_BADVA1 166 
#define  HEX_REG_BRKPTCFG0 165 
#define  HEX_REG_BRKPTCFG1 164 
#define  HEX_REG_BRKPTPC0 163 
#define  HEX_REG_BRKPTPC1 162 
#define  HEX_REG_CCR 161 
#define  HEX_REG_CFGBASE 160 
#define  HEX_REG_DIAG 159 
#define  HEX_REG_ELR 158 
#define  HEX_REG_EVB 157 
#define  HEX_REG_HTID 156 
#define  HEX_REG_IAD 155 
#define  HEX_REG_IAHL 154 
#define  HEX_REG_IEL 153 
#define  HEX_REG_IMASK 152 
#define  HEX_REG_IPEND 151 
#define  HEX_REG_ISDBCFG0 150 
#define  HEX_REG_ISDBCFG1 149 
#define  HEX_REG_ISDBEN 148 
#define  HEX_REG_ISDBGPR 147 
#define  HEX_REG_ISDBMBXIN 146 
#define  HEX_REG_ISDBMBXOUT 145 
#define  HEX_REG_ISDBST 144 
#define  HEX_REG_MODECTL 143 
#define  HEX_REG_PCYCLEHI 142 
#define  HEX_REG_PCYCLELO 141 
#define  HEX_REG_PMUCFG 140 
#define  HEX_REG_PMUCNT0 139 
#define  HEX_REG_PMUCNT1 138 
#define  HEX_REG_PMUCNT2 137 
#define  HEX_REG_PMUCNT3 136 
#define  HEX_REG_PMUEVTCFG 135 
#define  HEX_REG_REV 134 
#define  HEX_REG_SGP0 133 
#define  HEX_REG_SGP1 132 
#define  HEX_REG_SSR 131 
#define  HEX_REG_STID 130 
#define  HEX_REG_SYSCFG 129 
#define  HEX_REG_VID 128 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

char* hex_get_sys_reg(int opreg)
{
	static char tmp[5];
	switch (opreg) {
		case HEX_REG_SGP0:
			return "SGP0";
		case HEX_REG_SGP1:
			return "SGP1";
		case HEX_REG_STID:
			return "STID";
		case HEX_REG_ELR:
			return "ELR";
		case HEX_REG_BADVA0:
			return "BADVA0";
		case HEX_REG_BADVA1:
			return "BADVA1";
		case HEX_REG_SSR:
			return "SSR";
		case HEX_REG_CCR:
			return "CCR";
		case HEX_REG_HTID:
			return "HTID";
		case HEX_REG_BADVA:
			return "BADVA";
		case HEX_REG_IMASK:
			return "IMASK";
		case HEX_REG_EVB:
			return "EVB";
		case HEX_REG_MODECTL:
			return "MODECTL";
		case HEX_REG_SYSCFG:
			return "SYSCFG";
		case HEX_REG_IPEND:
			return "IPEND";
		case HEX_REG_VID:
			return "VID";
		case HEX_REG_IAD:
			return "IAD";
		case HEX_REG_IEL:
			return "IEL";
		case HEX_REG_IAHL:
			return "IAHL";
		case HEX_REG_CFGBASE:
			return "CFGBASE";
		case HEX_REG_DIAG:
			return "DIAG";
		case HEX_REG_REV:
			return "REV";
		case HEX_REG_PCYCLELO:
			return "PCYCLELO";
		case HEX_REG_PCYCLEHI:
			return "PCYCLEHI";
		case HEX_REG_ISDBST:
			return "ISDBST";
		case HEX_REG_ISDBCFG0:
			return "ISDBCFG0";
		case HEX_REG_ISDBCFG1:
			return "ISDBCFG1";
		case HEX_REG_BRKPTPC0:
			return "BRKPTPC0";
		case HEX_REG_BRKPTCFG0:
			return "BRKPTCFG0";
		case HEX_REG_BRKPTPC1:
			return "BRKPTPC1";
		case HEX_REG_BRKPTCFG1:
			return "BRKPTCFG1";
		case HEX_REG_ISDBMBXIN:
			return "ISDBMBXIN";
		case HEX_REG_ISDBMBXOUT:
			return "ISDBMBXOUT";
		case HEX_REG_ISDBEN:
			return "ISDBEN";
		case HEX_REG_ISDBGPR:
			return "ISDBGPR";
		case HEX_REG_PMUCNT0:
			return "PMUCNT0";
		case HEX_REG_PMUCNT1:
			return "PMUCNT1";
		case HEX_REG_PMUCNT2:
			return "PMUCNT2";
		case HEX_REG_PMUCNT3:
			return "PMUCNT3";
		case HEX_REG_PMUEVTCFG:
			return "PMUEVTCFG";
		case HEX_REG_PMUCFG:
			return "PMUCFG";
		default:
			sprintf(tmp, "S%d", opreg);
			return tmp;
	}
}