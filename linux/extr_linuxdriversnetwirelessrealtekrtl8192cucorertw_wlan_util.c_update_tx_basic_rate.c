#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct mlme_ext_priv {int cur_channel; } ;
struct TYPE_5__ {struct mlme_ext_priv mlmeextpriv; } ;
typedef  TYPE_1__ _adapter ;
typedef  int /*<<< orphan*/  NDIS_802_11_RATES_EX ;

/* Variables and functions */
 int /*<<< orphan*/  HW_VAR_BASIC_RATE ; 
 int /*<<< orphan*/  IEEE80211_CCK_RATE_1MB ; 
 int /*<<< orphan*/  IEEE80211_OFDM_RATE_6MB ; 
 int /*<<< orphan*/  NDIS_802_11_LENGTH_RATES_EX ; 
 int WIRELESS_11B ; 
 int /*<<< orphan*/  _rtw_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  _rtw_memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_basic_rate_cck ; 
 int /*<<< orphan*/  rtw_basic_rate_mix ; 
 int /*<<< orphan*/  rtw_basic_rate_ofdm ; 
 int /*<<< orphan*/  rtw_hal_set_hwreg (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_mgnt_tx_rate (TYPE_1__*,int /*<<< orphan*/ ) ; 

void update_tx_basic_rate(_adapter *padapter, u8 wirelessmode)
{
	NDIS_802_11_RATES_EX	supported_rates;
	struct mlme_ext_priv	*pmlmeext = &padapter->mlmeextpriv;
#ifdef CONFIG_P2P
	struct wifidirect_info*	pwdinfo = &padapter->wdinfo;

	//	Added by Albert 2011/03/22
	//	In the P2P mode, the driver should not support the b mode.
	//	So, the Tx packet shouldn't use the CCK rate
	if(!rtw_p2p_chk_state(pwdinfo, P2P_STATE_NONE))
		return;
#endif //CONFIG_P2P
#ifdef CONFIG_INTEL_WIDI
	if (padapter->mlmepriv.widi_state != INTEL_WIDI_STATE_NONE)
		return;
#endif //CONFIG_INTEL_WIDI

	_rtw_memset(supported_rates, 0, NDIS_802_11_LENGTH_RATES_EX);

	//clear B mod if current channel is in 5G band, avoid tx cck rate in 5G band.
	if(pmlmeext->cur_channel > 14)
		wirelessmode &= ~(WIRELESS_11B);

	if ((wirelessmode & WIRELESS_11B) && (wirelessmode == WIRELESS_11B)) {
		_rtw_memcpy(supported_rates, rtw_basic_rate_cck, 4);
	} else if (wirelessmode & WIRELESS_11B) {
		_rtw_memcpy(supported_rates, rtw_basic_rate_mix, 7);
	} else {
		_rtw_memcpy(supported_rates, rtw_basic_rate_ofdm, 3);
	}

	if (wirelessmode & WIRELESS_11B)
		update_mgnt_tx_rate(padapter, IEEE80211_CCK_RATE_1MB);
	else
		update_mgnt_tx_rate(padapter, IEEE80211_OFDM_RATE_6MB);

	rtw_hal_set_hwreg(padapter, HW_VAR_BASIC_RATE, supported_rates);
}