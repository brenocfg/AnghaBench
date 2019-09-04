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
struct reportpwrstate_parm {int state; } ;
struct pwrctrl_priv {int cpwm_tog; int cpwm; int alives; int /*<<< orphan*/  mutex_lock; int /*<<< orphan*/  rpwm_check_timer; } ;
struct cmd_priv {int /*<<< orphan*/  cmd_queue_comp; } ;
struct _adapter {struct pwrctrl_priv pwrctrlpriv; struct cmd_priv cmdpriv; } ;

/* Variables and functions */
 int CMD_ALIVE ; 
 int PS_STATE_S2 ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void r8712_cpwm_int_hdl(struct _adapter *padapter,
			struct reportpwrstate_parm *preportpwrstate)
{
	struct pwrctrl_priv *pwrpriv = &(padapter->pwrctrlpriv);
	struct cmd_priv	*pcmdpriv = &(padapter->cmdpriv);

	if (pwrpriv->cpwm_tog == ((preportpwrstate->state) & 0x80))
		return;
	del_timer(&padapter->pwrctrlpriv.rpwm_check_timer);
	mutex_lock(&pwrpriv->mutex_lock);
	pwrpriv->cpwm = (preportpwrstate->state) & 0xf;
	if (pwrpriv->cpwm >= PS_STATE_S2) {
		if (pwrpriv->alives & CMD_ALIVE)
			complete(&(pcmdpriv->cmd_queue_comp));
	}
	pwrpriv->cpwm_tog = (preportpwrstate->state) & 0x80;
	mutex_unlock(&pwrpriv->mutex_lock);
}