#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int m; int e; int /*<<< orphan*/  i; } ;
union iwreq_data {TYPE_3__ freq; } ;
struct net_device {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  DSConfig; } ;
struct TYPE_12__ {TYPE_2__ Configuration; } ;
struct TYPE_7__ {TYPE_6__ network; } ;
struct mlme_priv {TYPE_1__ cur_network; } ;
struct iw_request_info {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  cur_channel; } ;
struct TYPE_11__ {TYPE_4__ mlmeextpriv; struct mlme_priv mlmepriv; } ;
typedef  TYPE_5__ _adapter ;
typedef  TYPE_6__ WLAN_BSSID_EX ;

/* Variables and functions */
 int /*<<< orphan*/  _FW_LINKED ; 
 scalar_t__ _TRUE ; 
 scalar_t__ check_fwstate (struct mlme_priv*,int /*<<< orphan*/ ) ; 
 int rtw_ch2freq (int /*<<< orphan*/ ) ; 
 scalar_t__ rtw_netdev_priv (struct net_device*) ; 

__attribute__((used)) static int rtw_wx_get_freq(struct net_device *dev, 
			     struct iw_request_info *info, 
			     union iwreq_data *wrqu, char *extra)
{
	_adapter *padapter = (_adapter *)rtw_netdev_priv(dev);
	struct	mlme_priv	*pmlmepriv = &(padapter->mlmepriv);
	WLAN_BSSID_EX  *pcur_bss = &pmlmepriv->cur_network.network;
	
	if(check_fwstate(pmlmepriv, _FW_LINKED) == _TRUE)
	{
		//wrqu->freq.m = ieee80211_wlan_frequencies[pcur_bss->Configuration.DSConfig-1] * 100000;
		wrqu->freq.m = rtw_ch2freq(pcur_bss->Configuration.DSConfig) * 100000;
		wrqu->freq.e = 1;
		wrqu->freq.i = pcur_bss->Configuration.DSConfig;

	}
	else{
		wrqu->freq.m = rtw_ch2freq(padapter->mlmeextpriv.cur_channel) * 100000;
		wrqu->freq.e = 1;
		wrqu->freq.i = padapter->mlmeextpriv.cur_channel;
	}

	return 0;
}