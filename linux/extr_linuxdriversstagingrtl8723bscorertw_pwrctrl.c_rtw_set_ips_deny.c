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
typedef  int /*<<< orphan*/  u32 ;
struct pwrctrl_priv {scalar_t__ ips_deny_time; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 struct pwrctrl_priv* adapter_to_pwrctl (struct adapter*) ; 
 scalar_t__ jiffies ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 

inline void rtw_set_ips_deny(struct adapter *padapter, u32 ms)
{
	struct pwrctrl_priv *pwrpriv = adapter_to_pwrctl(padapter);
	pwrpriv->ips_deny_time = jiffies + msecs_to_jiffies(ms);
}