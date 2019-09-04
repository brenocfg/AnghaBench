#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
union iwreq_data {int /*<<< orphan*/  name; } ;
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct net_device {int dummy; } ;
struct TYPE_6__ {int DSConfig; } ;
struct TYPE_8__ {TYPE_2__ Configuration; int /*<<< orphan*/  SupportedRates; scalar_t__ IELength; int /*<<< orphan*/ * IEs; } ;
struct TYPE_5__ {TYPE_4__ network; } ;
struct mlme_priv {TYPE_1__ cur_network; } ;
struct iw_request_info {int /*<<< orphan*/  cmd; } ;
struct TYPE_7__ {struct mlme_priv mlmepriv; } ;
typedef  TYPE_3__ _adapter ;
typedef  TYPE_4__ WLAN_BSSID_EX ;
typedef  int /*<<< orphan*/  NDIS_802_11_RATES_EX ;

/* Variables and functions */
 int /*<<< orphan*/  IFNAMSIZ ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int WIFI_ADHOC_MASTER_STATE ; 
 scalar_t__ _FALSE ; 
 int _FW_LINKED ; 
 int /*<<< orphan*/  _HT_CAPABILITY_IE_ ; 
 scalar_t__ _TRUE ; 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  _module_rtl871x_mlme_c_ ; 
 scalar_t__ check_fwstate (struct mlme_priv*,int) ; 
 char* rtw_get_ie (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*,scalar_t__) ; 
 scalar_t__ rtw_is_cckrates_included (scalar_t__*) ; 
 scalar_t__ rtw_is_cckratesonly_included (scalar_t__*) ; 
 scalar_t__ rtw_netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int rtw_wx_get_name(struct net_device *dev, 
			     struct iw_request_info *info, 
			     union iwreq_data *wrqu, char *extra)
{
	_adapter *padapter = (_adapter *)rtw_netdev_priv(dev);
	u16 cap;
	u32 ht_ielen = 0;
	char *p;
	u8 ht_cap=_FALSE;
	struct	mlme_priv	*pmlmepriv = &(padapter->mlmepriv);
	WLAN_BSSID_EX  *pcur_bss = &pmlmepriv->cur_network.network;
	NDIS_802_11_RATES_EX* prates = NULL;

	RT_TRACE(_module_rtl871x_mlme_c_,_drv_info_,("cmd_code=%x\n", info->cmd));

	_func_enter_;	

	if (check_fwstate(pmlmepriv, _FW_LINKED|WIFI_ADHOC_MASTER_STATE) == _TRUE)
	{
		//parsing HT_CAP_IE
		p = rtw_get_ie(&pcur_bss->IEs[12], _HT_CAPABILITY_IE_, &ht_ielen, pcur_bss->IELength-12);
		if(p && ht_ielen>0)
		{
			ht_cap = _TRUE;
		}

		prates = &pcur_bss->SupportedRates;

		if (rtw_is_cckratesonly_included((u8*)prates) == _TRUE)
		{
			if(ht_cap == _TRUE)
				snprintf(wrqu->name, IFNAMSIZ, "IEEE 802.11bn");
			else
				snprintf(wrqu->name, IFNAMSIZ, "IEEE 802.11b");
		}
		else if ((rtw_is_cckrates_included((u8*)prates)) == _TRUE)
		{
			if(ht_cap == _TRUE)
				snprintf(wrqu->name, IFNAMSIZ, "IEEE 802.11bgn");
			else
				snprintf(wrqu->name, IFNAMSIZ, "IEEE 802.11bg");
		}
		else
		{
			if(pcur_bss->Configuration.DSConfig > 14)
			{
				if(ht_cap == _TRUE)
					snprintf(wrqu->name, IFNAMSIZ, "IEEE 802.11an");
				else
					snprintf(wrqu->name, IFNAMSIZ, "IEEE 802.11a");
			}
			else
			{
				if(ht_cap == _TRUE)
					snprintf(wrqu->name, IFNAMSIZ, "IEEE 802.11gn");
				else
					snprintf(wrqu->name, IFNAMSIZ, "IEEE 802.11g");
			}
		}
	}
	else
	{
		//prates = &padapter->registrypriv.dev_network.SupportedRates;
		//snprintf(wrqu->name, IFNAMSIZ, "IEEE 802.11g");
		snprintf(wrqu->name, IFNAMSIZ, "unassociated");
	}

	_func_exit_;

	return 0;
}