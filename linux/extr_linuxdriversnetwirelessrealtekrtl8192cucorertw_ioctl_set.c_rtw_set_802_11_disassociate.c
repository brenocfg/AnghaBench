#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct mlme_priv {int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  _irqL ;
struct TYPE_6__ {struct mlme_priv mlmepriv; } ;
typedef  TYPE_1__ _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _FW_LINKED ; 
 scalar_t__ _TRUE ; 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  _enter_critical_bh (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _exit_critical_bh (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  _module_rtl871x_ioctl_set_c_ ; 
 scalar_t__ check_fwstate (struct mlme_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_disassoc_cmd (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  rtw_free_assoc_resources_cmd (TYPE_1__*) ; 
 int /*<<< orphan*/  rtw_indicate_disconnect (TYPE_1__*) ; 

u8 rtw_set_802_11_disassociate(_adapter *padapter)
{
	_irqL irqL;
	struct mlme_priv * pmlmepriv = &padapter->mlmepriv;

_func_enter_;

	_enter_critical_bh(&pmlmepriv->lock, &irqL);

	if (check_fwstate(pmlmepriv, _FW_LINKED) == _TRUE)
	{
		RT_TRACE(_module_rtl871x_ioctl_set_c_,_drv_info_,("MgntActrtw_set_802_11_disassociate: rtw_indicate_disconnect\n"));

		rtw_disassoc_cmd(padapter, 0, _TRUE);
		rtw_indicate_disconnect(padapter);
		//modify for CONFIG_IEEE80211W, none 11w can use it
		rtw_free_assoc_resources_cmd(padapter);
	}

	_exit_critical_bh(&pmlmepriv->lock, &irqL);
	
_func_exit_;

	return _TRUE;	
}