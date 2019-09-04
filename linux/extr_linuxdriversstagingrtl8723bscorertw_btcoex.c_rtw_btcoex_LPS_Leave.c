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
struct pwrctrl_priv {scalar_t__ pwr_mode; int bpower_saving; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LPS_RF_ON_check (struct adapter*,int) ; 
 scalar_t__ PS_MODE_ACTIVE ; 
 struct pwrctrl_priv* adapter_to_pwrctl (struct adapter*) ; 
 int /*<<< orphan*/  rtw_set_ps_mode (struct adapter*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

void rtw_btcoex_LPS_Leave(struct adapter *padapter)
{
	struct pwrctrl_priv *pwrpriv;


	pwrpriv = adapter_to_pwrctl(padapter);

	if (pwrpriv->pwr_mode != PS_MODE_ACTIVE) {
		rtw_set_ps_mode(padapter, PS_MODE_ACTIVE, 0, 0, "BTCOEX");
		LPS_RF_ON_check(padapter, 100);
		pwrpriv->bpower_saving = false;
	}
}