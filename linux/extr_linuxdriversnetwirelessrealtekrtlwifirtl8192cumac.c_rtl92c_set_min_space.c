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
typedef  int /*<<< orphan*/  u8 ;
struct rtl_priv {int dummy; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_MSS_DENSITY_1T ; 
 int /*<<< orphan*/  MAX_MSS_DENSITY_2T ; 
 int /*<<< orphan*/  REG_AMPDU_MIN_SPACE ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_write_byte (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void rtl92c_set_min_space(struct ieee80211_hw *hw, bool is2T)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	u8 value = is2T ? MAX_MSS_DENSITY_2T : MAX_MSS_DENSITY_1T;

	rtl_write_byte(rtlpriv, REG_AMPDU_MIN_SPACE, value);
}