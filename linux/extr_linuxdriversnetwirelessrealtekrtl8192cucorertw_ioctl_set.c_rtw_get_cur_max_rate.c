#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct registry_priv {int dummy; } ;
struct TYPE_7__ {int* SupportedRates; } ;
struct TYPE_5__ {TYPE_3__ network; } ;
struct mlme_priv {TYPE_1__ cur_network; } ;
struct mlme_ext_info {int dummy; } ;
struct mlme_ext_priv {struct mlme_ext_info mlmext_info; } ;
struct TYPE_6__ {struct mlme_priv mlmepriv; struct registry_priv registrypriv; struct mlme_ext_priv mlmeextpriv; } ;
typedef  TYPE_2__ _adapter ;
typedef  TYPE_3__ WLAN_BSSID_EX ;

/* Variables and functions */
 int /*<<< orphan*/  WIFI_ADHOC_MASTER_STATE ; 
 int /*<<< orphan*/  _FW_LINKED ; 
 scalar_t__ _TRUE ; 
 scalar_t__ check_fwstate (struct mlme_priv*,int /*<<< orphan*/ ) ; 

u16 rtw_get_cur_max_rate(_adapter *adapter)
{
	int	i = 0;
	u8	*p;
	u16	rate = 0, max_rate = 0;
	struct mlme_ext_priv	*pmlmeext = &adapter->mlmeextpriv;
	struct mlme_ext_info	*pmlmeinfo = &(pmlmeext->mlmext_info);
	struct registry_priv *pregistrypriv = &adapter->registrypriv;
	struct mlme_priv	*pmlmepriv = &adapter->mlmepriv;
	WLAN_BSSID_EX  *pcur_bss = &pmlmepriv->cur_network.network;
#ifdef CONFIG_80211N_HT
	struct rtw_ieee80211_ht_cap *pht_capie;
	u8	rf_type = 0;
	u8	bw_40MHz=0, short_GI_20=0, short_GI_40=0;
	u16	mcs_rate=0;
	u32	ht_ielen = 0;	
#endif

#ifdef CONFIG_MP_INCLUDED
	if (adapter->registrypriv.mp_mode == 1)
	{	
		if (check_fwstate(pmlmepriv, WIFI_MP_STATE) == _TRUE)
			return 0;
	}
#endif

	if((check_fwstate(pmlmepriv, _FW_LINKED) != _TRUE) 
		&& (check_fwstate(pmlmepriv, WIFI_ADHOC_MASTER_STATE) != _TRUE))
		return 0;

#ifdef CONFIG_80211N_HT
	if (pmlmeext->cur_wireless_mode & (WIRELESS_11_24N|WIRELESS_11_5N)) {
		p = rtw_get_ie(&pcur_bss->IEs[12], _HT_CAPABILITY_IE_, &ht_ielen, pcur_bss->IELength-12);
		if(p && ht_ielen>0)
		{
			pht_capie = (struct rtw_ieee80211_ht_cap *)(p+2);
		
			_rtw_memcpy(&mcs_rate , pht_capie->supp_mcs_set, 2);

			//bw_40MHz = (pht_capie->cap_info&IEEE80211_HT_CAP_SUP_WIDTH) ? 1:0;
			//cur_bwmod is updated by beacon, pmlmeinfo is updated by association response
			bw_40MHz = (pmlmeext->cur_bwmode && (HT_INFO_HT_PARAM_REC_TRANS_CHNL_WIDTH & pmlmeinfo->HT_info.infos[0])) ? 1:0;
			
			//short_GI = (pht_capie->cap_info&(IEEE80211_HT_CAP_SGI_20|IEEE80211_HT_CAP_SGI_40)) ? 1:0;
			short_GI_20 = (pmlmeinfo->HT_caps.u.HT_cap_element.HT_caps_info&IEEE80211_HT_CAP_SGI_20) ? 1:0;
			short_GI_40 = (pmlmeinfo->HT_caps.u.HT_cap_element.HT_caps_info&IEEE80211_HT_CAP_SGI_40) ? 1:0;

			rtw_hal_get_hwreg(adapter, HW_VAR_RF_TYPE, (u8 *)(&rf_type));
			max_rate = rtw_mcs_rate(
				rf_type,
				bw_40MHz & (pregistrypriv->cbw40_enable), 
				short_GI_20,
				short_GI_40,
				pmlmeinfo->HT_caps.u.HT_cap_element.MCS_rate
			);
		}
	} 
	else
#endif //CONFIG_80211N_HT
	{
		while( (pcur_bss->SupportedRates[i]!=0) && (pcur_bss->SupportedRates[i]!=0xFF))
		{
			rate = pcur_bss->SupportedRates[i]&0x7F;
			if(rate>max_rate)
				max_rate = rate;
			i++;
		}
	
		max_rate = max_rate*10/2;
	}

	return max_rate;
}