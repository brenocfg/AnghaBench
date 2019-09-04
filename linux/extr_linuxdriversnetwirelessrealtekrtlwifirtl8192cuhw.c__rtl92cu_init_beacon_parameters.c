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
struct rtl_priv {int dummy; } ;
struct rtl_hal {int /*<<< orphan*/  version; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCN_DMA_ATIME_INT_TIME ; 
 int /*<<< orphan*/  DRIVER_EARLY_INT_TIME ; 
 scalar_t__ IS_NORMAL_CHIP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_BCNDMATIM ; 
 int /*<<< orphan*/  REG_BCNTCFG ; 
 int /*<<< orphan*/  REG_BCN_CTRL ; 
 int /*<<< orphan*/  REG_DRVERLYINT ; 
 int /*<<< orphan*/  REG_TBTT_PROHIBIT ; 
 struct rtl_hal* rtl_hal (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_write_byte (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_write_word (struct rtl_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void _rtl92cu_init_beacon_parameters(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_hal *rtlhal = rtl_hal(rtlpriv);

	rtl_write_word(rtlpriv, REG_BCN_CTRL, 0x1010);

	/* TODO: Remove these magic number */
	rtl_write_word(rtlpriv, REG_TBTT_PROHIBIT, 0x6404);
	rtl_write_byte(rtlpriv, REG_DRVERLYINT, DRIVER_EARLY_INT_TIME);
	rtl_write_byte(rtlpriv, REG_BCNDMATIM, BCN_DMA_ATIME_INT_TIME);
	/* Change beacon AIFS to the largest number
	 * beacause test chip does not contension before sending beacon.
	 */
	if (IS_NORMAL_CHIP(rtlhal->version))
		rtl_write_word(rtlpriv, REG_BCNTCFG, 0x660F);
	else
		rtl_write_word(rtlpriv, REG_BCNTCFG, 0x66FF);
}