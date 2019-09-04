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
typedef  void* u8 ;
struct rtl_phy {void* cur_bw40_txpwridx; void* cur_bw20_txpwridx; void* cur_ofdm24g_txpwridx; void* cur_cck_txpwridx; } ;
struct rtl_priv {struct rtl_phy phy; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static void _rtl88e_ccxpower_index_check(struct ieee80211_hw *hw,
					 u8 channel, u8 *cckpowerlevel,
					 u8 *ofdmpowerlevel, u8 *bw20powerlevel,
					 u8 *bw40powerlevel)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_phy *rtlphy = &rtlpriv->phy;

	rtlphy->cur_cck_txpwridx = cckpowerlevel[0];
	rtlphy->cur_ofdm24g_txpwridx = ofdmpowerlevel[0];
	rtlphy->cur_bw20_txpwridx = bw20powerlevel[0];
	rtlphy->cur_bw40_txpwridx = bw40powerlevel[0];

}