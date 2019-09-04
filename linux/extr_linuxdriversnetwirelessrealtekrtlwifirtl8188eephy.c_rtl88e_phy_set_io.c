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
struct dig_t {int cur_igvalue; } ;
struct TYPE_2__ {int xaagccore1; } ;
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
 int /*<<< orphan*/  RCCK0_CCA ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  rtl88e_phy_set_txpower_level (struct ieee80211_hw*,int /*<<< orphan*/ ) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_set_bbreg (struct ieee80211_hw*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void rtl88e_phy_set_io(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_phy *rtlphy = &rtlpriv->phy;
	struct dig_t *dm_digtable = &rtlpriv->dm_digtable;

	RT_TRACE(rtlpriv, COMP_CMD, DBG_TRACE,
		 "--->Cmd(%#x), set_io_inprogress(%d)\n",
		  rtlphy->current_io_type, rtlphy->set_io_inprogress);
	switch (rtlphy->current_io_type) {
	case IO_CMD_RESUME_DM_BY_SCAN:
		dm_digtable->cur_igvalue = rtlphy->initgain_backup.xaagccore1;
		/*rtl92c_dm_write_dig(hw);*/
		rtl88e_phy_set_txpower_level(hw, rtlphy->current_channel);
		rtl_set_bbreg(hw, RCCK0_CCA, 0xff0000, 0x83);
		break;
	case IO_CMD_PAUSE_BAND0_DM_BY_SCAN:
		rtlphy->initgain_backup.xaagccore1 = dm_digtable->cur_igvalue;
		dm_digtable->cur_igvalue = 0x17;
		rtl_set_bbreg(hw, RCCK0_CCA, 0xff0000, 0x40);
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