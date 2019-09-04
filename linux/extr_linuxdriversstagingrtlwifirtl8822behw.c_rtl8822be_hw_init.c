#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
typedef  int u8 ;
typedef  scalar_t__ u32 ;
struct rtl_ps_ctl {int fw_current_inpsmode; int /*<<< orphan*/  rfpwr_state; } ;
struct TYPE_11__ {TYPE_9__* ops; } ;
struct TYPE_19__ {int being_init_adapter; } ;
struct TYPE_18__ {TYPE_6__* btc_ops; } ;
struct TYPE_13__ {TYPE_1__* ops; } ;
struct rtl_phy {int* rfreg_chnlval; scalar_t__ backup_rf_0x1a; } ;
struct rtl_priv {TYPE_10__ phydm; TYPE_8__ rtlhal; TYPE_7__ btcoexist; TYPE_5__* cfg; TYPE_3__* intf_ops; TYPE_2__ halmac; struct rtl_phy phy; } ;
struct rtl_pci {int receive_config; } ;
struct rtl_mac {int /*<<< orphan*/  mac_addr; } ;
struct rtl_hal {int mac_func_enable; int fw_ready; int fw_clk_change_in_progress; int allow_sw_to_change_hwclc; scalar_t__ last_hmeboxnum; int /*<<< orphan*/  fw_ps_state; scalar_t__ rx_tag; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_20__ {int /*<<< orphan*/  (* phydm_init_dm ) (struct rtl_priv*) ;} ;
struct TYPE_17__ {int /*<<< orphan*/  (* btc_init_hw_config_wifi_only ) (struct rtl_priv*) ;int /*<<< orphan*/  (* btc_init_hw_config ) (struct rtl_priv*) ;int /*<<< orphan*/  (* btc_power_on_setting ) (struct rtl_priv*) ;} ;
struct TYPE_16__ {TYPE_4__* ops; } ;
struct TYPE_15__ {scalar_t__ (* get_btc_status ) () ;int /*<<< orphan*/  (* set_hw_reg ) (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_14__ {int /*<<< orphan*/  (* enable_aspm ) (struct ieee80211_hw*) ;int /*<<< orphan*/  (* disable_aspm ) (struct ieee80211_hw*) ;} ;
struct TYPE_12__ {int (* halmac_init_hal ) (struct rtl_priv*) ;} ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  COMP_INIT ; 
 int /*<<< orphan*/  DBG_DMESG ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  ERFON ; 
 int /*<<< orphan*/  FW_PS_STATE_ALL_ON_8822B ; 
 int /*<<< orphan*/  HW_VAR_ETHER_ADDR ; 
 int RCR_ACRC32 ; 
 int RCR_AICV ; 
 int /*<<< orphan*/  REG_HISR0_8822B ; 
 scalar_t__ REG_PCIE_CTRL_8822B ; 
 int /*<<< orphan*/  REG_RCR_8822B ; 
 int /*<<< orphan*/  REG_RXFLTMAP1_8822B ; 
 scalar_t__ REG_RX_DRVINFO_SZ_8822B ; 
 int /*<<< orphan*/  RF90_PATH_A ; 
 int /*<<< orphan*/  RF90_PATH_B ; 
 int /*<<< orphan*/  RFREG_OFFSET_MASK ; 
 int /*<<< orphan*/  RF_CHNLBW ; 
 int /*<<< orphan*/  RF_RX_G1 ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ _rtl8822be_check_pcie_dma_hang (struct rtl_priv*) ; 
 int /*<<< orphan*/  _rtl8822be_enable_aspm_back_door (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  _rtl8822be_init_trxbd (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  _rtl8822be_reset_pcie_interface_dma (struct rtl_priv*,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  rtl8822be_enable_hw_security_config (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_cam_reset_all_entry (struct ieee80211_hw*) ; 
 void* rtl_get_rfreg (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rtl_hal* rtl_hal (struct rtl_priv*) ; 
 struct rtl_mac* rtl_mac (struct rtl_priv*) ; 
 struct rtl_pci* rtl_pcidev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_pcipriv (struct ieee80211_hw*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 struct rtl_ps_ctl* rtl_psc (struct rtl_priv*) ; 
 int rtl_read_byte (struct rtl_priv*,scalar_t__) ; 
 int rtl_read_dword (struct rtl_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_write_byte (struct rtl_priv*,scalar_t__,int) ; 
 int /*<<< orphan*/  rtl_write_dword (struct rtl_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtl_write_word (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  stub10 (struct rtl_priv*) ; 
 int stub2 (struct rtl_priv*) ; 
 scalar_t__ stub3 () ; 
 int /*<<< orphan*/  stub4 (struct rtl_priv*) ; 
 int /*<<< orphan*/  stub5 (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (struct ieee80211_hw*) ; 
 scalar_t__ stub7 () ; 
 int /*<<< orphan*/  stub8 (struct rtl_priv*) ; 
 int /*<<< orphan*/  stub9 (struct rtl_priv*) ; 

int rtl8822be_hw_init(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	struct rtl_mac *mac = rtl_mac(rtl_priv(hw));
	struct rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	struct rtl_phy *rtlphy = &rtlpriv->phy;
	struct rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	int err = 0;
	u8 tmp_u1b;

	RT_TRACE(rtlpriv, COMP_INIT, DBG_LOUD, " Rtl8822BE hw init\n");
	rtlpriv->rtlhal.being_init_adapter = true;
	rtlpriv->intf_ops->disable_aspm(hw);

	if (_rtl8822be_check_pcie_dma_hang(rtlpriv)) {
		RT_TRACE(rtlpriv, COMP_INIT, DBG_DMESG, "8822be dma hang!\n");
		_rtl8822be_reset_pcie_interface_dma(rtlpriv,
						    rtlhal->mac_func_enable);
		rtlhal->mac_func_enable = false;
	}

	/* init TRX BD */
	_rtl8822be_init_trxbd(hw);

	/* use halmac to init */
	err = rtlpriv->halmac.ops->halmac_init_hal(rtlpriv);
	if (err) {
		pr_err("halmac_init_hal failed\n");
		rtlhal->fw_ready = false;
		return err;
	}

	rtlhal->fw_ready = true;

	/* have to init after halmac init */
	tmp_u1b = rtl_read_byte(rtlpriv, REG_PCIE_CTRL_8822B + 2);
	rtl_write_byte(rtlpriv, REG_PCIE_CTRL_8822B + 2, (tmp_u1b | BIT(4)));

	/*rtl_write_word(rtlpriv, REG_PCIE_CTRL_8822B, 0x8000);*/
	rtlhal->rx_tag = 0;

	rtl_write_byte(rtlpriv, REG_RX_DRVINFO_SZ_8822B, 0x4);

	/*fw related variable initialize */
	ppsc->fw_current_inpsmode = false;
	rtlhal->fw_ps_state = FW_PS_STATE_ALL_ON_8822B;
	rtlhal->fw_clk_change_in_progress = false;
	rtlhal->allow_sw_to_change_hwclc = false;
	rtlhal->last_hmeboxnum = 0;

	rtlphy->rfreg_chnlval[0] =
		rtl_get_rfreg(hw, RF90_PATH_A, RF_CHNLBW, RFREG_OFFSET_MASK);
	rtlphy->rfreg_chnlval[1] =
		rtl_get_rfreg(hw, RF90_PATH_B, RF_CHNLBW, RFREG_OFFSET_MASK);
	rtlphy->backup_rf_0x1a = (u32)rtl_get_rfreg(hw, RF90_PATH_A, RF_RX_G1,
						    RFREG_OFFSET_MASK);
	rtlphy->rfreg_chnlval[0] =
		(rtlphy->rfreg_chnlval[0] & 0xfffff3ff) | BIT(10) | BIT(11);

	rtlhal->mac_func_enable = true;

	if (rtlpriv->cfg->ops->get_btc_status())
		rtlpriv->btcoexist.btc_ops->btc_power_on_setting(rtlpriv);

	/* reset cam / set security */
	rtl_cam_reset_all_entry(hw);
	rtl8822be_enable_hw_security_config(hw);

	/* check RCR/ICV bit */
	rtlpci->receive_config &= ~(RCR_ACRC32 | RCR_AICV);
	rtl_write_dword(rtlpriv, REG_RCR_8822B, rtlpci->receive_config);

	/* clear rx ctrl frame */
	rtl_write_word(rtlpriv, REG_RXFLTMAP1_8822B, 0);

	ppsc->rfpwr_state = ERFON;

	rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_ETHER_ADDR, mac->mac_addr);
	_rtl8822be_enable_aspm_back_door(hw);
	rtlpriv->intf_ops->enable_aspm(hw);

	if (rtlpriv->cfg->ops->get_btc_status())
		rtlpriv->btcoexist.btc_ops->btc_init_hw_config(rtlpriv);
	else
		rtlpriv->btcoexist.btc_ops->btc_init_hw_config_wifi_only(
								rtlpriv);

	rtlpriv->rtlhal.being_init_adapter = false;

	rtlpriv->phydm.ops->phydm_init_dm(rtlpriv);

	/* clear ISR, and IMR will be on later */
	rtl_write_dword(rtlpriv, REG_HISR0_8822B,
			rtl_read_dword(rtlpriv, REG_HISR0_8822B));

	RT_TRACE(rtlpriv, COMP_INIT, DBG_LOUD, "end of Rtl8822BE hw init %x\n",
		 err);
	return 0;
}