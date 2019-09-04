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
typedef  int uint ;
struct HAL_VERSION {scalar_t__ ChipType; scalar_t__ VendorType; int CUTVersion; } ;

/* Variables and functions */
 int A_CUT_VERSION ; 
 int B_CUT_VERSION ; 
 scalar_t__ CHIP_VENDOR_TSMC ; 
 int C_CUT_VERSION ; 
 int D_CUT_VERSION ; 
 int E_CUT_VERSION ; 
 scalar_t__ NORMAL_CHIP ; 
 int /*<<< orphan*/  pr_info (char*,char*) ; 
 int sprintf (char*,char*,...) ; 

void dump_chip_info(struct HAL_VERSION	chip_vers)
{
	uint cnt = 0;
	char buf[128];

	cnt += sprintf((buf+cnt), "Chip Version Info: CHIP_8188E_");
	cnt += sprintf((buf+cnt), "%s_", chip_vers.ChipType == NORMAL_CHIP ?
		       "Normal_Chip" : "Test_Chip");
	cnt += sprintf((buf+cnt), "%s_", chip_vers.VendorType == CHIP_VENDOR_TSMC ?
		       "TSMC" : "UMC");
	if (chip_vers.CUTVersion == A_CUT_VERSION)
		cnt += sprintf((buf+cnt), "A_CUT_");
	else if (chip_vers.CUTVersion == B_CUT_VERSION)
		cnt += sprintf((buf+cnt), "B_CUT_");
	else if (chip_vers.CUTVersion == C_CUT_VERSION)
		cnt += sprintf((buf+cnt), "C_CUT_");
	else if (chip_vers.CUTVersion == D_CUT_VERSION)
		cnt += sprintf((buf+cnt), "D_CUT_");
	else if (chip_vers.CUTVersion == E_CUT_VERSION)
		cnt += sprintf((buf+cnt), "E_CUT_");
	else
		cnt += sprintf((buf+cnt), "UNKNOWN_CUT(%d)_",
			       chip_vers.CUTVersion);
	cnt += sprintf((buf+cnt), "1T1R_");
	cnt += sprintf((buf+cnt), "RomVer(0)\n");

	pr_info("%s", buf);
}