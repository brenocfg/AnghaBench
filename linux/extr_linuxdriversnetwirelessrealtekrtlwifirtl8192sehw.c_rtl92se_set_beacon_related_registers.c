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
typedef  int u16 ;
struct rtl_priv {int dummy; } ;
struct rtl_mac {int beacon_interval; scalar_t__ opmode; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATIMWND ; 
 int /*<<< orphan*/  BCN_DMATIME ; 
 int /*<<< orphan*/  BCN_DRV_EARLY_INT ; 
 int /*<<< orphan*/  BCN_ERR_THRESH ; 
 int /*<<< orphan*/  BCN_INTERVAL ; 
 int BCN_TCFG_CW_SHIFT ; 
 int BCN_TCFG_IFS ; 
 scalar_t__ NL80211_IFTYPE_ADHOC ; 
 int /*<<< orphan*/  rtl92s_phy_set_beacon_hwreg (struct ieee80211_hw*,int) ; 
 struct rtl_mac* rtl_mac (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_write_byte (struct rtl_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtl_write_word (struct rtl_priv*,int /*<<< orphan*/ ,int) ; 

void rtl92se_set_beacon_related_registers(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_mac *mac = rtl_mac(rtl_priv(hw));
	u16 bcntime_cfg = 0;
	u16 bcn_cw = 6, bcn_ifs = 0xf;
	u16 atim_window = 2;

	/* ATIM Window (in unit of TU). */
	rtl_write_word(rtlpriv, ATIMWND, atim_window);

	/* Beacon interval (in unit of TU). */
	rtl_write_word(rtlpriv, BCN_INTERVAL, mac->beacon_interval);

	/* DrvErlyInt (in unit of TU). (Time to send
	 * interrupt to notify driver to change
	 * beacon content) */
	rtl_write_word(rtlpriv, BCN_DRV_EARLY_INT, 10 << 4);

	/* BcnDMATIM(in unit of us). Indicates the
	 * time before TBTT to perform beacon queue DMA  */
	rtl_write_word(rtlpriv, BCN_DMATIME, 256);

	/* Force beacon frame transmission even
	 * after receiving beacon frame from
	 * other ad hoc STA */
	rtl_write_byte(rtlpriv, BCN_ERR_THRESH, 100);

	/* Beacon Time Configuration */
	if (mac->opmode == NL80211_IFTYPE_ADHOC)
		bcntime_cfg |= (bcn_cw << BCN_TCFG_CW_SHIFT);

	/* TODO: bcn_ifs may required to be changed on ASIC */
	bcntime_cfg |= bcn_ifs << BCN_TCFG_IFS;

	/*for beacon changed */
	rtl92s_phy_set_beacon_hwreg(hw, mac->beacon_interval);
}