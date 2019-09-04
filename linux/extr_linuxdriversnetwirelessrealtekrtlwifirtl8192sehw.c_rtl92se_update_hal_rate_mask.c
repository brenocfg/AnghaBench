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
typedef  int u8 ;
typedef  int u32 ;
struct rtl_sta_info {int wireless_mode; int ratr_index; } ;
struct TYPE_6__ {scalar_t__ version; } ;
struct rtl_phy {int /*<<< orphan*/  rf_type; } ;
struct rtl_priv {TYPE_3__ rtlhal; struct rtl_phy phy; } ;
struct rtl_mac {scalar_t__ opmode; int bw_40; } ;
struct rtl_hal {scalar_t__ current_bandtype; } ;
struct TYPE_4__ {int* rx_mask; } ;
struct TYPE_5__ {int cap; TYPE_1__ mcs; } ;
struct ieee80211_sta {scalar_t__ bandwidth; int aid; int* supp_rates; TYPE_2__ ht_cap; scalar_t__ drv_priv; } ;
struct ieee80211_hw {int dummy; } ;
typedef  enum wireless_mode { ____Placeholder_wireless_mode } wireless_mode ;

/* Variables and functions */
 scalar_t__ BAND_ON_5G ; 
 int /*<<< orphan*/  COMP_RATR ; 
 int /*<<< orphan*/  DBG_TRACE ; 
 int FW_RA_UPDATE_MASK ; 
 int IEEE80211_HT_CAP_SGI_20 ; 
 int IEEE80211_HT_CAP_SGI_40 ; 
 int IEEE80211_SMPS_OFF ; 
 int IEEE80211_SMPS_STATIC ; 
 scalar_t__ IEEE80211_STA_RX_BW_40 ; 
 scalar_t__ NL80211_IFTYPE_ADHOC ; 
 scalar_t__ NL80211_IFTYPE_AP ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 int RATR_INX_WIRELESS_A ; 
 int RATR_INX_WIRELESS_B ; 
 int RATR_INX_WIRELESS_GB ; 
 int RATR_INX_WIRELESS_NGB ; 
 int /*<<< orphan*/  RF_1T1R ; 
 int /*<<< orphan*/  RF_1T2R ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  SG_RATE ; 
 scalar_t__ VERSION_8192S_ACUT ; 
 scalar_t__ VERSION_8192S_BCUT ; 
 int WFM5 ; 
 int WIRELESS_11A ; 
 int WIRELESS_11B ; 
 int WIRELESS_11G ; 
 int WIRELESS_11N ; 
