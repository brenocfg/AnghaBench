#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_3__ {scalar_t__ RxIdleAnt; } ;
struct TYPE_4__ {TYPE_1__ DM_FatTable; } ;
struct hal_com_data {int /*<<< orphan*/  ant_path; scalar_t__ AntDivCfg; TYPE_2__ odmpriv; } ;
struct adapter {int dummy; } ;
typedef  TYPE_1__* pFAT_T ;
typedef  TYPE_2__* PDM_ODM_T ;

/* Variables and functions */
 struct hal_com_data* GET_HAL_DATA (struct adapter*) ; 
 scalar_t__ MAIN_ANT ; 
 int /*<<< orphan*/  ODM_RF_PATH_A ; 
 int /*<<< orphan*/  ODM_RF_PATH_B ; 
 int /*<<< orphan*/  PHY_SetTxPowerLevelByPath (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  _module_hal_init_c_ ; 

void PHY_SetTxPowerLevel8723B(struct adapter *Adapter, u8 Channel)
{
	struct hal_com_data *pHalData = GET_HAL_DATA(Adapter);
	PDM_ODM_T pDM_Odm = &pHalData->odmpriv;
	pFAT_T pDM_FatTable = &pDM_Odm->DM_FatTable;
	u8 RFPath = ODM_RF_PATH_A;

	if (pHalData->AntDivCfg) {/*  antenna diversity Enable */
		RFPath = ((pDM_FatTable->RxIdleAnt == MAIN_ANT) ? ODM_RF_PATH_A : ODM_RF_PATH_B);
	} else { /*  antenna diversity disable */
		RFPath = pHalData->ant_path;
	}

	RT_TRACE(_module_hal_init_c_, _drv_info_, ("==>PHY_SetTxPowerLevel8723B()\n"));

	PHY_SetTxPowerLevelByPath(Adapter, Channel, RFPath);

	RT_TRACE(_module_hal_init_c_, _drv_info_, ("<==PHY_SetTxPowerLevel8723B()\n"));
}