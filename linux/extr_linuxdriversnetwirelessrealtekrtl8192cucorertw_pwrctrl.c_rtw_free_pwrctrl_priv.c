#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pwrctrl_priv {int /*<<< orphan*/  lock; } ;
struct TYPE_3__ {struct pwrctrl_priv pwrctrlpriv; } ;
typedef  TYPE_1__* PADAPTER ;

/* Variables and functions */
 int /*<<< orphan*/  _free_pwrlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 

void rtw_free_pwrctrl_priv(PADAPTER adapter)
{
	struct pwrctrl_priv *pwrctrlpriv = &adapter->pwrctrlpriv;

_func_enter_;

	//_rtw_memset((unsigned char *)pwrctrlpriv, 0, sizeof(struct pwrctrl_priv));


	#ifdef CONFIG_RESUME_IN_WORKQUEUE
	if (pwrctrlpriv->rtw_workqueue) { 
		flush_workqueue(pwrctrlpriv->rtw_workqueue);
		destroy_workqueue(pwrctrlpriv->rtw_workqueue);
	}
	#endif


	#if defined(CONFIG_HAS_EARLYSUSPEND) || defined(CONFIG_ANDROID_POWER)
	rtw_unregister_early_suspend(pwrctrlpriv);
	#endif //CONFIG_HAS_EARLYSUSPEND || CONFIG_ANDROID_POWER

	_free_pwrlock(&pwrctrlpriv->lock);

_func_exit_;
}