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
struct TYPE_5__ {int m; int e; int i; } ;
union iwreq_data {TYPE_2__ freq; } ;
struct TYPE_6__ {int DSConfig; } ;
struct wlan_bssid_ex {TYPE_3__ Configuration; } ;
struct net_device {int dummy; } ;
struct TYPE_4__ {struct wlan_bssid_ex network; } ;
struct mlme_priv {TYPE_1__ cur_network; } ;
struct iw_request_info {int dummy; } ;
struct _adapter {struct mlme_priv mlmepriv; } ;

/* Variables and functions */
 int ENOLINK ; 
 int /*<<< orphan*/  _FW_LINKED ; 
 int /*<<< orphan*/  check_fwstate (struct mlme_priv*,int /*<<< orphan*/ ) ; 
 int* ieee80211_wlan_frequencies ; 
 struct _adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int r8711_wx_get_freq(struct net_device *dev,
			     struct iw_request_info *info,
			     union iwreq_data *wrqu, char *extra)
{
	struct _adapter *padapter = netdev_priv(dev);
	struct mlme_priv *pmlmepriv = &padapter->mlmepriv;
	struct wlan_bssid_ex *pcur_bss = &pmlmepriv->cur_network.network;

	if (!check_fwstate(pmlmepriv, _FW_LINKED))
		return -ENOLINK;

	wrqu->freq.m = ieee80211_wlan_frequencies[
		       pcur_bss->Configuration.DSConfig - 1] * 100000;
	wrqu->freq.e = 1;
	wrqu->freq.i = pcur_bss->Configuration.DSConfig;

	return 0;
}