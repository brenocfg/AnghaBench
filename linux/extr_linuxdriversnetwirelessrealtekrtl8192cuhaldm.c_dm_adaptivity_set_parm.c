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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  s8 ;
typedef  int /*<<< orphan*/  _adapter ;

/* Variables and functions */

void dm_adaptivity_set_parm(_adapter *pAdapter, s8 TH_L2H_ini, s8 TH_EDCCA_HL_diff,
	s8 IGI_Base, bool ForceEDCCA, u8 AdapEn_RSSI, u8 IGI_LowerBound)
{
#ifdef CONFIG_DM_ADAPTIVITY
	HAL_DATA_TYPE *pHalData = GET_HAL_DATA(pAdapter);
	struct dm_priv *dmpriv = &pHalData->dmpriv;

	dmpriv->TH_L2H_ini = TH_L2H_ini;
	dmpriv->TH_EDCCA_HL_diff = TH_EDCCA_HL_diff;
	dmpriv->IGI_Base = IGI_Base;
	dmpriv->ForceEDCCA = ForceEDCCA;
	dmpriv->AdapEn_RSSI = AdapEn_RSSI;
	dmpriv->IGI_LowerBound = IGI_LowerBound;

#endif /* CONFIG_DM_ADAPTIVITY */
}