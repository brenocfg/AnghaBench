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
struct mlme_priv {int dummy; } ;
struct adapter {struct mlme_priv mlmepriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  LPS_CTRL_DISCONNECT ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int WIFI_UNDER_WPS ; 
 int _FW_LINKED ; 
 int _FW_UNDER_LINKING ; 
 int /*<<< orphan*/  _clr_fwstate_ (struct mlme_priv*,int) ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _module_rtl871x_mlme_c_ ; 
 scalar_t__ check_fwstate (struct mlme_priv*,int) ; 
 int /*<<< orphan*/  rtw_clear_scan_deny (struct adapter*) ; 
 int /*<<< orphan*/  rtw_lps_ctrl_wk_cmd (struct adapter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtw_os_indicate_disconnect (struct adapter*) ; 
 int /*<<< orphan*/  rtw_set_ips_deny (struct adapter*,int) ; 
 scalar_t__ rtw_to_roam (struct adapter*) ; 

void rtw_indicate_disconnect(struct adapter *padapter)
{
	struct	mlme_priv *pmlmepriv = &padapter->mlmepriv;

	RT_TRACE(_module_rtl871x_mlme_c_, _drv_err_, ("+rtw_indicate_disconnect\n"));

	_clr_fwstate_(pmlmepriv, _FW_UNDER_LINKING|WIFI_UNDER_WPS);

	/* DBG_871X("clear wps when %s\n", __func__); */

	if (rtw_to_roam(padapter) > 0)
		_clr_fwstate_(pmlmepriv, _FW_LINKED);

	if (check_fwstate(&padapter->mlmepriv, _FW_LINKED)
		|| (rtw_to_roam(padapter) <= 0)
	) {
		rtw_os_indicate_disconnect(padapter);

		/* set ips_deny_time to avoid enter IPS before LPS leave */
		rtw_set_ips_deny(padapter, 3000);

		_clr_fwstate_(pmlmepriv, _FW_LINKED);

		rtw_clear_scan_deny(padapter);
	}

	rtw_lps_ctrl_wk_cmd(padapter, LPS_CTRL_DISCONNECT, 1);
}