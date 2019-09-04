#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  signal_stat_timer; } ;
struct TYPE_4__ {int /*<<< orphan*/  pwr_state_check_timer; } ;
struct TYPE_6__ {int /*<<< orphan*/  dynamic_chk_timer; int /*<<< orphan*/  scan_to_timer; int /*<<< orphan*/  assoc_timer; } ;
struct adapter {TYPE_2__ recvpriv; TYPE_1__ pwrctrlpriv; TYPE_3__ mlmepriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  _module_os_intfs_c_ ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtw_hal_sw_led_deinit (struct adapter*) ; 

void rtw_cancel_all_timer(struct adapter *padapter)
{
	RT_TRACE(_module_os_intfs_c_, _drv_info_, ("+rtw_cancel_all_timer\n"));

	del_timer_sync(&padapter->mlmepriv.assoc_timer);
	RT_TRACE(_module_os_intfs_c_, _drv_info_, ("rtw_cancel_all_timer:cancel association timer complete!\n"));

	del_timer_sync(&padapter->mlmepriv.scan_to_timer);
	RT_TRACE(_module_os_intfs_c_, _drv_info_, ("rtw_cancel_all_timer:cancel scan_to_timer!\n"));

	del_timer_sync(&padapter->mlmepriv.dynamic_chk_timer);
	RT_TRACE(_module_os_intfs_c_, _drv_info_, ("rtw_cancel_all_timer:cancel dynamic_chk_timer!\n"));

	/*  cancel sw led timer */
	rtw_hal_sw_led_deinit(padapter);
	RT_TRACE(_module_os_intfs_c_, _drv_info_, ("rtw_cancel_all_timer:cancel DeInitSwLeds!\n"));

	del_timer_sync(&padapter->pwrctrlpriv.pwr_state_check_timer);

	del_timer_sync(&padapter->recvpriv.signal_stat_timer);
}