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

int dm_adaptivity_get_parm_str(_adapter *pAdapter, char *buf, int len)
{
#ifdef CONFIG_DM_ADAPTIVITY
	HAL_DATA_TYPE *pHalData = GET_HAL_DATA(pAdapter);
	struct dm_priv *dmpriv = &pHalData->dmpriv;

	return snprintf(buf, len, DM_ADAPTIVITY_VER"\n"
		"TH_L2H_ini\tTH_EDCCA_HL_diff\tIGI_Base\tForceEDCCA\tAdapEn_RSSI\tIGI_LowerBound\n"
		"0x%02x\t%d\t0x%02x\t%d\t%u\t%u\n",
		(u8)dmpriv->TH_L2H_ini,
		dmpriv->TH_EDCCA_HL_diff,
		dmpriv->IGI_Base,
		dmpriv->ForceEDCCA,
		dmpriv->AdapEn_RSSI,
		dmpriv->IGI_LowerBound
	);
#endif /* CONFIG_DM_ADAPTIVITY */
	return 0;
}