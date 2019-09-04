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
struct timer_list {int dummy; } ;
struct pwrctrl_priv {struct adapter* adapter; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 struct pwrctrl_priv* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pwr_state_check_timer ; 
 struct pwrctrl_priv* pwrctrlpriv ; 
 int /*<<< orphan*/  rtw_ps_cmd (struct adapter*) ; 

__attribute__((used)) static void pwr_state_check_handler(struct timer_list *t)
{
	struct pwrctrl_priv *pwrctrlpriv =
		from_timer(pwrctrlpriv, t, pwr_state_check_timer);
	struct adapter *padapter = pwrctrlpriv->adapter;

	rtw_ps_cmd(padapter);
}