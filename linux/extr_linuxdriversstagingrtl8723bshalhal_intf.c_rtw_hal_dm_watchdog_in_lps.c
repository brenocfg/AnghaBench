#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  (* hal_dm_watchdog_in_lps ) (struct adapter*) ;} ;
struct adapter {TYPE_1__ HalFunc; } ;
struct TYPE_4__ {int bFwCurrentInPSMode; } ;

/* Variables and functions */
 TYPE_2__* adapter_to_pwrctl (struct adapter*) ; 
 int /*<<< orphan*/  stub1 (struct adapter*) ; 

void rtw_hal_dm_watchdog_in_lps(struct adapter *padapter)
{
	if (adapter_to_pwrctl(padapter)->bFwCurrentInPSMode == true) {
		if (padapter->HalFunc.hal_dm_watchdog_in_lps)
			padapter->HalFunc.hal_dm_watchdog_in_lps(padapter); /* this fuction caller is in interrupt context */
	}
}