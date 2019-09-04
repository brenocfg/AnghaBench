#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {union iwreq_data* sa_data; int /*<<< orphan*/  sa_family; } ;
union iwreq_data {TYPE_1__ ap_addr; } ;
struct TYPE_5__ {int /*<<< orphan*/  pnetdev; } ;
typedef  TYPE_2__ _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_ETHER ; 
 int ETH_ALEN ; 
 int /*<<< orphan*/  SIOCGIWAP ; 
 int /*<<< orphan*/  _rtw_memset (union iwreq_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wireless_send_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,union iwreq_data*,int /*<<< orphan*/ *) ; 

void rtw_indicate_wx_disassoc_event(_adapter *padapter)
{
#ifndef CONFIG_IOCTL_CFG80211
	union iwreq_data wrqu;

	_rtw_memset(&wrqu, 0, sizeof(union iwreq_data));

	wrqu.ap_addr.sa_family = ARPHRD_ETHER;
	_rtw_memset(wrqu.ap_addr.sa_data, 0, ETH_ALEN);

	//DBG_871X("+rtw_indicate_wx_disassoc_event\n");
	wireless_send_event(padapter->pnetdev, SIOCGIWAP, &wrqu, NULL);
#endif
}