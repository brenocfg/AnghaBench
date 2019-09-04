#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {int assoc_id; } ;
struct TYPE_3__ {int dm_flag; int /*<<< orphan*/  dynamic_txpower_enable; } ;
struct rtl_phy {int /*<<< orphan*/  current_channel; } ;
struct rtl_priv {TYPE_2__ mac80211; TYPE_1__ dm; struct rtl_phy phy; } ;
struct rtl_hal {int current_fwcmd_io; int set_fwcmd_inprogress; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_CMD ; 
 int /*<<< orphan*/  DBG_DMESG ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int FW_ADD_A2_ENTRY ; 
#define  FW_CMD_ADD_A2_ENTRY 142 
#define  FW_CMD_CTRL_DM_BY_DRIVER 141 
#define  FW_CMD_HIGH_PWR_DISABLE 140 
#define  FW_CMD_HIGH_PWR_ENABLE 139 
#define  FW_CMD_IQK_ENABLE 138 
#define  FW_CMD_LPS_ENTER 137 
#define  FW_CMD_LPS_LEAVE 136 
#define  FW_CMD_PAUSE_DM_BY_SCAN 135 
#define  FW_CMD_RA_ACTIVE 134 
#define  FW_CMD_RA_REFRESH_BG 133 
#define  FW_CMD_RA_REFRESH_BG_COMB 132 
#define  FW_CMD_RA_REFRESH_N 131 
#define  FW_CMD_RA_REFRESH_N_COMB 130 
#define  FW_CMD_RA_RESET 129 
#define  FW_CMD_RESUME_DM_BY_SCAN 128 
 int FW_CTRL_DM_BY_DRIVER ; 
 int FW_IQK_ENABLE ; 
 int FW_LPS_ENTER ; 
 int FW_LPS_LEAVE ; 
 int FW_RA_ACTIVE ; 
 int FW_RA_DISABLE_RSSI_MASK ; 
 int FW_RA_ENABLE_RSSI_MASK ; 
 int FW_RA_IOT_BG_COMB ; 
 int FW_RA_IOT_N_COMB ; 
 int FW_RA_REFRESH ; 
 int FW_RA_RESET ; 
 int HAL_DM_HIPWR_DISABLE ; 
 int /*<<< orphan*/  MASKBYTE0 ; 
 int /*<<< orphan*/  MASKBYTE2 ; 
 int /*<<< orphan*/  RCCK0_CCA ; 
 int /*<<< orphan*/  ROFDM0_XAAGCCORE1 ; 
 int /*<<< orphan*/  ROFDM0_XBAGCCORE1 ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  WFM5 ; 
 int hal_get_firmwareversion (struct rtl_priv*) ; 
 scalar_t__ is_hal_stop (struct rtl_hal*) ; 
 int /*<<< orphan*/  rtl92s_phy_chk_fwcmd_iodone (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl92s_phy_set_txpower (struct ieee80211_hw*,int /*<<< orphan*/ ) ; 
 struct rtl_hal* rtl_hal (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_set_bbreg (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtl_write_dword (struct rtl_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void _rtl92s_phy_set_fwcmd_io(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	struct rtl_phy *rtlphy = &(rtlpriv->phy);
	u32 input, current_aid = 0;

	if (is_hal_stop(rtlhal))
		return;

	if (hal_get_firmwareversion(rtlpriv) < 0x34)
		goto skip;
	/* We re-map RA related CMD IO to combinational ones */
	/* if FW version is v.52 or later. */
	switch (rtlhal->current_fwcmd_io) {
	case FW_CMD_RA_REFRESH_N:
		rtlhal->current_fwcmd_io = FW_CMD_RA_REFRESH_N_COMB;
		break;
	case FW_CMD_RA_REFRESH_BG:
		rtlhal->current_fwcmd_io = FW_CMD_RA_REFRESH_BG_COMB;
		break;
	default:
		break;
	}

skip:
	switch (rtlhal->current_fwcmd_io) {
	case FW_CMD_RA_RESET:
		RT_TRACE(rtlpriv, COMP_CMD, DBG_DMESG, "FW_CMD_RA_RESET\n");
		rtl_write_dword(rtlpriv, WFM5, FW_RA_RESET);
		rtl92s_phy_chk_fwcmd_iodone(hw);
		break;
	case FW_CMD_RA_ACTIVE:
		RT_TRACE(rtlpriv, COMP_CMD, DBG_DMESG, "FW_CMD_RA_ACTIVE\n");
		rtl_write_dword(rtlpriv, WFM5, FW_RA_ACTIVE);
		rtl92s_phy_chk_fwcmd_iodone(hw);
		break;
	case FW_CMD_RA_REFRESH_N:
		RT_TRACE(rtlpriv, COMP_CMD, DBG_DMESG, "FW_CMD_RA_REFRESH_N\n");
		input = FW_RA_REFRESH;
		rtl_write_dword(rtlpriv, WFM5, input);
		rtl92s_phy_chk_fwcmd_iodone(hw);
		rtl_write_dword(rtlpriv, WFM5, FW_RA_ENABLE_RSSI_MASK);
		rtl92s_phy_chk_fwcmd_iodone(hw);
		break;
	case FW_CMD_RA_REFRESH_BG:
		RT_TRACE(rtlpriv, COMP_CMD, DBG_DMESG,
			 "FW_CMD_RA_REFRESH_BG\n");
		rtl_write_dword(rtlpriv, WFM5, FW_RA_REFRESH);
		rtl92s_phy_chk_fwcmd_iodone(hw);
		rtl_write_dword(rtlpriv, WFM5, FW_RA_DISABLE_RSSI_MASK);
		rtl92s_phy_chk_fwcmd_iodone(hw);
		break;
	case FW_CMD_RA_REFRESH_N_COMB:
		RT_TRACE(rtlpriv, COMP_CMD, DBG_DMESG,
			 "FW_CMD_RA_REFRESH_N_COMB\n");
		input = FW_RA_IOT_N_COMB;
		rtl_write_dword(rtlpriv, WFM5, input);
		rtl92s_phy_chk_fwcmd_iodone(hw);
		break;
	case FW_CMD_RA_REFRESH_BG_COMB:
		RT_TRACE(rtlpriv, COMP_CMD, DBG_DMESG,
			 "FW_CMD_RA_REFRESH_BG_COMB\n");
		input = FW_RA_IOT_BG_COMB;
		rtl_write_dword(rtlpriv, WFM5, input);
		rtl92s_phy_chk_fwcmd_iodone(hw);
		break;
	case FW_CMD_IQK_ENABLE:
		RT_TRACE(rtlpriv, COMP_CMD, DBG_DMESG, "FW_CMD_IQK_ENABLE\n");
		rtl_write_dword(rtlpriv, WFM5, FW_IQK_ENABLE);
		rtl92s_phy_chk_fwcmd_iodone(hw);
		break;
	case FW_CMD_PAUSE_DM_BY_SCAN:
		/* Lower initial gain */
		rtl_set_bbreg(hw, ROFDM0_XAAGCCORE1, MASKBYTE0, 0x17);
		rtl_set_bbreg(hw, ROFDM0_XBAGCCORE1, MASKBYTE0, 0x17);
		/* CCA threshold */
		rtl_set_bbreg(hw, RCCK0_CCA, MASKBYTE2, 0x40);
		break;
	case FW_CMD_RESUME_DM_BY_SCAN:
		/* CCA threshold */
		rtl_set_bbreg(hw, RCCK0_CCA, MASKBYTE2, 0xcd);
		rtl92s_phy_set_txpower(hw, rtlphy->current_channel);
		break;
	case FW_CMD_HIGH_PWR_DISABLE:
		if (rtlpriv->dm.dm_flag & HAL_DM_HIPWR_DISABLE)
			break;

		/* Lower initial gain */
		rtl_set_bbreg(hw, ROFDM0_XAAGCCORE1, MASKBYTE0, 0x17);
		rtl_set_bbreg(hw, ROFDM0_XBAGCCORE1, MASKBYTE0, 0x17);
		/* CCA threshold */
		rtl_set_bbreg(hw, RCCK0_CCA, MASKBYTE2, 0x40);
		break;
	case FW_CMD_HIGH_PWR_ENABLE:
		if ((rtlpriv->dm.dm_flag & HAL_DM_HIPWR_DISABLE) ||
			rtlpriv->dm.dynamic_txpower_enable)
			break;

		/* CCA threshold */
		rtl_set_bbreg(hw, RCCK0_CCA, MASKBYTE2, 0xcd);
		break;
	case FW_CMD_LPS_ENTER:
		RT_TRACE(rtlpriv, COMP_CMD, DBG_DMESG, "FW_CMD_LPS_ENTER\n");
		current_aid = rtlpriv->mac80211.assoc_id;
		rtl_write_dword(rtlpriv, WFM5, (FW_LPS_ENTER |
				((current_aid | 0xc000) << 8)));
		rtl92s_phy_chk_fwcmd_iodone(hw);
		/* FW set TXOP disable here, so disable EDCA
		 * turbo mode until driver leave LPS */
		break;
	case FW_CMD_LPS_LEAVE:
		RT_TRACE(rtlpriv, COMP_CMD, DBG_DMESG, "FW_CMD_LPS_LEAVE\n");
		rtl_write_dword(rtlpriv, WFM5, FW_LPS_LEAVE);
		rtl92s_phy_chk_fwcmd_iodone(hw);
		break;
	case FW_CMD_ADD_A2_ENTRY:
		RT_TRACE(rtlpriv, COMP_CMD, DBG_DMESG, "FW_CMD_ADD_A2_ENTRY\n");
		rtl_write_dword(rtlpriv, WFM5, FW_ADD_A2_ENTRY);
		rtl92s_phy_chk_fwcmd_iodone(hw);
		break;
	case FW_CMD_CTRL_DM_BY_DRIVER:
		RT_TRACE(rtlpriv, COMP_CMD, DBG_LOUD,
			 "FW_CMD_CTRL_DM_BY_DRIVER\n");
		rtl_write_dword(rtlpriv, WFM5, FW_CTRL_DM_BY_DRIVER);
		rtl92s_phy_chk_fwcmd_iodone(hw);
		break;

	default:
		break;
	}

	rtl92s_phy_chk_fwcmd_iodone(hw);

	/* Clear FW CMD operation flag. */
	rtlhal->set_fwcmd_inprogress = false;
}