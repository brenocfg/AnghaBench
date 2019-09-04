#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct xmit_priv {int dummy; } ;
struct mlme_priv {int /*<<< orphan*/  to_join; } ;
struct TYPE_7__ {struct mlme_priv mlmepriv; struct xmit_priv xmitpriv; } ;
typedef  TYPE_1__ _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  LED_CTL_LINK ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _FALSE ; 
 int /*<<< orphan*/  _FW_LINKED ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  _module_rtl871x_mlme_c_ ; 
 int /*<<< orphan*/  check_fwstate (struct mlme_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_fwstate (struct mlme_priv*) ; 
 int /*<<< orphan*/  rtw_led_control (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_os_indicate_connect (TYPE_1__*) ; 
 int /*<<< orphan*/  rtw_set_roaming (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_set_scan_deny (TYPE_1__*,int) ; 
 int /*<<< orphan*/  set_fwstate (struct mlme_priv*,int /*<<< orphan*/ ) ; 

void rtw_indicate_connect(_adapter *padapter)
{
	struct mlme_priv	*pmlmepriv = &padapter->mlmepriv;
	struct xmit_priv	*pxmitpriv = &padapter->xmitpriv;
	
_func_enter_;

	RT_TRACE(_module_rtl871x_mlme_c_, _drv_err_, ("+rtw_indicate_connect\n"));
 
	pmlmepriv->to_join = _FALSE;

	if(!check_fwstate(&padapter->mlmepriv, _FW_LINKED)) 
	{

#ifdef CONFIG_SW_ANTENNA_DIVERSITY
	rtw_hal_set_hwreg(padapter, HW_VAR_ANTENNA_DIVERSITY_LINK, 0);
#endif
	set_fwstate(pmlmepriv, _FW_LINKED);

	rtw_led_control(padapter, LED_CTL_LINK);

#ifdef CONFIG_DRVEXT_MODULE
	if(padapter->drvextpriv.enable_wpa)
	{
		indicate_l2_connect(padapter);
	}
	else
#endif
	{
		rtw_os_indicate_connect(padapter);
	}

	}

	rtw_set_roaming(padapter, 0);

#ifdef CONFIG_INTEL_WIDI
	if(padapter->mlmepriv.widi_state == INTEL_WIDI_STATE_ROAMING)
	{
		_rtw_memset(pmlmepriv->sa_ext, 0x00, L2SDTA_SERVICE_VE_LEN);
		intel_widi_wk_cmd(padapter, INTEL_WIDI_LISTEN_WK, NULL);
		DBG_871X("change to widi listen\n");
	}
#endif // CONFIG_INTEL_WIDI

	rtw_set_scan_deny(padapter, 3000);

	RT_TRACE(_module_rtl871x_mlme_c_, _drv_err_, ("-rtw_indicate_connect: fw_state=0x%08x\n", get_fwstate(pmlmepriv)));
 
_func_exit_;

}