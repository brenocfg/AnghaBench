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
typedef  scalar_t__ u8 ;
struct TYPE_3__ {int TxPowerTrackControl; } ;
struct TYPE_4__ {int /*<<< orphan*/ * Remnant_OFDMSwingIdx; int /*<<< orphan*/  Remnant_CCKSwingIdx; TYPE_1__ RFCalibrateInfo; } ;
struct hal_com_data {TYPE_2__ odmpriv; } ;
struct adapter {int dummy; } ;
typedef  int /*<<< orphan*/  s8 ;
typedef  TYPE_2__* PDM_ODM_T ;

/* Variables and functions */
 struct hal_com_data* GET_HAL_DATA (struct adapter*) ; 
 scalar_t__ MGN_11M ; 
 scalar_t__ MGN_1M ; 
 scalar_t__ MGN_2M ; 
 scalar_t__ MGN_5_5M ; 

s8 PHY_GetTxPowerTrackingOffset(struct adapter *padapter, u8 RFPath, u8 Rate)
{
	struct hal_com_data *pHalData = GET_HAL_DATA(padapter);
	PDM_ODM_T pDM_Odm = &pHalData->odmpriv;
	s8 offset = 0;

	if (pDM_Odm->RFCalibrateInfo.TxPowerTrackControl  == false)
		return offset;

	if ((Rate == MGN_1M) || (Rate == MGN_2M) || (Rate == MGN_5_5M) || (Rate == MGN_11M)) {
		offset = pDM_Odm->Remnant_CCKSwingIdx;
		/* DBG_871X("+Remnant_CCKSwingIdx = 0x%x\n", RFPath, Rate, pDM_Odm->Remnant_CCKSwingIdx); */
	} else {
		offset = pDM_Odm->Remnant_OFDMSwingIdx[RFPath];
		/* DBG_871X("+Remanant_OFDMSwingIdx[RFPath %u][Rate 0x%x] = 0x%x\n", RFPath, Rate, pDM_Odm->Remnant_OFDMSwingIdx[RFPath]); */

	}

	return offset;
}