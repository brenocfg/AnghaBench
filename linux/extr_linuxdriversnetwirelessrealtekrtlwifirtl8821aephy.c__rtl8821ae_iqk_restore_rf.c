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
typedef  size_t u32 ;
struct rtl_priv {int dummy; } ;
struct ieee80211_hw {int dummy; } ;
typedef  enum radio_path { ____Placeholder_radio_path } radio_path ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  COMP_IQK ; 
 int /*<<< orphan*/  DBG_LOUD ; 
#define  RF90_PATH_A 128 
 int /*<<< orphan*/  RFREG_OFFSET_MASK ; 
 size_t RF_REG_NUM ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_set_bbreg (struct ieee80211_hw*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtl_set_rfreg (struct ieee80211_hw*,int,size_t,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static void _rtl8821ae_iqk_restore_rf(struct ieee80211_hw *hw,
				      enum radio_path path,
				      u32 *backup_rf_reg,
				      u32 *rf_backup, u32 rf_reg_num)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	u32 i;

	rtl_set_bbreg(hw, 0x82c, BIT(31), 0x0); /* [31] = 0 --> Page C */
	for (i = 0; i < RF_REG_NUM; i++)
		rtl_set_rfreg(hw, path, backup_rf_reg[i], RFREG_OFFSET_MASK,
			      rf_backup[i]);

	switch (path) {
	case RF90_PATH_A:
		RT_TRACE(rtlpriv, COMP_IQK, DBG_LOUD,
			 "RestoreRF Path A Success!!!!\n");
		break;
	default:
			break;
	}
}