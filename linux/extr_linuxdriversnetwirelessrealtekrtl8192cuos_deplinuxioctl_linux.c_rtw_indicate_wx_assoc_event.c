#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  sa_data; int /*<<< orphan*/  sa_family; } ;
union iwreq_data {TYPE_1__ ap_addr; } ;
struct TYPE_7__ {int /*<<< orphan*/  MacAddress; } ;
struct TYPE_8__ {TYPE_2__ network; } ;
struct mlme_priv {TYPE_3__ cur_network; } ;
struct TYPE_9__ {int /*<<< orphan*/  pnetdev; struct mlme_priv mlmepriv; } ;
typedef  TYPE_4__ _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_ETHER ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  SIOCGIWAP ; 
 int /*<<< orphan*/  _rtw_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _rtw_memset (union iwreq_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wireless_send_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,union iwreq_data*,int /*<<< orphan*/ *) ; 

void rtw_indicate_wx_assoc_event(_adapter *padapter)
{
#ifndef CONFIG_IOCTL_CFG80211
	union iwreq_data wrqu;
	struct	mlme_priv *pmlmepriv = &padapter->mlmepriv;

	_rtw_memset(&wrqu, 0, sizeof(union iwreq_data));

	wrqu.ap_addr.sa_family = ARPHRD_ETHER;

	_rtw_memcpy(wrqu.ap_addr.sa_data, pmlmepriv->cur_network.network.MacAddress, ETH_ALEN);

	//DBG_871X("+rtw_indicate_wx_assoc_event\n");
	wireless_send_event(padapter->pnetdev, SIOCGIWAP, &wrqu, NULL);
#endif
}