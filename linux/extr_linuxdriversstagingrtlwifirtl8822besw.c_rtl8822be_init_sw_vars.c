#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
typedef  void* u32 ;
struct TYPE_22__ {int /*<<< orphan*/  dev; } ;
struct TYPE_21__ {int earlymode_enable; int /*<<< orphan*/  pfirmware; int /*<<< orphan*/  macphymode; int /*<<< orphan*/  bandset; int /*<<< orphan*/  current_bandtype; } ;
struct TYPE_20__ {int reg_fwctrl_lps; int reg_max_lps_awakeintvl; int low_power_enable; int /*<<< orphan*/  fwctrl_psmode; int /*<<< orphan*/  fwctrl_lps; int /*<<< orphan*/  swctrl_lps; int /*<<< orphan*/  inactiveps; } ;
struct TYPE_17__ {int dm_initialgain_enable; int useramask; scalar_t__ disable_framebursting; scalar_t__ dm_flag; } ;
struct TYPE_16__ {TYPE_10__* ops; } ;
struct TYPE_15__ {TYPE_11__* ops; } ;
struct TYPE_14__ {int /*<<< orphan*/  btc_ops; } ;
struct rtl_priv {int max_fw_size; TYPE_9__ io; TYPE_8__ rtlhal; TYPE_7__ psc; TYPE_6__* cfg; TYPE_4__ dm; TYPE_3__ phydm; TYPE_2__ halmac; TYPE_1__ btcoexist; } ;
struct rtl_phydm_params {int dummy; } ;
struct rtl_pci {int transmit_config; int receive_config; int /*<<< orphan*/  msi_support; void** irq_mask; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_19__ {TYPE_5__* mod_params; } ;
struct TYPE_18__ {scalar_t__ disable_watchdog; int /*<<< orphan*/  msi_support; int /*<<< orphan*/  fwctrl_lps; int /*<<< orphan*/  swctrl_lps; int /*<<< orphan*/  inactiveps; } ;
struct TYPE_13__ {int /*<<< orphan*/  (* halmac_init_adapter ) (struct rtl_priv*) ;} ;
struct TYPE_12__ {int /*<<< orphan*/  (* phydm_init_priv ) (struct rtl_priv*,struct rtl_phydm_params*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BAND_ON_2_4G ; 
 int /*<<< orphan*/  BAND_ON_BOTH ; 
 int BIT (int) ; 
 int BIT_SETH2CDOK_MASK ; 
 int CFENDFORM ; 
 int /*<<< orphan*/  FW_PS_DTIM_MODE ; 
 int /*<<< orphan*/  FW_PS_MAX_MODE ; 
 int /*<<< orphan*/  FW_PS_MIN_MODE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IMR_BEDOK ; 
 int IMR_BKDOK ; 
 int IMR_C2HCMD ; 
 int IMR_GTINT3 ; 
 int IMR_HIGHDOK ; 
 int IMR_HSISR_IND_ON_INT ; 
 int IMR_MGNTDOK ; 
 int IMR_PSTIMEOUT ; 
 int IMR_RDU ; 
 int IMR_ROK ; 
 int IMR_RXFOVW ; 
 int IMR_TXFOVW ; 
 int IMR_VIDOK ; 
 int IMR_VODOK ; 
 int RCR_AB ; 
 int RCR_AM ; 
 int RCR_APM ; 
 int RCR_APPFCS ; 
 int RCR_APP_ICV ; 
 int RCR_APP_MIC ; 
 int RCR_APP_PHYST_RXFF ; 
 int RCR_CBSSID_BCN ; 
 int RCR_CBSSID_DATA ; 
 int RCR_HTC_LOC_CTRL ; 
 int RCR_VHT_DACK ; 
 int /*<<< orphan*/  SINGLEMAC_SINGLEPHY ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 
 int request_firmware_nowait (int /*<<< orphan*/ ,int,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ieee80211_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl8822be_bt_reg_init (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl8822be_init_aspm_vars (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl8822be_load_txpower_by_rate (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl8822be_load_txpower_limit (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl8822be_read_eeprom_info (struct ieee80211_hw*,struct rtl_phydm_params*) ; 
 int /*<<< orphan*/  rtl_btc_get_ops_pointer () ; 
 int /*<<< orphan*/  rtl_fw_cb ; 
 TYPE_11__* rtl_halmac_get_ops_pointer () ; 
 struct rtl_pci* rtl_pcidev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_pcipriv (struct ieee80211_hw*) ; 
 TYPE_10__* rtl_phydm_get_ops_pointer () ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  stub1 (struct rtl_priv*) ; 
 int /*<<< orphan*/  stub2 (struct rtl_priv*,struct rtl_phydm_params*) ; 
 int /*<<< orphan*/  vzalloc (int) ; 

int rtl8822be_init_sw_vars(struct ieee80211_hw *hw)
{
	int err = 0;
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	const char *fw_name;
	struct rtl_phydm_params params;

	rtl8822be_bt_reg_init(hw);
	rtlpci->msi_support = rtlpriv->cfg->mod_params->msi_support;
	rtlpriv->btcoexist.btc_ops = rtl_btc_get_ops_pointer();
	rtlpriv->halmac.ops = rtl_halmac_get_ops_pointer();
	rtlpriv->halmac.ops->halmac_init_adapter(rtlpriv);

	/* should after halmac_init_adapter() */
	rtl8822be_read_eeprom_info(hw, &params);

	/* need eeprom info */
	rtlpriv->phydm.ops = rtl_phydm_get_ops_pointer();
	rtlpriv->phydm.ops->phydm_init_priv(rtlpriv, &params);

	rtlpriv->dm.dm_initialgain_enable = 1;
	rtlpriv->dm.dm_flag = 0;
	rtlpriv->dm.disable_framebursting = 0;
	/*rtlpriv->dm.thermalvalue = 0;*/
	rtlpriv->dm.useramask = 1; /* turn on RA */
	rtlpci->transmit_config = CFENDFORM | BIT(15);

	rtlpriv->rtlhal.current_bandtype = BAND_ON_2_4G;
	/*following 2 is for register 5G band, refer to _rtl_init_mac80211()*/
	rtlpriv->rtlhal.bandset = BAND_ON_BOTH;
	rtlpriv->rtlhal.macphymode = SINGLEMAC_SINGLEPHY;

	rtlpci->receive_config = (RCR_APPFCS			|
				  RCR_APP_MIC			|
				  RCR_APP_ICV			|
				  RCR_APP_PHYST_RXFF		|
				  RCR_VHT_DACK			|
				  RCR_HTC_LOC_CTRL		|
				  /*RCR_AMF			|*/
				  RCR_CBSSID_BCN		|
				  RCR_CBSSID_DATA		|
				  /*RCR_ACF			|*/
				  /*RCR_ADF			|*/
				  /*RCR_AICV			|*/
				  /*RCR_ACRC32			|*/
				  RCR_AB			|
				  RCR_AM			|
				  RCR_APM			|
				  0);

	rtlpci->irq_mask[0] = (u32)(IMR_PSTIMEOUT		|
				    /*IMR_TBDER			|*/
				    /*IMR_TBDOK			|*/
				    /*IMR_BCNDMAINT0		|*/
				    IMR_GTINT3			|
				    IMR_HSISR_IND_ON_INT	|
				    IMR_C2HCMD			|
				    IMR_HIGHDOK			|
				    IMR_MGNTDOK			|
				    IMR_BKDOK			|
				    IMR_BEDOK			|
				    IMR_VIDOK			|
				    IMR_VODOK			|
				    IMR_RDU			|
				    IMR_ROK			|
				    0);

	rtlpci->irq_mask[1] = (u32)(IMR_RXFOVW | IMR_TXFOVW | 0);
	rtlpci->irq_mask[3] = (u32)(BIT_SETH2CDOK_MASK | 0);

	/* for LPS & IPS */
	rtlpriv->psc.inactiveps = rtlpriv->cfg->mod_params->inactiveps;
	rtlpriv->psc.swctrl_lps = rtlpriv->cfg->mod_params->swctrl_lps;
	rtlpriv->psc.fwctrl_lps = rtlpriv->cfg->mod_params->fwctrl_lps;
	rtlpci->msi_support = rtlpriv->cfg->mod_params->msi_support;
	if (rtlpriv->cfg->mod_params->disable_watchdog)
		pr_info("watchdog disabled\n");
	rtlpriv->psc.reg_fwctrl_lps = 2;
	rtlpriv->psc.reg_max_lps_awakeintvl = 2;
	/* for ASPM, you can close aspm through
	 * set const_support_pciaspm = 0
	 */
	rtl8822be_init_aspm_vars(hw);

	if (rtlpriv->psc.reg_fwctrl_lps == 1)
		rtlpriv->psc.fwctrl_psmode = FW_PS_MIN_MODE;
	else if (rtlpriv->psc.reg_fwctrl_lps == 2)
		rtlpriv->psc.fwctrl_psmode = FW_PS_MAX_MODE;
	else if (rtlpriv->psc.reg_fwctrl_lps == 3)
		rtlpriv->psc.fwctrl_psmode = FW_PS_DTIM_MODE;

	/* for early mode */
	rtlpriv->rtlhal.earlymode_enable = false;

	/*low power */
	rtlpriv->psc.low_power_enable = false;

	/* for firmware buf */
	rtlpriv->rtlhal.pfirmware = vzalloc(0x40000);
	if (!rtlpriv->rtlhal.pfirmware) {
		/*pr_err("Can't alloc buffer for fw\n");*/
		return 1;
	}

	/* request fw */
	fw_name = "rtlwifi/rtl8822befw.bin";

	rtlpriv->max_fw_size = 0x40000;
	pr_info("Using firmware %s\n", fw_name);
	err = request_firmware_nowait(THIS_MODULE, 1, fw_name, rtlpriv->io.dev,
				      GFP_KERNEL, hw, rtl_fw_cb);
	if (err) {
		pr_err("Failed to request firmware!\n");
		return 1;
	}

	/* init table of tx power by rate & limit */
	rtl8822be_load_txpower_by_rate(hw);
	rtl8822be_load_txpower_limit(hw);

	return 0;
}