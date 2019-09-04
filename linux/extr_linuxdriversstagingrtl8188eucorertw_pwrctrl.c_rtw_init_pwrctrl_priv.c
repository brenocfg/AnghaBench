#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pwrctrl_priv {int bips_processing; int bInternalAutoSuspend; int bInSuspend; int bkeepfwalive; scalar_t__ power_mgnt; int bLeisurePs; int bFwCurrentInPSMode; int tog; int btcoex_rfon; int /*<<< orphan*/  pwr_state_check_timer; scalar_t__ bcn_ant_mode; int /*<<< orphan*/  smart_ps; scalar_t__ pwr_mode; int /*<<< orphan*/  cpwm; scalar_t__ rpwm; scalar_t__ LpsIdleCount; scalar_t__ pwr_state_check_cnts; int /*<<< orphan*/  pwr_state_check_interval; int /*<<< orphan*/  ips_mode_req; int /*<<< orphan*/  ips_mode; scalar_t__ ips_leave_cnts; scalar_t__ ips_enter_cnts; int /*<<< orphan*/  rf_pwrstate; int /*<<< orphan*/  mutex_lock; } ;
struct TYPE_2__ {int mp_mode; scalar_t__ power_mgnt; int /*<<< orphan*/  smart_ps; int /*<<< orphan*/  ips_mode; } ;
struct adapter {TYPE_1__ registrypriv; struct pwrctrl_priv pwrctrlpriv; } ;

/* Variables and functions */
 scalar_t__ PS_MODE_ACTIVE ; 
 int /*<<< orphan*/  PS_STATE_S4 ; 
 int /*<<< orphan*/  RTW_PWR_STATE_CHK_INTERVAL ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pwr_state_check_handler ; 
 int /*<<< orphan*/  rf_on ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void rtw_init_pwrctrl_priv(struct adapter *padapter)
{
	struct pwrctrl_priv *pwrctrlpriv = &padapter->pwrctrlpriv;

	mutex_init(&pwrctrlpriv->mutex_lock);
	pwrctrlpriv->rf_pwrstate = rf_on;
	pwrctrlpriv->ips_enter_cnts = 0;
	pwrctrlpriv->ips_leave_cnts = 0;
	pwrctrlpriv->bips_processing = false;

	pwrctrlpriv->ips_mode = padapter->registrypriv.ips_mode;
	pwrctrlpriv->ips_mode_req = padapter->registrypriv.ips_mode;

	pwrctrlpriv->pwr_state_check_interval = RTW_PWR_STATE_CHK_INTERVAL;
	pwrctrlpriv->pwr_state_check_cnts = 0;
	pwrctrlpriv->bInternalAutoSuspend = false;
	pwrctrlpriv->bInSuspend = false;
	pwrctrlpriv->bkeepfwalive = false;

	pwrctrlpriv->LpsIdleCount = 0;
	if (padapter->registrypriv.mp_mode == 1)
		pwrctrlpriv->power_mgnt = PS_MODE_ACTIVE;
	else
		pwrctrlpriv->power_mgnt = padapter->registrypriv.power_mgnt;/*  PS_MODE_MIN; */
	pwrctrlpriv->bLeisurePs = (pwrctrlpriv->power_mgnt != PS_MODE_ACTIVE) ? true : false;

	pwrctrlpriv->bFwCurrentInPSMode = false;

	pwrctrlpriv->rpwm = 0;
	pwrctrlpriv->cpwm = PS_STATE_S4;

	pwrctrlpriv->pwr_mode = PS_MODE_ACTIVE;
	pwrctrlpriv->smart_ps = padapter->registrypriv.smart_ps;
	pwrctrlpriv->bcn_ant_mode = 0;

	pwrctrlpriv->tog = 0x80;

	pwrctrlpriv->btcoex_rfon = false;

	timer_setup(&pwrctrlpriv->pwr_state_check_timer,
		    pwr_state_check_handler, 0);
}