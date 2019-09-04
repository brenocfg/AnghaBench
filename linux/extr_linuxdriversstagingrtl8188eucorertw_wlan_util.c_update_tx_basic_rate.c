#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u8 ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HW_VAR_BASIC_RATE ; 
 int /*<<< orphan*/  IEEE80211_CCK_RATE_1MB ; 
 int /*<<< orphan*/  IEEE80211_OFDM_RATE_6MB ; 
 int NDIS_802_11_LENGTH_RATES_EX ; 
 int WIRELESS_11B ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtw_basic_rate_cck ; 
 int /*<<< orphan*/  rtw_basic_rate_mix ; 
 int /*<<< orphan*/  rtw_basic_rate_ofdm ; 
 int /*<<< orphan*/  rtw_hal_set_hwreg (struct adapter*,int /*<<< orphan*/ ,unsigned char*) ; 
 int /*<<< orphan*/  update_mgnt_tx_rate (struct adapter*,int /*<<< orphan*/ ) ; 

void update_tx_basic_rate(struct adapter *padapter, u8 wirelessmode)
{
	unsigned char supported_rates[NDIS_802_11_LENGTH_RATES_EX];

	memset(supported_rates, 0, NDIS_802_11_LENGTH_RATES_EX);

	if ((wirelessmode & WIRELESS_11B) && (wirelessmode == WIRELESS_11B))
		memcpy(supported_rates, rtw_basic_rate_cck, 4);
	else if (wirelessmode & WIRELESS_11B)
		memcpy(supported_rates, rtw_basic_rate_mix, 7);
	else
		memcpy(supported_rates, rtw_basic_rate_ofdm, 3);

	if (wirelessmode & WIRELESS_11B)
		update_mgnt_tx_rate(padapter, IEEE80211_CCK_RATE_1MB);
	else
		update_mgnt_tx_rate(padapter, IEEE80211_OFDM_RATE_6MB);

	rtw_hal_set_hwreg(padapter, HW_VAR_BASIC_RATE, supported_rates);
}