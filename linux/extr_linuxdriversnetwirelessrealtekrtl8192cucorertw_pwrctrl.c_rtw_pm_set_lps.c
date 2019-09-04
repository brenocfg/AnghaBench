#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct pwrctrl_priv {scalar_t__ power_mgnt; int LpsIdleCount; int /*<<< orphan*/  bLeisurePs; } ;
struct TYPE_4__ {struct pwrctrl_priv pwrctrlpriv; } ;
typedef  TYPE_1__ _adapter ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  LeaveAllPowerSaveMode (TYPE_1__*) ; 
 scalar_t__ PS_MODE_ACTIVE ; 
 scalar_t__ PS_MODE_NUM ; 
 int /*<<< orphan*/  _FALSE ; 
 int /*<<< orphan*/  _TRUE ; 

int rtw_pm_set_lps(_adapter *padapter, u8 mode)
{
	int	ret = 0;	
	struct pwrctrl_priv *pwrctrlpriv = &padapter->pwrctrlpriv;
	
	if ( mode < PS_MODE_NUM )
	{
		if(pwrctrlpriv->power_mgnt !=mode)
		{
			if(PS_MODE_ACTIVE == mode)
			{
				LeaveAllPowerSaveMode(padapter);
			}
			else
			{
				pwrctrlpriv->LpsIdleCount = 2;
			}
			pwrctrlpriv->power_mgnt = mode;
			pwrctrlpriv->bLeisurePs = (PS_MODE_ACTIVE != pwrctrlpriv->power_mgnt)?_TRUE:_FALSE;
		}
	}
	else
	{
		ret = -EINVAL;
	}

	return ret;
}