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
typedef  int u32 ;
struct rtl_phy {scalar_t__ current_chan_bw; } ;
struct rtl_priv {struct rtl_phy phy; } ;
struct rtl_efuse {int** txpwr_legacyhtdiff; int** txpwr_ht20diff; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FPHY ; 
 scalar_t__ HT_CHANNEL_WIDTH_20 ; 
 int /*<<< orphan*/  PHY_TXPWR ; 
 int /*<<< orphan*/  RTPRINT (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char,int) ; 
 struct rtl_efuse* rtl_efuse (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static void rtl8723e_phy_get_power_base(struct ieee80211_hw *hw,
					u8 *ppowerlevel, u8 channel,
					u32 *ofdmbase, u32 *mcsbase)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_phy *rtlphy = &rtlpriv->phy;
	struct rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	u32 powerbase0, powerbase1;
	u8 legacy_pwrdiff, ht20_pwrdiff;
	u8 i, powerlevel[2];

	for (i = 0; i < 2; i++) {
		powerlevel[i] = ppowerlevel[i];
		legacy_pwrdiff = rtlefuse->txpwr_legacyhtdiff[i][channel - 1];
		powerbase0 = powerlevel[i] + legacy_pwrdiff;

		powerbase0 = (powerbase0 << 24) | (powerbase0 << 16) |
		    (powerbase0 << 8) | powerbase0;
		*(ofdmbase + i) = powerbase0;
		RTPRINT(rtlpriv, FPHY, PHY_TXPWR,
			" [OFDM power base index rf(%c) = 0x%x]\n",
			 ((i == 0) ? 'A' : 'B'), *(ofdmbase + i));
	}

	for (i = 0; i < 2; i++) {
		if (rtlphy->current_chan_bw == HT_CHANNEL_WIDTH_20) {
			ht20_pwrdiff =
				rtlefuse->txpwr_ht20diff[i][channel - 1];
			powerlevel[i] += ht20_pwrdiff;
		}
		powerbase1 = powerlevel[i];
		powerbase1 = (powerbase1 << 24) |
		    (powerbase1 << 16) | (powerbase1 << 8) | powerbase1;

		*(mcsbase + i) = powerbase1;

		RTPRINT(rtlpriv, FPHY, PHY_TXPWR,
			" [MCS power base index rf(%c) = 0x%x]\n",
			 ((i == 0) ? 'A' : 'B'), *(mcsbase + i));
	}
}