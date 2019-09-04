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
typedef  int u8 ;
typedef  int u32 ;
struct rtl_sta_info {int wireless_mode; int ratr_index; } ;
struct TYPE_12__ {TYPE_5__* ops; } ;
struct rtl_phy {int current_chan_bw; } ;
struct rtl_priv {TYPE_6__ phydm; struct rtl_phy phy; } ;
struct rtl_mac {scalar_t__ opmode; int bw_40; } ;
struct TYPE_9__ {int /*<<< orphan*/  rx_mcs_map; } ;
struct TYPE_10__ {TYPE_3__ vht_mcs; } ;
struct TYPE_7__ {int* rx_mask; } ;
struct TYPE_8__ {int cap; TYPE_1__ mcs; } ;
struct ieee80211_sta {int aid; int* supp_rates; TYPE_4__ vht_cap; TYPE_2__ ht_cap; scalar_t__ drv_priv; } ;
struct ieee80211_hw {int dummy; } ;
typedef  enum wireless_mode { ____Placeholder_wireless_mode } wireless_mode ;
struct TYPE_11__ {int (* phydm_rate_id_mapping ) (struct rtl_priv*,int,int,int) ;int /*<<< orphan*/  (* phydm_get_ra_bitmap ) (struct rtl_priv*,int,int,int,int,int*,int*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  COMP_RATR ; 
 int /*<<< orphan*/  DBG_DMESG ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  H2C_8822B_MACID_CFG ; 
 int /*<<< orphan*/  H2C_8822B_MACID_CFG_3SS ; 
 int IEEE80211_HT_CAP_SUP_WIDTH_20_40 ; 
 size_t NL80211_BAND_2GHZ ; 
 size_t NL80211_BAND_5GHZ ; 
 scalar_t__ NL80211_IFTYPE_ADHOC ; 
 scalar_t__ NL80211_IFTYPE_AP ; 
 scalar_t__ NL80211_IFTYPE_MESH_POINT ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,...) ; 
 int WIRELESS_MODE_A ; 
 int WIRELESS_MODE_AC_24G ; 
 int WIRELESS_MODE_AC_5G ; 
 int WIRELESS_MODE_AC_ONLY ; 
 int WIRELESS_MODE_N_24G ; 
 int WIRELESS_MODE_N_5G ; 
 int _rtl8822be_get_ra_ldpc (struct ieee80211_hw*,int,struct rtl_sta_info*,int) ; 
 int _rtl8822be_get_ra_rftype (struct ieee80211_hw*,int,int) ; 
 int _rtl8822be_get_ra_shortgi (struct ieee80211_hw*,struct ieee80211_sta*,int) ; 
 int _rtl8822be_get_vht_en (int,int) ; 
 int _rtl8822be_rate_to_bitmap_2ssvht (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _rtl8822be_set_bcn_ctrl_reg (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtl8822be_fill_h2c_cmd (struct ieee80211_hw*,int /*<<< orphan*/ ,int,int*) ; 
 struct rtl_mac* rtl_mac (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int stub1 (struct rtl_priv*,int,int,int) ; 
 int /*<<< orphan*/  stub2 (struct rtl_priv*,int,int,int,int,int*,int*) ; 

__attribute__((used)) static void rtl8822be_update_hal_rate_mask(struct ieee80211_hw *hw,
					   struct ieee80211_sta *sta,
					   u8 rssi_level, bool update_bw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_phy *rtlphy = &rtlpriv->phy;
	struct rtl_mac *mac = rtl_mac(rtl_priv(hw));
	struct rtl_sta_info *sta_entry = NULL;
	u32 ratr_bitmap, ratr_bitmap_msb = 0;
	u8 ratr_index;
	enum wireless_mode wirelessmode = 0;
	u8 curtxbw_40mhz =
		(sta->ht_cap.cap & IEEE80211_HT_CAP_SUP_WIDTH_20_40) ? 1 : 0;
	bool b_shortgi = false;
	u8 rate_mask[7];
	u8 macid = 0;
	u8 rf_type;

	sta_entry = (struct rtl_sta_info *)sta->drv_priv;
	wirelessmode = sta_entry->wireless_mode;

	RT_TRACE(rtlpriv, COMP_RATR, DBG_LOUD, "wireless mode = 0x%x\n",
		 wirelessmode);
	if (mac->opmode == NL80211_IFTYPE_STATION ||
	    mac->opmode == NL80211_IFTYPE_MESH_POINT) {
		curtxbw_40mhz = mac->bw_40;
	} else if (mac->opmode == NL80211_IFTYPE_AP ||
		   mac->opmode == NL80211_IFTYPE_ADHOC)
		macid = sta->aid + 1;
	if (wirelessmode == WIRELESS_MODE_N_5G ||
	    wirelessmode == WIRELESS_MODE_AC_5G ||
	    wirelessmode == WIRELESS_MODE_A)
		ratr_bitmap = (sta->supp_rates[NL80211_BAND_5GHZ]) << 4;
	else
		ratr_bitmap = sta->supp_rates[NL80211_BAND_2GHZ];

	if (mac->opmode == NL80211_IFTYPE_ADHOC)
		ratr_bitmap = 0xfff;

	if (wirelessmode == WIRELESS_MODE_N_24G ||
	    wirelessmode == WIRELESS_MODE_N_5G)
		ratr_bitmap |= (sta->ht_cap.mcs.rx_mask[1] << 20 |
				sta->ht_cap.mcs.rx_mask[0] << 12);
	else if (wirelessmode == WIRELESS_MODE_AC_24G ||
		 wirelessmode == WIRELESS_MODE_AC_5G ||
		 wirelessmode == WIRELESS_MODE_AC_ONLY)
		ratr_bitmap |= _rtl8822be_rate_to_bitmap_2ssvht(
				       sta->vht_cap.vht_mcs.rx_mcs_map)
			       << 12;

	b_shortgi = _rtl8822be_get_ra_shortgi(hw, sta, macid);
	rf_type = _rtl8822be_get_ra_rftype(hw, wirelessmode, ratr_bitmap);

	ratr_index = rtlpriv->phydm.ops->phydm_rate_id_mapping(
		rtlpriv, wirelessmode, rf_type, rtlphy->current_chan_bw);
	sta_entry->ratr_index = ratr_index;

	rtlpriv->phydm.ops->phydm_get_ra_bitmap(
		rtlpriv, wirelessmode, rf_type, rtlphy->current_chan_bw,
		rssi_level, &ratr_bitmap_msb, &ratr_bitmap);

	RT_TRACE(rtlpriv, COMP_RATR, DBG_LOUD, "ratr_bitmap :%x\n",
		 ratr_bitmap);

	rate_mask[0] = macid;
	rate_mask[1] = ratr_index | (b_shortgi ? 0x80 : 0x00);
	rate_mask[2] =
		rtlphy->current_chan_bw | ((!update_bw) << 3) |
		_rtl8822be_get_vht_en(wirelessmode, ratr_bitmap) |
		_rtl8822be_get_ra_ldpc(hw, macid, sta_entry, wirelessmode);

	rate_mask[3] = (u8)(ratr_bitmap & 0x000000ff);
	rate_mask[4] = (u8)((ratr_bitmap & 0x0000ff00) >> 8);
	rate_mask[5] = (u8)((ratr_bitmap & 0x00ff0000) >> 16);
	rate_mask[6] = (u8)((ratr_bitmap & 0xff000000) >> 24);

	RT_TRACE(
		rtlpriv, COMP_RATR, DBG_DMESG,
		"Rate_index:%x, ratr_val:%08x, %02x:%02x:%02x:%02x:%02x:%02x:%02x\n",
		ratr_index, ratr_bitmap, rate_mask[0], rate_mask[1],
		rate_mask[2], rate_mask[3], rate_mask[4], rate_mask[5],
		rate_mask[6]);
	rtl8822be_fill_h2c_cmd(hw, H2C_8822B_MACID_CFG, 7, rate_mask);

	/* for h2c cmd 0x46, only modify cmd id & ra mask */
	/* Keep rate_mask0~2 of cmd 0x40, but clear byte3 and later */
	/* 8822B has no 3SS, so keep it zeros. */
	memset(rate_mask + 3, 0, 4);

	rtl8822be_fill_h2c_cmd(hw, H2C_8822B_MACID_CFG_3SS, 7, rate_mask);

	_rtl8822be_set_bcn_ctrl_reg(hw, BIT(3), 0);
}