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
typedef  int u32 ;
struct rtl_priv {int dummy; } ;
struct ieee80211_hw {int dummy; } ;
typedef  enum radio_path { ____Placeholder_radio_path } radio_path ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  COMP_IQK ; 
 int /*<<< orphan*/  DBG_LOUD ; 
#define  RF90_PATH_A 128 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int) ; 
 int rtl_get_bbreg (struct ieee80211_hw*,int,int) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_set_bbreg (struct ieee80211_hw*,int,int,int) ; 
 int /*<<< orphan*/  rtl_write_dword (struct rtl_priv*,int,int) ; 

__attribute__((used)) static void _rtl8821ae_iqk_tx_fill_iqc(struct ieee80211_hw *hw,
				       enum radio_path path, u32 tx_x, u32 tx_y)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	switch (path) {
	case RF90_PATH_A:
		/* [31] = 1 --> Page C1 */
		rtl_set_bbreg(hw, 0x82c, BIT(31), 0x1);
		rtl_write_dword(rtlpriv, 0xc90, 0x00000080);
		rtl_write_dword(rtlpriv, 0xcc4, 0x20040000);
		rtl_write_dword(rtlpriv, 0xcc8, 0x20000000);
		rtl_set_bbreg(hw, 0xccc, 0x000007ff, tx_y);
		rtl_set_bbreg(hw, 0xcd4, 0x000007ff, tx_x);
		RT_TRACE(rtlpriv, COMP_IQK, DBG_LOUD,
			 "TX_X = %x;;TX_Y = %x =====> fill to IQC\n",
			 tx_x, tx_y);
		RT_TRACE(rtlpriv, COMP_IQK, DBG_LOUD,
			 "0xcd4 = %x;;0xccc = %x ====>fill to IQC\n",
			 rtl_get_bbreg(hw, 0xcd4, 0x000007ff),
			 rtl_get_bbreg(hw, 0xccc, 0x000007ff));
		break;
	default:
		break;
	}
}