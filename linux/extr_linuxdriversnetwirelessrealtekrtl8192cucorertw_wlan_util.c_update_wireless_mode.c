#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_9__ {unsigned char* SupportedRates; } ;
struct mlme_ext_info {int HT_enable; scalar_t__ HT_caps_enable; scalar_t__ HT_info_enable; TYPE_3__ network; } ;
struct mlme_ext_priv {int cur_channel; int cur_wireless_mode; struct mlme_ext_info mlmext_info; } ;
struct TYPE_7__ {int wireless_mode; } ;
struct TYPE_8__ {TYPE_1__ registrypriv; struct mlme_ext_priv mlmeextpriv; } ;
typedef  TYPE_2__ _adapter ;
typedef  TYPE_3__ WLAN_BSSID_EX ;

/* Variables and functions */
 int /*<<< orphan*/  HW_VAR_INIT_DATA_RATE ; 
 int /*<<< orphan*/  HW_VAR_RESP_SIFS ; 
 int /*<<< orphan*/  IEEE80211_CCK_RATE_1MB ; 
 int /*<<< orphan*/  IEEE80211_OFDM_RATE_6MB ; 
 int WIRELESS_11A ; 
 int WIRELESS_11B ; 
 int WIRELESS_11BG ; 
 int WIRELESS_11G ; 
 int WIRELESS_11_24N ; 
 int WIRELESS_11_5N ; 
 scalar_t__ _TRUE ; 
 scalar_t__ cckrates_included (unsigned char*,int) ; 
 scalar_t__ cckratesonly_included (unsigned char*,int) ; 
 int get_highest_rate_idx (int) ; 
 int rtw_get_rateset_len (unsigned char*) ; 
 int /*<<< orphan*/  rtw_hal_set_hwreg (TYPE_2__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  update_mgnt_tx_rate (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int update_supported_rate (unsigned char*,int) ; 

void update_wireless_mode(_adapter *padapter)
{
	u8	init_rate=0;
	int	ratelen, network_type = 0;
	u32	SIFS_Timer, mask;
	struct mlme_ext_priv	*pmlmeext = &padapter->mlmeextpriv;
	struct mlme_ext_info	*pmlmeinfo = &(pmlmeext->mlmext_info);
	WLAN_BSSID_EX 		*cur_network = &(pmlmeinfo->network);
	unsigned char			*rate = cur_network->SupportedRates;
#ifdef CONFIG_CONCURRENT_MODE
	_adapter *pbuddy_adapter = padapter->pbuddy_adapter;
#endif //CONFIG_CONCURRENT_MODE

	ratelen = rtw_get_rateset_len(cur_network->SupportedRates);

	if ((pmlmeinfo->HT_info_enable) && (pmlmeinfo->HT_caps_enable))
	{
		pmlmeinfo->HT_enable = 1;
	}

	if(pmlmeext->cur_channel > 14)
	{
		if (pmlmeinfo->HT_enable)
		{
			network_type = WIRELESS_11_5N;
		}

		network_type |= WIRELESS_11A;
	}
	else
	{
		if (pmlmeinfo->HT_enable)
		{
			network_type = WIRELESS_11_24N;
		}
	
		if ((cckratesonly_included(rate, ratelen)) == _TRUE)
		{
			network_type |= WIRELESS_11B;
		}
		else if((cckrates_included(rate, ratelen)) == _TRUE)
		{
			network_type |= WIRELESS_11BG;
		}
		else
		{
			network_type |= WIRELESS_11G;
		}
	}

	pmlmeext->cur_wireless_mode = network_type & padapter->registrypriv.wireless_mode;

	//For STA mode, driver need to modify initial data rate, or MAC will use wrong tx rate.
	//Modified by Thomas 2012-12-3
	mask = update_supported_rate(cur_network->SupportedRates, ratelen);
	init_rate = get_highest_rate_idx(mask)&0x3f;
	rtw_hal_set_hwreg( padapter, HW_VAR_INIT_DATA_RATE,  (u8 *)&init_rate);
	
/*
	if((pmlmeext->cur_wireless_mode==WIRELESS_11G) ||
		(pmlmeext->cur_wireless_mode==WIRELESS_11BG))//WIRELESS_MODE_G)
		SIFS_Timer = 0x0a0a;//CCK
	else
		SIFS_Timer = 0x0e0e;//pHalData->SifsTime; //OFDM
*/
	
	SIFS_Timer = 0x0a0a0808; //0x0808 -> for CCK, 0x0a0a -> for OFDM
                             //change this value if having IOT issues.
		
	rtw_hal_set_hwreg( padapter, HW_VAR_RESP_SIFS,  (u8 *)&SIFS_Timer);

	if (pmlmeext->cur_wireless_mode & WIRELESS_11B)
		update_mgnt_tx_rate(padapter, IEEE80211_CCK_RATE_1MB);
	else
	{
		update_mgnt_tx_rate(padapter, IEEE80211_OFDM_RATE_6MB);
#ifdef CONFIG_CONCURRENT_MODE
		if(pbuddy_adapter && (pmlmeext->cur_wireless_mode & WIRELESS_11A))
			update_mgnt_tx_rate(pbuddy_adapter, IEEE80211_OFDM_RATE_6MB);
#endif //CONFIG_CONCURRENT_MODE
	}
}