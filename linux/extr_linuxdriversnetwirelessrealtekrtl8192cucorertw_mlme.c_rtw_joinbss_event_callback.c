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
typedef  int /*<<< orphan*/  u8 ;
struct wlan_network {int /*<<< orphan*/  join_res; } ;
typedef  int /*<<< orphan*/  _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  mlmeext_joinbss_event_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_os_xmit_schedule (int /*<<< orphan*/ *) ; 

void rtw_joinbss_event_callback(_adapter *adapter, u8 *pbuf)
{
	struct wlan_network 	*pnetwork	= (struct wlan_network *)pbuf;

_func_enter_;

	mlmeext_joinbss_event_callback(adapter, pnetwork->join_res);

	rtw_os_xmit_schedule(adapter);

#ifdef CONFIG_CONCURRENT_MODE	
	rtw_os_xmit_schedule(adapter->pbuddy_adapter);
#endif

#ifdef CONFIG_DUALMAC_CONCURRENT
	dc_resume_xmit(adapter);
#endif

_func_exit_;
}