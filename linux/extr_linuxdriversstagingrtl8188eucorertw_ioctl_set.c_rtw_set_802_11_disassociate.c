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
typedef  int u8 ;
struct mlme_priv {int /*<<< orphan*/  lock; } ;
struct adapter {struct mlme_priv mlmepriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _FW_LINKED ; 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  _module_rtl871x_ioctl_set_c_ ; 
 scalar_t__ check_fwstate (struct mlme_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_disassoc_cmd (struct adapter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtw_free_assoc_resources (struct adapter*) ; 
 int /*<<< orphan*/  rtw_indicate_disconnect (struct adapter*) ; 
 int /*<<< orphan*/  rtw_pwr_wakeup (struct adapter*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

u8 rtw_set_802_11_disassociate(struct adapter *padapter)
{
	struct mlme_priv *pmlmepriv = &padapter->mlmepriv;

	spin_lock_bh(&pmlmepriv->lock);

	if (check_fwstate(pmlmepriv, _FW_LINKED)) {
		RT_TRACE(_module_rtl871x_ioctl_set_c_, _drv_info_,
			 ("MgntActrtw_set_802_11_disassociate: rtw_indicate_disconnect\n"));

		rtw_disassoc_cmd(padapter, 0, true);
		rtw_indicate_disconnect(padapter);
		rtw_free_assoc_resources(padapter);
		rtw_pwr_wakeup(padapter);
	}

	spin_unlock_bh(&pmlmepriv->lock);

	return true;
}