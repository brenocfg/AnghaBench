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

void sreset_reset(_adapter *padapter)
{
#ifdef DBG_CONFIG_ERROR_RESET
	HAL_DATA_TYPE	*pHalData = GET_HAL_DATA(padapter);
	struct sreset_priv *psrtpriv = &pHalData->srestpriv;
	struct pwrctrl_priv *pwrpriv = &padapter->pwrctrlpriv;
	struct mlme_priv	*pmlmepriv = &(padapter->mlmepriv);
	struct xmit_priv	*pxmitpriv = &padapter->xmitpriv;
	_irqL irqL;
	u32 start = rtw_get_current_time();

	DBG_871X("%s\n", __FUNCTION__);

	psrtpriv->Wifi_Error_Status = WIFI_STATUS_SUCCESS;

	_enter_pwrlock(&pwrpriv->lock);

	psrtpriv->silent_reset_inprogress = _TRUE;
	pwrpriv->change_rfpwrstate = rf_off;

	sreset_stop_adapter(padapter);
	#ifdef CONFIG_CONCURRENT_MODE
	sreset_stop_adapter(padapter->pbuddy_adapter);
	#endif

	#ifdef CONFIG_IPS
	_ips_enter(padapter);
	_ips_leave(padapter);
	#endif

	sreset_start_adapter(padapter);
	#ifdef CONFIG_CONCURRENT_MODE
	sreset_start_adapter(padapter->pbuddy_adapter);
	#endif

	psrtpriv->silent_reset_inprogress = _FALSE;

	_exit_pwrlock(&pwrpriv->lock);

	DBG_871X("%s done in %d ms\n", __FUNCTION__, rtw_get_passing_time_ms(start));
#endif
}