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
struct rtl_phy {int current_io_type; int set_io_inprogress; } ;
struct rtl_priv {struct rtl_phy phy; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_CMD ; 
 int /*<<< orphan*/  DBG_TRACE ; 
#define  IO_CMD_PAUSE_BAND0_DM_BY_SCAN 130 
#define  IO_CMD_PAUSE_BAND1_DM_BY_SCAN 129 
#define  IO_CMD_RESUME_DM_BY_SCAN 128 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static void rtl8822be_phy_set_io(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_phy *rtlphy = &rtlpriv->phy;

	RT_TRACE(rtlpriv, COMP_CMD, DBG_TRACE,
		 "--->Cmd(%#x), set_io_inprogress(%d)\n",
		 rtlphy->current_io_type, rtlphy->set_io_inprogress);
	switch (rtlphy->current_io_type) {
	case IO_CMD_RESUME_DM_BY_SCAN:
		break;
	case IO_CMD_PAUSE_BAND0_DM_BY_SCAN:
		break;
	case IO_CMD_PAUSE_BAND1_DM_BY_SCAN:
		break;
	default:
		pr_err("switch case not process\n");
		break;
	}
	rtlphy->set_io_inprogress = false;
	RT_TRACE(rtlpriv, COMP_CMD, DBG_TRACE, "(%#x)\n",
		 rtlphy->current_io_type);
}