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
struct TYPE_4__ {scalar_t__* pid; int /*<<< orphan*/  pnetdev; } ;
typedef  TYPE_1__ _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  SIGALRM ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  netif_carrier_on (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_indicate_wx_assoc_event (TYPE_1__*) ; 
 int /*<<< orphan*/  rtw_signal_process (scalar_t__,int /*<<< orphan*/ ) ; 

void rtw_os_indicate_connect(_adapter *adapter)
{

_func_enter_;	

#ifdef CONFIG_IOCTL_CFG80211
	rtw_cfg80211_indicate_connect(adapter);
#endif //CONFIG_IOCTL_CFG80211

	rtw_indicate_wx_assoc_event(adapter);
	netif_carrier_on(adapter->pnetdev);

	if(adapter->pid[2] !=0)
		rtw_signal_process(adapter->pid[2], SIGALRM);

#ifdef RTK_DMP_PLATFORM
	_set_workitem(&adapter->mlmepriv.Linkup_workitem);
#endif

_func_exit_;	

}