#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int length; int flags; } ;
union iwreq_data {TYPE_3__ essid; } ;
typedef  int u32 ;
struct net_device {int dummy; } ;
struct TYPE_7__ {int SsidLength; int /*<<< orphan*/  Ssid; } ;
struct TYPE_10__ {TYPE_2__ Ssid; } ;
struct TYPE_6__ {TYPE_5__ network; } ;
struct mlme_priv {TYPE_1__ cur_network; } ;
struct iw_request_info {int dummy; } ;
struct TYPE_9__ {struct mlme_priv mlmepriv; } ;
typedef  TYPE_4__ _adapter ;
typedef  TYPE_5__ WLAN_BSSID_EX ;

/* Variables and functions */
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  WIFI_ADHOC_MASTER_STATE ; 
 int /*<<< orphan*/  _FW_LINKED ; 
 scalar_t__ _TRUE ; 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  _module_rtl871x_mlme_c_ ; 
 int /*<<< orphan*/  _rtw_memcpy (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ check_fwstate (struct mlme_priv*,int /*<<< orphan*/ ) ; 
 scalar_t__ rtw_netdev_priv (struct net_device*) ; 

__attribute__((used)) static int rtw_wx_get_essid(struct net_device *dev, 
			      struct iw_request_info *a,
			      union iwreq_data *wrqu, char *extra)
{
	u32 len,ret = 0;
	_adapter *padapter = (_adapter *)rtw_netdev_priv(dev);
	struct	mlme_priv	*pmlmepriv = &(padapter->mlmepriv);
	WLAN_BSSID_EX  *pcur_bss = &pmlmepriv->cur_network.network;

	RT_TRACE(_module_rtl871x_mlme_c_,_drv_info_,("rtw_wx_get_essid\n"));

	_func_enter_;

	if ( (check_fwstate(pmlmepriv, _FW_LINKED) == _TRUE) ||
	      (check_fwstate(pmlmepriv, WIFI_ADHOC_MASTER_STATE) == _TRUE))
	{
		len = pcur_bss->Ssid.SsidLength;

		wrqu->essid.length = len;
			
		_rtw_memcpy(extra, pcur_bss->Ssid.Ssid, len);

		wrqu->essid.flags = 1;
	}
	else
	{
		ret = -1;
		goto exit;
	}

exit:
	
	_func_exit_;
	
	return ret;
	
}