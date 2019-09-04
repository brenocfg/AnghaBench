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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct rtl_phy {scalar_t__ num_total_rfpath; } ;
struct rtl_priv {struct rtl_phy phy; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DESC_RATEMCS7 ; 
 int RA_TXPWRTRAING ; 
 int RB_TXPWRTRAING ; 
 scalar_t__ RF90_PATH_A ; 
 scalar_t__ RF90_PATH_B ; 
 int _rtl8821ae_get_txpower_index (struct ieee80211_hw*,scalar_t__,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_set_bbreg (struct ieee80211_hw*,int,int,int) ; 

__attribute__((used)) static void _rtl8821ae_phy_txpower_training_by_path(struct ieee80211_hw *hw,
						    u8 bw, u8 channel, u8 path)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_phy *rtlphy = &rtlpriv->phy;

	u8 i;
	u32 power_level, data, offset;

	if (path >= rtlphy->num_total_rfpath)
		return;

	data = 0;
	if (path == RF90_PATH_A) {
		power_level =
			_rtl8821ae_get_txpower_index(hw, RF90_PATH_A,
			DESC_RATEMCS7, bw, channel);
		offset =  RA_TXPWRTRAING;
	} else {
		power_level =
			_rtl8821ae_get_txpower_index(hw, RF90_PATH_B,
			DESC_RATEMCS7, bw, channel);
		offset =  RB_TXPWRTRAING;
	}

	for (i = 0; i < 3; i++) {
		if (i == 0)
			power_level = power_level - 10;
		else if (i == 1)
			power_level = power_level - 8;
		else
			power_level = power_level - 6;

		data |= (((power_level > 2) ? (power_level) : 2) << (i * 8));
	}
	rtl_set_bbreg(hw, offset, 0xffffff, data);
}