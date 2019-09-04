#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  pnetdev; } ;
typedef  TYPE_1__ _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  netif_carrier_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_indicate_wx_disassoc_event (TYPE_1__*) ; 
 int /*<<< orphan*/  rtw_reset_securitypriv_cmd (TYPE_1__*) ; 

void rtw_os_indicate_disconnect( _adapter *adapter )
{
   //RT_PMKID_LIST   backupPMKIDList[ NUM_PMKID_CACHE ];
  
_func_enter_;

	netif_carrier_off(adapter->pnetdev); // Do it first for tx broadcast pkt after disconnection issue!

#ifdef CONFIG_IOCTL_CFG80211
	rtw_cfg80211_indicate_disconnect(adapter); 	
#endif //CONFIG_IOCTL_CFG80211

	rtw_indicate_wx_disassoc_event(adapter);	

#ifdef RTK_DMP_PLATFORM
	_set_workitem(&adapter->mlmepriv.Linkdown_workitem);
#endif
	 //modify for CONFIG_IEEE80211W, none 11w also can use the same command
	 rtw_reset_securitypriv_cmd(adapter);

_func_exit_;

}