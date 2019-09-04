#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  size_t u32 ;
struct TYPE_3__ {int /*<<< orphan*/  Adapter; } ;
struct hal_com_data {TYPE_1__ odmpriv; } ;
struct adapter {int dummy; } ;
typedef  TYPE_1__* PDM_ODM_T ;

/* Variables and functions */
 size_t BIT3 ; 
 size_t BIT5 ; 
 struct hal_com_data* GET_HAL_DATA (struct adapter*) ; 
 int IQK_MAC_REG_NUM ; 
 int /*<<< orphan*/  ODM_COMP_CALIBRATION ; 
 int /*<<< orphan*/  ODM_DBG_LOUD ; 
 int /*<<< orphan*/  ODM_RT_TRACE (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rtw_write8 (int /*<<< orphan*/ ,size_t,int) ; 

__attribute__((used)) static void _PHY_MACSettingCalibration8723B(
	struct adapter *padapter, u32 *MACReg, u32 *MACBackup
)
{
	u32 i = 0;
	struct hal_com_data	*pHalData = GET_HAL_DATA(padapter);
	PDM_ODM_T pDM_Odm = &pHalData->odmpriv;

	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("MAC settings for Calibration.\n"));

	rtw_write8(pDM_Odm->Adapter, MACReg[i], 0x3F);

	for (i = 1 ; i < (IQK_MAC_REG_NUM - 1); i++) {
		rtw_write8(pDM_Odm->Adapter, MACReg[i], (u8)(MACBackup[i]&(~BIT3)));
	}
	rtw_write8(pDM_Odm->Adapter, MACReg[i], (u8)(MACBackup[i]&(~BIT5)));

}