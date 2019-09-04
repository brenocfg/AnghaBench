#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct rtl_ps_ctl {int fw_current_inpsmode; scalar_t__ rfpwr_state; } ;
struct TYPE_12__ {int being_init_adapter; } ;
struct TYPE_7__ {int btcoexist; } ;
struct TYPE_8__ {TYPE_1__ btc_info; } ;
struct rtl_phy {int* rfreg_chnlval; int backup_rf_0x1a; int iqk_initialized; int* rfpath_rx_enable; scalar_t__ rf_type; } ;
struct rtl_priv {TYPE_6__ rtlhal; TYPE_5__* intf_ops; TYPE_4__* cfg; TYPE_2__ btcoexist; struct rtl_phy phy; } ;
struct rtl_mac {int /*<<< orphan*/  mac_addr; } ;
struct rtl_hal {int mac_func_enable; int fw_ready; int fw_clk_change_in_progress; int allow_sw_to_change_hwclc; scalar_t__ last_hmeboxnum; void* fw_ps_state; scalar_t__ rx_tag; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_11__ {int /*<<< orphan*/  (* enable_aspm ) (struct ieee80211_hw*) ;int /*<<< orphan*/  (* disable_aspm ) (struct ieee80211_hw*) ;} ;
struct TYPE_10__ {TYPE_3__* ops; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* set_hw_reg ) (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BCCKEN ; 
 int BIT (int) ; 
 int /*<<< orphan*/  BOFDMEN ; 
 int /*<<< orphan*/  COMP_ERR ; 
 int /*<<< orphan*/  COMP_INIT ; 
 int /*<<< orphan*/  DBG_DMESG ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  DBG_WARNING ; 
 scalar_t__ ERFON ; 
 void* FW_PS_STATE_ALL_ON_92E ; 
 int /*<<< orphan*/  HW_VAR_ETHER_ADDR ; 
 int REG_AFE_CTRL2 ; 
 int REG_AFE_CTRL4 ; 
 scalar_t__ REG_CR ; 
 int REG_NAV_UPPER ; 
 int /*<<< orphan*/  REG_PCIE_CTRL_REG ; 
 scalar_t__ REG_SYS_CLKR ; 
 int REG_SYS_SWR_CTRL1 ; 
 int REG_SYS_SWR_CTRL2 ; 
 int /*<<< orphan*/  RF90_PATH_A ; 
 int /*<<< orphan*/  RF90_PATH_B ; 
 int /*<<< orphan*/  RFPGA0_RFMOD ; 
 int RFREG_OFFSET_MASK ; 
 scalar_t__ RF_2T2R ; 
 int RF_CHNLBW ; 
 int RF_RX_G1 ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ _rtl8192ee_check_pcie_dma_hang (struct rtl_priv*) ; 
 int /*<<< orphan*/  _rtl8192ee_reset_pcie_interface_dma (struct rtl_priv*,int) ; 
 int /*<<< orphan*/  _rtl92ee_enable_aspm_back_door (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  _rtl92ee_hw_configure (struct ieee80211_hw*) ; 
 int _rtl92ee_init_mac (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  efuse_one_byte_read (struct ieee80211_hw*,int,int*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  rtl92ee_bt_hw_init (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl92ee_dm_init (struct ieee80211_hw*) ; 
 int rtl92ee_download_fw (struct ieee80211_hw*,int) ; 
 int /*<<< orphan*/  rtl92ee_enable_hw_security_config (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl92ee_phy_bb_config (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl92ee_phy_iq_calibrate (struct ieee80211_hw*,int) ; 
 int /*<<< orphan*/  rtl92ee_phy_mac_config (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl92ee_phy_rf_config (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_cam_reset_all_entry (struct ieee80211_hw*) ; 
 void* rtl_get_rfreg (struct ieee80211_hw*,int /*<<< orphan*/ ,int,int) ; 
 struct rtl_hal* rtl_hal (struct rtl_priv*) ; 
 struct rtl_mac* rtl_mac (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 struct rtl_ps_ctl* rtl_psc (struct rtl_priv*) ; 
 int rtl_read_byte (struct rtl_priv*,scalar_t__) ; 
 int rtl_read_dword (struct rtl_priv*,int) ; 
 int /*<<< orphan*/  rtl_set_bbreg (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtl_set_rfreg (struct ieee80211_hw*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  rtl_write_byte (struct rtl_priv*,int,int) ; 
 int /*<<< orphan*/  rtl_write_dword (struct rtl_priv*,int,int) ; 
 int /*<<< orphan*/  rtl_write_word (struct rtl_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  stub2 (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct ieee80211_hw*) ; 

int rtl92ee_hw_init(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	struct rtl_mac *mac = rtl_mac(rtl_priv(hw));
	struct rtl_phy *rtlphy = &rtlpriv->phy;
	struct rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	bool rtstatus = true;
	int err = 0;
	u8 tmp_u1b, u1byte;
	u32 tmp_u4b;

	RT_TRACE(rtlpriv, COMP_INIT, DBG_LOUD, " Rtl8192EE hw init\n");
	rtlpriv->rtlhal.being_init_adapter = true;
	rtlpriv->intf_ops->disable_aspm(hw);

	tmp_u1b = rtl_read_byte(rtlpriv, REG_SYS_CLKR+1);
	u1byte = rtl_read_byte(rtlpriv, REG_CR);
	if ((tmp_u1b & BIT(3)) && (u1byte != 0 && u1byte != 0xEA)) {
		rtlhal->mac_func_enable = true;
	} else {
		rtlhal->mac_func_enable = false;
		rtlhal->fw_ps_state = FW_PS_STATE_ALL_ON_92E;
	}

	if (_rtl8192ee_check_pcie_dma_hang(rtlpriv)) {
		RT_TRACE(rtlpriv, COMP_INIT, DBG_DMESG, "92ee dma hang!\n");
		_rtl8192ee_reset_pcie_interface_dma(rtlpriv,
						    rtlhal->mac_func_enable);
		rtlhal->mac_func_enable = false;
	}

	rtstatus = _rtl92ee_init_mac(hw);

	rtl_write_byte(rtlpriv, 0x577, 0x03);

	/*for Crystal 40 Mhz setting */
	rtl_write_byte(rtlpriv, REG_AFE_CTRL4, 0x2A);
	rtl_write_byte(rtlpriv, REG_AFE_CTRL4 + 1, 0x00);
	rtl_write_byte(rtlpriv, REG_AFE_CTRL2, 0x83);

	/*Forced the antenna b to wifi */
	if (rtlpriv->btcoexist.btc_info.btcoexist == 1) {
		rtl_write_byte(rtlpriv, 0x64, 0);
		rtl_write_byte(rtlpriv, 0x65, 1);
	}
	if (!rtstatus) {
		pr_err("Init MAC failed\n");
		err = 1;
		return err;
	}
	rtlhal->rx_tag = 0;
	rtl_write_word(rtlpriv, REG_PCIE_CTRL_REG, 0x8000);
	err = rtl92ee_download_fw(hw, false);
	if (err) {
		RT_TRACE(rtlpriv, COMP_ERR, DBG_WARNING,
			 "Failed to download FW. Init HW without FW now..\n");
		err = 1;
		rtlhal->fw_ready = false;
		return err;
	}
	rtlhal->fw_ready = true;
	/*fw related variable initialize */
	ppsc->fw_current_inpsmode = false;
	rtlhal->fw_ps_state = FW_PS_STATE_ALL_ON_92E;
	rtlhal->fw_clk_change_in_progress = false;
	rtlhal->allow_sw_to_change_hwclc = false;
	rtlhal->last_hmeboxnum = 0;

	rtl92ee_phy_mac_config(hw);

	rtl92ee_phy_bb_config(hw);

	rtl92ee_phy_rf_config(hw);

	rtlphy->rfreg_chnlval[0] = rtl_get_rfreg(hw, RF90_PATH_A,
						 RF_CHNLBW, RFREG_OFFSET_MASK);
	rtlphy->rfreg_chnlval[1] = rtl_get_rfreg(hw, RF90_PATH_B,
						 RF_CHNLBW, RFREG_OFFSET_MASK);
	rtlphy->backup_rf_0x1a = (u32)rtl_get_rfreg(hw, RF90_PATH_A, RF_RX_G1,
						    RFREG_OFFSET_MASK);
	rtlphy->rfreg_chnlval[0] = (rtlphy->rfreg_chnlval[0] & 0xfffff3ff) |
				   BIT(10) | BIT(11);

	rtl_set_rfreg(hw, RF90_PATH_A, RF_CHNLBW, RFREG_OFFSET_MASK,
		      rtlphy->rfreg_chnlval[0]);
	rtl_set_rfreg(hw, RF90_PATH_B, RF_CHNLBW, RFREG_OFFSET_MASK,
		      rtlphy->rfreg_chnlval[0]);

	/*---- Set CCK and OFDM Block "ON"----*/
	rtl_set_bbreg(hw, RFPGA0_RFMOD, BCCKEN, 0x1);
	rtl_set_bbreg(hw, RFPGA0_RFMOD, BOFDMEN, 0x1);

	/* Must set this,
	 * otherwise the rx sensitivity will be very pool. Maddest
	 */
	rtl_set_rfreg(hw, RF90_PATH_A, 0xB1, RFREG_OFFSET_MASK, 0x54418);

	/*Set Hardware(MAC default setting.)*/
	_rtl92ee_hw_configure(hw);

	rtlhal->mac_func_enable = true;

	rtl_cam_reset_all_entry(hw);
	rtl92ee_enable_hw_security_config(hw);

	ppsc->rfpwr_state = ERFON;

	rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_ETHER_ADDR, mac->mac_addr);
	_rtl92ee_enable_aspm_back_door(hw);
	rtlpriv->intf_ops->enable_aspm(hw);

	rtl92ee_bt_hw_init(hw);

	rtlpriv->rtlhal.being_init_adapter = false;

	if (ppsc->rfpwr_state == ERFON) {
		if (rtlphy->iqk_initialized) {
			rtl92ee_phy_iq_calibrate(hw, true);
		} else {
			rtl92ee_phy_iq_calibrate(hw, false);
			rtlphy->iqk_initialized = true;
		}
	}

	rtlphy->rfpath_rx_enable[0] = true;
	if (rtlphy->rf_type == RF_2T2R)
		rtlphy->rfpath_rx_enable[1] = true;

	efuse_one_byte_read(hw, 0x1FA, &tmp_u1b);
	if (!(tmp_u1b & BIT(0))) {
		rtl_set_rfreg(hw, RF90_PATH_A, 0x15, 0x0F, 0x05);
		RT_TRACE(rtlpriv, COMP_INIT, DBG_LOUD, "PA BIAS path A\n");
	}

	if ((!(tmp_u1b & BIT(1))) && (rtlphy->rf_type == RF_2T2R)) {
		rtl_set_rfreg(hw, RF90_PATH_B, 0x15, 0x0F, 0x05);
		RT_TRACE(rtlpriv, COMP_INIT, DBG_LOUD, "PA BIAS path B\n");
	}

	rtl_write_byte(rtlpriv, REG_NAV_UPPER, ((30000 + 127) / 128));

	/*Fixed LDPC rx hang issue. */
	tmp_u4b = rtl_read_dword(rtlpriv, REG_SYS_SWR_CTRL1);
	rtl_write_byte(rtlpriv, REG_SYS_SWR_CTRL2, 0x75);
	tmp_u4b =  (tmp_u4b & 0xfff00fff) | (0x7E << 12);
	rtl_write_dword(rtlpriv, REG_SYS_SWR_CTRL1, tmp_u4b);

	rtl92ee_dm_init(hw);

	rtl_write_dword(rtlpriv, 0x4fc, 0);

	RT_TRACE(rtlpriv, COMP_INIT, DBG_LOUD,
		 "end of Rtl8192EE hw init %x\n", err);
	return 0;
}