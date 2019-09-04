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
typedef  int u32 ;
typedef  int /*<<< orphan*/  PDM_ODM_T ;

/* Variables and functions */
 int /*<<< orphan*/  ODM_COMP_INIT ; 
 int /*<<< orphan*/  ODM_DBG_TRACE ; 
 int /*<<< orphan*/  ODM_RF_PATH_A ; 
 int /*<<< orphan*/  ODM_RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  odm_ConfigRFReg_8723B (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int) ; 

void odm_ConfigRF_RadioA_8723B(PDM_ODM_T pDM_Odm, u32 Addr, u32 Data)
{
	u32  content = 0x1000; /*  RF_Content: radioa_txt */
	u32 maskforPhySet = (u32)(content&0xE000);

	odm_ConfigRFReg_8723B(
		pDM_Odm,
		Addr,
		Data,
		ODM_RF_PATH_A,
		Addr|maskforPhySet
	);

	ODM_RT_TRACE(
		pDM_Odm,
		ODM_COMP_INIT,
		ODM_DBG_TRACE,
		(
			"===> ODM_ConfigRFWithHeaderFile: [RadioA] %08X %08X\n",
			Addr,
			Data
		)
	);
}