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
struct pwrctrl_priv {int bips_processing; scalar_t__ ips_mode; scalar_t__ ips_mode_req; scalar_t__ change_rfpwrstate; int bpower_saving; int bkeepfwalive; scalar_t__ rf_pwrstate; int /*<<< orphan*/  ips_enter_cnts; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_871X (char*,...) ; 
 scalar_t__ IPS_LEVEL_2 ; 
 struct pwrctrl_priv* adapter_to_pwrctl (struct adapter*) ; 
 scalar_t__ rf_off ; 
 int /*<<< orphan*/  rtw_ips_pwr_down (struct adapter*) ; 

void _ips_enter(struct adapter *padapter)
{
	struct pwrctrl_priv *pwrpriv = adapter_to_pwrctl(padapter);

	pwrpriv->bips_processing = true;

	/*  syn ips_mode with request */
	pwrpriv->ips_mode = pwrpriv->ips_mode_req;

	pwrpriv->ips_enter_cnts++;
	DBG_871X("==>ips_enter cnts:%d\n", pwrpriv->ips_enter_cnts);

	if (rf_off == pwrpriv->change_rfpwrstate) {
		pwrpriv->bpower_saving = true;
		DBG_871X("nolinked power save enter\n");

		if (pwrpriv->ips_mode == IPS_LEVEL_2)
			pwrpriv->bkeepfwalive = true;

		rtw_ips_pwr_down(padapter);
		pwrpriv->rf_pwrstate = rf_off;
	}
	pwrpriv->bips_processing = false;

}