#define  WIRELESS_MODE_A 132 
#define  WIRELESS_MODE_B 131 
#define  WIRELESS_MODE_G 130 
#define  WIRELESS_MODE_N_24G 129 
#define  WIRELESS_MODE_N_5G 128 
 struct rtl_hal* rtl_hal (struct rtl_priv*) ; 
 struct rtl_mac* rtl_mac (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_write_byte (struct rtl_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtl_write_dword (struct rtl_priv*,int,int) ; 

__attribute__((used)) static void rtl92se_update_hal_rate_mask(struct ieee80211_hw *hw,
					 struct ieee80211_sta *sta,
					 u8 rssi_level, bool update_bw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_phy *rtlphy = &(rtlpriv->phy);
	struct rtl_mac *mac = rtl_mac(rtl_priv(hw));
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	struct rtl_sta_info *sta_entry = NULL;
	u32 ratr_bitmap;
	u8 ratr_index = 0;
	u8 curtxbw_40mhz = (sta->bandwidth >= IEEE80211_STA_RX_BW_40) ? 1 : 0;
	u8 curshortgi_40mhz = (sta->ht_cap.cap & IEEE80211_HT_CAP_SGI_40) ?
				1 : 0;
	u8 curshortgi_20mhz = (sta->ht_cap.cap & IEEE80211_HT_CAP_SGI_20) ?
				1 : 0;
	enum wireless_mode wirelessmode = 0;
	bool shortgi = false;
	u32 ratr_value = 0;
	u8 shortgi_rate = 0;
	u32 mask = 0;
	u32 band = 0;
	bool bmulticast = false;
	u8 macid = 0;
	u8 mimo_ps = IEEE80211_SMPS_OFF;

	sta_entry = (struct rtl_sta_info *) sta->drv_priv;
	wirelessmode = sta_entry->wireless_mode;
	if (mac->opmode == NL80211_IFTYPE_STATION)
		curtxbw_40mhz = mac->bw_40;
	else if (mac->opmode == NL80211_IFTYPE_AP ||
		mac->opmode == NL80211_IFTYPE_ADHOC)
		macid = sta->aid + 1;

	if (rtlhal->current_bandtype == BAND_ON_5G)
		ratr_bitmap = sta->supp_rates[1] << 4;
	else
		ratr_bitmap = sta->supp_rates[0];
	if (mac->opmode == NL80211_IFTYPE_ADHOC)
		ratr_bitmap = 0xfff;
	ratr_bitmap |= (sta->ht_cap.mcs.rx_mask[1] << 20 |
			sta->ht_cap.mcs.rx_mask[0] << 12);
	switch (wirelessmode) {
	case WIRELESS_MODE_B:
		band |= WIRELESS_11B;
		ratr_index = RATR_INX_WIRELESS_B;
		if (ratr_bitmap & 0x0000000c)
			ratr_bitmap &= 0x0000000d;
		else
			ratr_bitmap &= 0x0000000f;
		break;
	case WIRELESS_MODE_G:
		band |= (WIRELESS_11G | WIRELESS_11B);
		ratr_index = RATR_INX_WIRELESS_GB;

		if (rssi_level == 1)
			ratr_bitmap &= 0x00000f00;
		else if (rssi_level == 2)
			ratr_bitmap &= 0x00000ff0;
		else
			ratr_bitmap &= 0x00000ff5;
		break;
	case WIRELESS_MODE_A:
		band |= WIRELESS_11A;
		ratr_index = RATR_INX_WIRELESS_A;
		ratr_bitmap &= 0x00000ff0;
		break;
	case WIRELESS_MODE_N_24G:
	case WIRELESS_MODE_N_5G:
		band |= (WIRELESS_11N | WIRELESS_11G | WIRELESS_11B);
		ratr_index = RATR_INX_WIRELESS_NGB;

		if (mimo_ps == IEEE80211_SMPS_STATIC) {
			if (rssi_level == 1)
				ratr_bitmap &= 0x00070000;
			else if (rssi_level == 2)
				ratr_bitmap &= 0x0007f000;
			else
				ratr_bitmap &= 0x0007f005;
		} else {
			if (rtlphy->rf_type == RF_1T2R ||
				rtlphy->rf_type == RF_1T1R) {
				if (rssi_level == 1) {
						ratr_bitmap &= 0x000f0000;
				} else if (rssi_level == 3) {
					ratr_bitmap &= 0x000fc000;
				} else if (rssi_level == 5) {
						ratr_bitmap &= 0x000ff000;
				} else {
					if (curtxbw_40mhz)
						ratr_bitmap &= 0x000ff015;
					else
						ratr_bitmap &= 0x000ff005;
				}
			} else {
				if (rssi_level == 1) {
					ratr_bitmap &= 0x0f8f0000;
				} else if (rssi_level == 3) {
					ratr_bitmap &= 0x0f8fc000;
				} else if (rssi_level == 5) {
					ratr_bitmap &= 0x0f8ff000;
				} else {
					if (curtxbw_40mhz)
						ratr_bitmap &= 0x0f8ff015;
					else
						ratr_bitmap &= 0x0f8ff005;
				}
			}
		}

		if ((curtxbw_40mhz && curshortgi_40mhz) ||
		    (!curtxbw_40mhz && curshortgi_20mhz)) {
			if (macid == 0)
				shortgi = true;
			else if (macid == 1)
				shortgi = false;
		}
		break;
	default:
		band |= (WIRELESS_11N | WIRELESS_11G | WIRELESS_11B);
		ratr_index = RATR_INX_WIRELESS_NGB;

		if (rtlphy->rf_type == RF_1T2R)
			ratr_bitmap &= 0x000ff0ff;
		else
			ratr_bitmap &= 0x0f8ff0ff;
		break;
	}
	sta_entry->ratr_index = ratr_index;

	if (rtlpriv->rtlhal.version >= VERSION_8192S_BCUT)
		ratr_bitmap &= 0x0FFFFFFF;
	else if (rtlpriv->rtlhal.version == VERSION_8192S_ACUT)
		ratr_bitmap &= 0x0FFFFFF0;

	if (shortgi) {
		ratr_bitmap |= 0x10000000;
		/* Get MAX MCS available. */
		ratr_value = (ratr_bitmap >> 12);
		for (shortgi_rate = 15; shortgi_rate > 0; shortgi_rate--) {
			if ((1 << shortgi_rate) & ratr_value)
				break;
		}

		shortgi_rate = (shortgi_rate << 12) | (shortgi_rate << 8) |
			(shortgi_rate << 4) | (shortgi_rate);
		rtl_write_byte(rtlpriv, SG_RATE, shortgi_rate);
	}

	mask |= (bmulticast ? 1 : 0) << 9 | (macid & 0x1f) << 4 | (band & 0xf);

	RT_TRACE(rtlpriv, COMP_RATR, DBG_TRACE, "mask = %x, bitmap = %x\n",
		 mask, ratr_bitmap);
	rtl_write_dword(rtlpriv, 0x2c4, ratr_bitmap);
	rtl_write_dword(rtlpriv, WFM5, (FW_RA_UPDATE_MASK | (mask << 8)));

	if (macid != 0)
		sta_entry->ratr_index = ratr_index;
}