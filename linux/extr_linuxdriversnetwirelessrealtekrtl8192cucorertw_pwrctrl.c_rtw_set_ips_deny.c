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
typedef  int /*<<< orphan*/  u32 ;
struct pwrctrl_priv {scalar_t__ ips_deny_time; } ;
struct TYPE_3__ {struct pwrctrl_priv pwrctrlpriv; } ;
typedef  TYPE_1__ _adapter ;

/* Variables and functions */
 scalar_t__ rtw_get_current_time () ; 
 scalar_t__ rtw_ms_to_systime (int /*<<< orphan*/ ) ; 

inline void rtw_set_ips_deny(_adapter *padapter, u32 ms)
{
	struct pwrctrl_priv *pwrpriv = &padapter->pwrctrlpriv;
	pwrpriv->ips_deny_time = rtw_get_current_time() + rtw_ms_to_systime(ms);
}