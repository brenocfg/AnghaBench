#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct dig_t {int cur_igvalue; int cur_cck_cca_thres; } ;
struct TYPE_2__ {int xaagccore1; int cca; } ;
struct rtl_phy {int current_io_type; int set_io_inprogress; TYPE_1__ initgain_backup; int /*<<< orphan*/  current_channel; } ;
struct rtl_priv {struct dig_t dm_digtable; struct rtl_phy phy; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_CMD ; 
 int /*<<< orphan*/  COMP_ERR ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  DBG_TRACE ; 
#define  IO_CMD_PAUSE_BAND0_DM_BY_SCAN 129 
#define  IO_CMD_RESUME_DM_BY_SCAN 128 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  rtl92ee_dm_write_cck_cca_thres (struct ieee80211_hw*,int) ; 
 int /*<<< orphan*/  rtl92ee_dm_write_dig (struct ieee80211_hw*,int) ; 
 int /*<<< orphan*/  rtl92ee_phy_set_txpower_level (struct ieee80211_hw*,int /*<<< orphan*/ ) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static void rtl92ee_phy_set_io(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_phy *rtlphy = &rtlpriv->phy;
	struct dig_t *dm_dig = &rtlpriv->dm_digtable;

	RT_TRACE(rtlpriv, COMP_CMD, DBG_TRACE,
		 "--->Cmd(%#x), set_io_inprogress(%d)\n",
		  rtlphy->current_io_type, rtlphy->set_io_inprogress);
	switch (rtlphy->current_io_type) {
	case IO_CMD_RESUME_DM_BY_SCAN:
		rtl92ee_dm_write_dig(hw, rtlphy->initgain_backup.xaagccore1);
		rtl92ee_dm_write_cck_cca_thres(hw, rtlphy->initgain_backup.cca);
		RT_TRACE(rtlpriv, COMP_CMD, DBG_TRACE , "no set txpower\n");
		rtl92ee_phy_set_txpower_level(hw, rtlphy->current_channel);
		break;
	case IO_CMD_PAUSE_BAND0_DM_BY_SCAN:
		/* 8192eebt */
		rtlphy->initgain_backup.xaagccore1 = dm_dig->cur_igvalue;
		rtl92ee_dm_write_dig(hw, 0x17);
		rtlphy->initgain_backup.cca = dm_dig->cur_cck_cca_thres;
		rtl92ee_dm_write_cck_cca_thres(hw, 0x40);
		break;
	default:
		RT_TRACE(rtlpriv, COMP_ERR, DBG_LOUD,
			 "switch case %#x not processed\n",
			 rtlphy->current_io_type);
		break;
	}
	rtlphy->set_io_inprogress = false;
	RT_TRACE(rtlpriv, COMP_CMD, DBG_TRACE,
		 "(%#x)\n", rtlphy->current_io_type);
}