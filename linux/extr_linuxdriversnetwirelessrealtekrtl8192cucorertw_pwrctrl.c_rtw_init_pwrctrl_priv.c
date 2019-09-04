#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pwrctrl_priv {scalar_t__ power_mgnt; int tog; scalar_t__ smart_ps; scalar_t__ pwr_mode; int /*<<< orphan*/  cpwm; void* bFwCurrentInPSMode; void* bLeisurePs; scalar_t__ LpsIdleCount; void* bkeepfwalive; void* bInSuspend; void* bInternalAutoSuspend; scalar_t__ pwr_state_check_cnts; int /*<<< orphan*/  pwr_state_check_interval; int /*<<< orphan*/  ips_mode_req; int /*<<< orphan*/  ips_mode; scalar_t__ ips_leave_cnts; scalar_t__ ips_enter_cnts; int /*<<< orphan*/  rf_pwrstate; int /*<<< orphan*/  lock; } ;
struct TYPE_4__ {scalar_t__ power_mgnt; int /*<<< orphan*/  ips_mode; } ;
struct TYPE_5__ {TYPE_1__ registrypriv; struct pwrctrl_priv pwrctrlpriv; } ;
typedef  TYPE_2__* PADAPTER ;

/* Variables and functions */
 scalar_t__ PS_MODE_ACTIVE ; 
 int /*<<< orphan*/  PS_STATE_S4 ; 
 int /*<<< orphan*/  RTW_PWR_STATE_CHK_INTERVAL ; 
 void* _FALSE ; 
 void* _TRUE ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  _init_pwrlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rf_on ; 

void rtw_init_pwrctrl_priv(PADAPTER padapter)
{
	struct pwrctrl_priv *pwrctrlpriv = &padapter->pwrctrlpriv;

_func_enter_;

#ifdef PLATFORM_WINDOWS
	pwrctrlpriv->pnp_current_pwr_state=NdisDeviceStateD0;
#endif

	_init_pwrlock(&pwrctrlpriv->lock);
	pwrctrlpriv->rf_pwrstate = rf_on;
	pwrctrlpriv->ips_enter_cnts=0;
	pwrctrlpriv->ips_leave_cnts=0;

	pwrctrlpriv->ips_mode = padapter->registrypriv.ips_mode;
	pwrctrlpriv->ips_mode_req = padapter->registrypriv.ips_mode;

	pwrctrlpriv->pwr_state_check_interval = RTW_PWR_STATE_CHK_INTERVAL;
	pwrctrlpriv->pwr_state_check_cnts = 0;
	pwrctrlpriv->bInternalAutoSuspend = _FALSE;
	pwrctrlpriv->bInSuspend = _FALSE;
	pwrctrlpriv->bkeepfwalive = _FALSE;

#ifdef CONFIG_AUTOSUSPEND
#ifdef SUPPORT_HW_RFOFF_DETECTED
	pwrctrlpriv->pwr_state_check_interval = (pwrctrlpriv->bHWPwrPindetect) ?1000:2000;		
#endif
#endif

	pwrctrlpriv->LpsIdleCount = 0;
	//pwrctrlpriv->FWCtrlPSMode =padapter->registrypriv.power_mgnt;// PS_MODE_MIN;
	pwrctrlpriv->power_mgnt =padapter->registrypriv.power_mgnt;// PS_MODE_MIN;
	pwrctrlpriv->bLeisurePs = (PS_MODE_ACTIVE != pwrctrlpriv->power_mgnt)?_TRUE:_FALSE;

	pwrctrlpriv->bFwCurrentInPSMode = _FALSE;

	pwrctrlpriv->cpwm = PS_STATE_S4;

	pwrctrlpriv->pwr_mode = PS_MODE_ACTIVE;


	pwrctrlpriv->smart_ps = 0;

	pwrctrlpriv->tog = 0x80;

#ifdef PLATFORM_LINUX
#if LINUX_VERSION_CODE < KERNEL_VERSION(4, 15, 0)
	_init_timer(&(pwrctrlpriv->pwr_state_check_timer), padapter->pnetdev, pwr_state_check_handler, (u8 *)padapter);
#else
	timer_setup(&pwrctrlpriv->pwr_state_check_timer, pwr_state_check_handler, 0);
#endif
#endif

	#ifdef CONFIG_RESUME_IN_WORKQUEUE
	_init_workitem(&pwrctrlpriv->resume_work, resume_workitem_callback, NULL);
	pwrctrlpriv->rtw_workqueue = create_singlethread_workqueue("rtw_workqueue");
	#endif //CONFIG_RESUME_IN_WORKQUEUE

	#if defined(CONFIG_HAS_EARLYSUSPEND) || defined(CONFIG_ANDROID_POWER)
	pwrctrlpriv->early_suspend.suspend = NULL;
	rtw_register_early_suspend(pwrctrlpriv);
	#endif //CONFIG_HAS_EARLYSUSPEND || CONFIG_ANDROID_POWER


_func_exit_;

}