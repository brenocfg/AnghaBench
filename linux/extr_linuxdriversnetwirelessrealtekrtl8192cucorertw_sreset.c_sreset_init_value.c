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

void sreset_init_value(_adapter *padapter)
{
#if defined(DBG_CONFIG_ERROR_DETECT)
	HAL_DATA_TYPE	*pHalData = GET_HAL_DATA(padapter);
	struct sreset_priv *psrtpriv = &pHalData->srestpriv;

	_rtw_mutex_init(&psrtpriv->silentreset_mutex);
	psrtpriv->silent_reset_inprogress = _FALSE;
	psrtpriv->Wifi_Error_Status = WIFI_STATUS_SUCCESS;
	psrtpriv->last_tx_time =0;
	psrtpriv->last_tx_complete_time =0;
#endif
}