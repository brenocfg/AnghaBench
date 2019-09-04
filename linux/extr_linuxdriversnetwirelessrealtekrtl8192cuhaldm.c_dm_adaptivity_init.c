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
typedef  int /*<<< orphan*/  _adapter ;

/* Variables and functions */

void dm_adaptivity_init(_adapter *pAdapter)
{
#ifdef CONFIG_DM_ADAPTIVITY
	HAL_DATA_TYPE *pHalData = GET_HAL_DATA(pAdapter);
	struct dm_priv *dmpriv = &pHalData->dmpriv;

	/*
	if(pDM_Odm->SupportICType == ODM_RTL8723B)
	{
		pDM_Odm->TH_L2H_ini = 0xf8; // -8
	}
	if((pDM_Odm->SupportICType == ODM_RTL8192E)&&(pDM_Odm->SupportInterface == ODM_ITRF_PCIE))
	{
		pDM_Odm->TH_L2H_ini = 0xf0; // -16
	}
	else */
	{
		dmpriv->TH_L2H_ini = 0xf9; // -7
	}

	dmpriv->TH_EDCCA_HL_diff = 7;
	dmpriv->IGI_Base = 0x32;
	dmpriv->IGI_target = 0x1c;
	dmpriv->ForceEDCCA = 0;
	dmpriv->AdapEn_RSSI = 20;
	dmpriv->IGI_LowerBound = 0;

	//Reg524[11]=0 is easily to transmit packets during adaptivity test
	PHY_SetBBReg(pAdapter, 0x524, BIT11, 1); // stop counting if EDCCA is asserted

#endif /* CONFIG_DM_ADAPTIVITY */
}