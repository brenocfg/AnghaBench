#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct mlme_priv {int dummy; } ;
struct TYPE_8__ {scalar_t__ ips_deny_time; } ;
struct TYPE_9__ {TYPE_1__ pwrctrlpriv; struct mlme_priv mlmepriv; } ;
typedef  TYPE_2__ _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  LED_CTL_NO_LINK ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int WIFI_UNDER_WPS ; 
 int _FW_LINKED ; 
 int _FW_UNDER_LINKING ; 
 int /*<<< orphan*/  _clr_fwstate_ (struct mlme_priv*,int) ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  _module_rtl871x_mlme_c_ ; 
 scalar_t__ check_fwstate (struct mlme_priv*,int) ; 
 int /*<<< orphan*/  rtw_clear_scan_deny (TYPE_2__*) ; 
 scalar_t__ rtw_get_current_time () ; 
 int /*<<< orphan*/  rtw_led_control (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ rtw_ms_to_systime (int) ; 
 int /*<<< orphan*/  rtw_os_indicate_disconnect (TYPE_2__*) ; 
 scalar_t__ rtw_to_roaming (TYPE_2__*) ; 

void rtw_indicate_disconnect( _adapter *padapter )
{
	struct	mlme_priv *pmlmepriv = &padapter->mlmepriv;	

_func_enter_;	
	
	RT_TRACE(_module_rtl871x_mlme_c_, _drv_err_, ("+rtw_indicate_disconnect\n"));

	_clr_fwstate_(pmlmepriv, _FW_UNDER_LINKING|WIFI_UNDER_WPS);

	if(rtw_to_roaming(padapter) > 0)
		_clr_fwstate_(pmlmepriv, _FW_LINKED);

	if(check_fwstate(&padapter->mlmepriv, _FW_LINKED) 
		|| (rtw_to_roaming(padapter) <= 0)
	)
	{
		rtw_os_indicate_disconnect(padapter);

		//set ips_deny_time to avoid enter IPS before LPS leave
		padapter->pwrctrlpriv.ips_deny_time = rtw_get_current_time() + rtw_ms_to_systime(3000);

	      _clr_fwstate_(pmlmepriv, _FW_LINKED);

		rtw_led_control(padapter, LED_CTL_NO_LINK);

		rtw_clear_scan_deny(padapter);

	}

#ifdef CONFIG_P2P_PS
	p2p_ps_wk_cmd(padapter, P2P_PS_DISABLE, 1);
#endif // CONFIG_P2P_PS

#ifdef CONFIG_LPS
#ifdef CONFIG_WOWLAN
	if(padapter->pwrctrlpriv.wowlan_mode==_FALSE)
#endif //CONFIG_WOWLAN
	rtw_lps_ctrl_wk_cmd(padapter, LPS_CTRL_DISCONNECT, 1);

#endif

_func_exit_;	
}