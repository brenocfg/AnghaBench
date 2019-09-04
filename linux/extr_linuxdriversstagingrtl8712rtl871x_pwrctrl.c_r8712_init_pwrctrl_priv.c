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
struct pwrctrl_priv {int tog; int /*<<< orphan*/  rpwm_check_timer; int /*<<< orphan*/  rpwm_workitem; int /*<<< orphan*/  SetPSModeWorkItem; scalar_t__ smart_ps; int /*<<< orphan*/  pwr_mode; int /*<<< orphan*/  cpwm; int /*<<< orphan*/  mutex_lock; } ;
struct _adapter {struct pwrctrl_priv pwrctrlpriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PS_MODE_ACTIVE ; 
 int /*<<< orphan*/  PS_STATE_S4 ; 
 int /*<<< orphan*/  SetPSModeWorkItemCallback ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r8712_write8 (struct _adapter*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpwm_check_handler ; 
 int /*<<< orphan*/  rpwm_workitem_callback ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void r8712_init_pwrctrl_priv(struct _adapter *padapter)
{
	struct pwrctrl_priv *pwrctrlpriv = &padapter->pwrctrlpriv;

	memset((unsigned char *)pwrctrlpriv, 0, sizeof(struct pwrctrl_priv));
	mutex_init(&pwrctrlpriv->mutex_lock);
	pwrctrlpriv->cpwm = PS_STATE_S4;
	pwrctrlpriv->pwr_mode = PS_MODE_ACTIVE;
	pwrctrlpriv->smart_ps = 0;
	pwrctrlpriv->tog = 0x80;
/* clear RPWM to ensure driver and fw back to initial state. */
	r8712_write8(padapter, 0x1025FE58, 0);
	INIT_WORK(&pwrctrlpriv->SetPSModeWorkItem, SetPSModeWorkItemCallback);
	INIT_WORK(&pwrctrlpriv->rpwm_workitem, rpwm_workitem_callback);
	timer_setup(&pwrctrlpriv->rpwm_check_timer, rpwm_check_handler, 0);
}