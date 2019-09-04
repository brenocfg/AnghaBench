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
struct pwrctrl_priv {scalar_t__ cpwm; scalar_t__ pwr_mode; scalar_t__ alives; int /*<<< orphan*/  mutex_lock; } ;
struct _adapter {int /*<<< orphan*/  mlmepriv; struct pwrctrl_priv pwrctrlpriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_ALIVE ; 
 scalar_t__ PS_MODE_ACTIVE ; 
 int /*<<< orphan*/  PS_STATE_S0 ; 
 scalar_t__ PS_STATE_S2 ; 
 int /*<<< orphan*/  _FW_UNDER_LINKING ; 
 int check_fwstate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r8712_set_rpwm (struct _adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_task_alive (struct pwrctrl_priv*,int /*<<< orphan*/ ) ; 

void r8712_unregister_cmd_alive(struct _adapter *padapter)
{
	struct pwrctrl_priv *pwrctrl = &padapter->pwrctrlpriv;

	mutex_lock(&pwrctrl->mutex_lock);
	unregister_task_alive(pwrctrl, CMD_ALIVE);
	if ((pwrctrl->cpwm > PS_STATE_S2) &&
	   (pwrctrl->pwr_mode > PS_MODE_ACTIVE)) {
		if ((pwrctrl->alives == 0) &&
		    (check_fwstate(&padapter->mlmepriv,
		     _FW_UNDER_LINKING) != true)) {
			r8712_set_rpwm(padapter, PS_STATE_S0);
		}
	}
	mutex_unlock(&pwrctrl->mutex_lock);
}