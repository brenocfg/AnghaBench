#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  pwr_state_check_timer; } ;
struct TYPE_8__ {int /*<<< orphan*/  dynamic_chk_timer; int /*<<< orphan*/  scan_to_timer; int /*<<< orphan*/  assoc_timer; } ;
struct TYPE_9__ {TYPE_1__ pwrctrlpriv; TYPE_2__ mlmepriv; } ;
typedef  TYPE_3__ _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _cancel_timer_ex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  _module_os_intfs_c_ ; 
 int /*<<< orphan*/  rtw_hal_dm_deinit (TYPE_3__*) ; 
 int /*<<< orphan*/  rtw_hal_sw_led_deinit (TYPE_3__*) ; 

void rtw_cancel_all_timer(_adapter *padapter)
{
	RT_TRACE(_module_os_intfs_c_,_drv_info_,("+rtw_cancel_all_timer\n"));

	_cancel_timer_ex(&padapter->mlmepriv.assoc_timer);
	RT_TRACE(_module_os_intfs_c_,_drv_info_,("rtw_cancel_all_timer:cancel association timer complete! \n"));

	//_cancel_timer_ex(&padapter->securitypriv.tkip_timer);
	//RT_TRACE(_module_os_intfs_c_,_drv_info_,("rtw_cancel_all_timer:cancel tkip_timer! \n"));

	_cancel_timer_ex(&padapter->mlmepriv.scan_to_timer);
	RT_TRACE(_module_os_intfs_c_,_drv_info_,("rtw_cancel_all_timer:cancel scan_to_timer! \n"));

	_cancel_timer_ex(&padapter->mlmepriv.dynamic_chk_timer);
	RT_TRACE(_module_os_intfs_c_,_drv_info_,("rtw_cancel_all_timer:cancel dynamic_chk_timer! \n"));

	// cancel sw led timer
	rtw_hal_sw_led_deinit(padapter);
	RT_TRACE(_module_os_intfs_c_,_drv_info_,("rtw_cancel_all_timer:cancel DeInitSwLeds! \n"));

	_cancel_timer_ex(&padapter->pwrctrlpriv.pwr_state_check_timer);

#ifdef CONFIG_IOCTL_CFG80211
#ifdef CONFIG_P2P
	_cancel_timer_ex(&padapter->cfg80211_wdinfo.remain_on_ch_timer);
#endif //CONFIG_P2P
#endif //CONFIG_IOCTL_CFG80211

#ifdef CONFIG_SET_SCAN_DENY_TIMER
	_cancel_timer_ex(&padapter->mlmepriv.set_scan_deny_timer);
	rtw_clear_scan_deny(padapter);
	RT_TRACE(_module_os_intfs_c_,_drv_info_,("rtw_cancel_all_timer:cancel set_scan_deny_timer! \n"));
#endif

#ifdef CONFIG_NEW_SIGNAL_STAT_PROCESS
	_cancel_timer_ex(&padapter->recvpriv.signal_stat_timer);
#endif

	// cancel dm  timer
	rtw_hal_dm_deinit(padapter);

#ifdef CONFIG_PLATFORM_FS_MX61
	msleep(50);
#endif
}