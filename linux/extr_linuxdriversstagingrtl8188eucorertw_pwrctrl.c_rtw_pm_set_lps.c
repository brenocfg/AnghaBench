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
typedef  scalar_t__ u8 ;
struct pwrctrl_priv {scalar_t__ power_mgnt; int LpsIdleCount; int bLeisurePs; } ;
struct adapter {struct pwrctrl_priv pwrctrlpriv; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  LeaveAllPowerSaveMode (struct adapter*) ; 
 scalar_t__ PS_MODE_ACTIVE ; 
 scalar_t__ PS_MODE_NUM ; 

int rtw_pm_set_lps(struct adapter *padapter, u8 mode)
{
	int	ret = 0;
	struct pwrctrl_priv *pwrctrlpriv = &padapter->pwrctrlpriv;

	if (mode < PS_MODE_NUM) {
		if (pwrctrlpriv->power_mgnt != mode) {
			if (mode == PS_MODE_ACTIVE)
				LeaveAllPowerSaveMode(padapter);
			else
				pwrctrlpriv->LpsIdleCount = 2;
			pwrctrlpriv->power_mgnt = mode;
			pwrctrlpriv->bLeisurePs = (pwrctrlpriv->power_mgnt != PS_MODE_ACTIVE) ? true : false;
		}
	} else {
		ret = -EINVAL;
	}

	return ret;
}