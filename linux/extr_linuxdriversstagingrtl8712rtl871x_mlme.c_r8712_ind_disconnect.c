#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mlme_priv {int /*<<< orphan*/  dhcp_timer; } ;
struct TYPE_6__ {scalar_t__ power_mgnt; int /*<<< orphan*/  smart_ps; } ;
struct TYPE_5__ {scalar_t__ pwr_mode; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* LedControlHandler ) (struct _adapter*,int /*<<< orphan*/ ) ;} ;
struct _adapter {TYPE_3__ registrypriv; TYPE_2__ pwrctrlpriv; TYPE_1__ ledpriv; struct mlme_priv mlmepriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  LED_CTL_NO_LINK ; 
 int /*<<< orphan*/  _FW_LINKED ; 
 int /*<<< orphan*/  _clr_fwstate_ (struct mlme_priv*,int /*<<< orphan*/ ) ; 
 scalar_t__ check_fwstate (struct mlme_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r8712_os_indicate_disconnect (struct _adapter*) ; 
 int /*<<< orphan*/  r8712_set_ps_mode (struct _adapter*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct _adapter*,int /*<<< orphan*/ ) ; 

void r8712_ind_disconnect(struct _adapter *padapter)
{
	struct mlme_priv *pmlmepriv = &padapter->mlmepriv;

	if (check_fwstate(pmlmepriv, _FW_LINKED)) {
		_clr_fwstate_(pmlmepriv, _FW_LINKED);
		padapter->ledpriv.LedControlHandler(padapter, LED_CTL_NO_LINK);
		r8712_os_indicate_disconnect(padapter);
	}
	if (padapter->pwrctrlpriv.pwr_mode !=
	    padapter->registrypriv.power_mgnt) {
		del_timer(&pmlmepriv->dhcp_timer);
		r8712_set_ps_mode(padapter, padapter->registrypriv.power_mgnt,
				  padapter->registrypriv.smart_ps);
	}
}