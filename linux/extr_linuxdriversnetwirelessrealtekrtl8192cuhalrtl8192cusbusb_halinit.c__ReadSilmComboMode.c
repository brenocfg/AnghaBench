#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ BoardType; int VersionID; void* SlimComboDbg; } ;
struct TYPE_7__ {scalar_t__ chip_type; } ;
typedef  TYPE_1__* PADAPTER ;
typedef  TYPE_2__ HAL_DATA_TYPE ;

/* Variables and functions */
 scalar_t__ BOARD_USB_COMBO ; 
 TYPE_2__* GET_HAL_DATA (TYPE_1__*) ; 
 int /*<<< orphan*/  REG_SYS_CFG ; 
 scalar_t__ RTL8188C_8192C ; 
#define  VERSION_NORMAL_TSMC_CHIP_88C 136 
#define  VERSION_NORMAL_TSMC_CHIP_92C 135 
#define  VERSION_NORMAL_TSMC_CHIP_92C_1T2R 134 
#define  VERSION_NORMAL_UMC_CHIP_88C_A_CUT 133 
#define  VERSION_NORMAL_UMC_CHIP_88C_B_CUT 132 
#define  VERSION_NORMAL_UMC_CHIP_92C_1T2R_A_CUT 131 
#define  VERSION_NORMAL_UMC_CHIP_92C_1T2R_B_CUT 130 
#define  VERSION_NORMAL_UMC_CHIP_92C_A_CUT 129 
#define  VERSION_NORMAL_UMC_CHIP_92C_B_CUT 128 
 void* _FALSE ; 
 void* _TRUE ; 
 int rtw_read8 (TYPE_1__*,int /*<<< orphan*/ ) ; 

void _ReadSilmComboMode(PADAPTER Adapter)
{
	HAL_DATA_TYPE	*pHalData = GET_HAL_DATA(Adapter);

	pHalData->SlimComboDbg = _FALSE;	// Default is not debug mode.

	// 2010/11/22 MH We need to enter debug mode for TSMA and UMC A cut
	if ((Adapter->chip_type == RTL8188C_8192C) && 
		(pHalData->BoardType == BOARD_USB_COMBO))
	{			
		switch (pHalData->VersionID)
		{
			case	VERSION_NORMAL_TSMC_CHIP_88C:
			case	VERSION_NORMAL_TSMC_CHIP_92C:
			case	VERSION_NORMAL_TSMC_CHIP_92C_1T2R:
			case	VERSION_NORMAL_UMC_CHIP_88C_A_CUT:
			case	VERSION_NORMAL_UMC_CHIP_92C_A_CUT:
			case	VERSION_NORMAL_UMC_CHIP_92C_1T2R_A_CUT:
				if ((rtw_read8(Adapter, REG_SYS_CFG+3) &0xF0) == 0x20)
					pHalData->SlimComboDbg = _TRUE;
				
				break;

			case	VERSION_NORMAL_UMC_CHIP_88C_B_CUT:
			case	VERSION_NORMAL_UMC_CHIP_92C_B_CUT:
			case	VERSION_NORMAL_UMC_CHIP_92C_1T2R_B_CUT:
				// 2011/02/15 MH UNC-B cut ECO fail, we need to support slim combo debug mode.
				if ((rtw_read8(Adapter, REG_SYS_CFG+3) &0xF0) == 0x20)
					pHalData->SlimComboDbg = _TRUE;
				break;
				
			default:
				break;
		}		
		
	}
	
}