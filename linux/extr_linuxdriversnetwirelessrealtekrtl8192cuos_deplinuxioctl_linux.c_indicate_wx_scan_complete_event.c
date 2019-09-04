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
typedef  union iwreq_data {int dummy; } iwreq_data ;
struct mlme_priv {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  pnetdev; struct mlme_priv mlmepriv; } ;
typedef  TYPE_1__ _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  SIOCGIWSCAN ; 
 int /*<<< orphan*/  _rtw_memset (union iwreq_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wireless_send_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,union iwreq_data*,int /*<<< orphan*/ *) ; 

void indicate_wx_scan_complete_event(_adapter *padapter)
{
#ifndef CONFIG_IOCTL_CFG80211
	union iwreq_data wrqu;
	struct	mlme_priv *pmlmepriv = &padapter->mlmepriv;

	_rtw_memset(&wrqu, 0, sizeof(union iwreq_data));

	//DBG_871X("+rtw_indicate_wx_scan_complete_event\n");
	wireless_send_event(padapter->pnetdev, SIOCGIWSCAN, &wrqu, NULL);
#endif
}