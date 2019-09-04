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
typedef  int /*<<< orphan*/  u16 ;
struct rt2x00_dev {struct rt2800_drv_data* drv_data; } ;
struct rt2800_drv_data {int max_psdu; } ;

/* Variables and functions */
 int AGGREGATION_SIZE ; 
 int /*<<< orphan*/  AMPDU_BA_WINSIZE ; 
 int /*<<< orphan*/  AMPDU_BA_WINSIZE_FORCE_WINSIZE ; 
 int /*<<< orphan*/  AMPDU_BA_WINSIZE_FORCE_WINSIZE_ENABLE ; 
 int /*<<< orphan*/  AUTO_RSP_CFG ; 
 int /*<<< orphan*/  AUTO_RSP_CFG_ACK_CTS_PSM_BIT ; 
 int /*<<< orphan*/  AUTO_RSP_CFG_AR_PREAMBLE ; 
 int /*<<< orphan*/  AUTO_RSP_CFG_AUTORESPONDER ; 
 int /*<<< orphan*/  AUTO_RSP_CFG_BAC_ACK_POLICY ; 
 int /*<<< orphan*/  AUTO_RSP_CFG_CTS_40_MMODE ; 
 int /*<<< orphan*/  AUTO_RSP_CFG_CTS_40_MREF ; 
 int /*<<< orphan*/  AUTO_RSP_CFG_DUAL_CTS_EN ; 
 int /*<<< orphan*/  BCN_TIME_CFG ; 
 int /*<<< orphan*/  BCN_TIME_CFG_BEACON_GEN ; 
 int /*<<< orphan*/  BCN_TIME_CFG_BEACON_INTERVAL ; 
 int /*<<< orphan*/  BCN_TIME_CFG_TBTT_ENABLE ; 
 int /*<<< orphan*/  BCN_TIME_CFG_TSF_SYNC ; 
 int /*<<< orphan*/  BCN_TIME_CFG_TSF_TICKING ; 
 int /*<<< orphan*/  BCN_TIME_CFG_TX_TIME_COMPENSATE ; 
 int /*<<< orphan*/  BKOFF_SLOT_CFG ; 
 int /*<<< orphan*/  BKOFF_SLOT_CFG_CC_DELAY_TIME ; 
 int /*<<< orphan*/  BKOFF_SLOT_CFG_SLOT_TIME ; 
 int /*<<< orphan*/  BT_COEX_CFG0 ; 
 int /*<<< orphan*/  BT_COEX_CFG1 ; 
 int /*<<< orphan*/  CCK_PROT_CFG ; 
 int /*<<< orphan*/  CCK_PROT_CFG_PROTECT_CTRL ; 
 int /*<<< orphan*/  CCK_PROT_CFG_PROTECT_NAV_SHORT ; 
 int /*<<< orphan*/  CCK_PROT_CFG_PROTECT_RATE ; 
 int /*<<< orphan*/  CCK_PROT_CFG_RTS_TH_EN ; 
 int /*<<< orphan*/  CCK_PROT_CFG_TX_OP_ALLOW_CCK ; 
 int /*<<< orphan*/  CCK_PROT_CFG_TX_OP_ALLOW_GF20 ; 
 int /*<<< orphan*/  CCK_PROT_CFG_TX_OP_ALLOW_GF40 ; 
 int /*<<< orphan*/  CCK_PROT_CFG_TX_OP_ALLOW_MM20 ; 
 int /*<<< orphan*/  CCK_PROT_CFG_TX_OP_ALLOW_MM40 ; 
 int /*<<< orphan*/  CCK_PROT_CFG_TX_OP_ALLOW_OFDM ; 
 int /*<<< orphan*/  CH_TIME_CFG ; 
 int /*<<< orphan*/  CH_TIME_CFG_EIFS_BUSY ; 
 int /*<<< orphan*/  CH_TIME_CFG_NAV_BUSY ; 
 int /*<<< orphan*/  CH_TIME_CFG_RX_BUSY ; 
 int /*<<< orphan*/  CH_TIME_CFG_TMR_EN ; 
 int /*<<< orphan*/  CH_TIME_CFG_TX_BUSY ; 
 int /*<<< orphan*/  CMB_CTRL ; 
 int /*<<< orphan*/  COEX_CFG0 ; 
 int /*<<< orphan*/  COEX_CFG2 ; 
 int /*<<< orphan*/  COEX_CFG_ANT ; 
 int /*<<< orphan*/  EEPROM_NIC_CONF1 ; 
 int /*<<< orphan*/  EEPROM_NIC_CONF1_DAC_TEST ; 
 int /*<<< orphan*/  EXP_ACK_TIME ; 
 int /*<<< orphan*/  FIF_ALLMULTI ; 
 int /*<<< orphan*/  GF20_PROT_CFG ; 
 int /*<<< orphan*/  GF20_PROT_CFG_PROTECT_CTRL ; 
 int /*<<< orphan*/  GF20_PROT_CFG_PROTECT_NAV_SHORT ; 
 int /*<<< orphan*/  GF20_PROT_CFG_PROTECT_RATE ; 
 int /*<<< orphan*/  GF20_PROT_CFG_RTS_TH_EN ; 
 int /*<<< orphan*/  GF20_PROT_CFG_TX_OP_ALLOW_CCK ; 
 int /*<<< orphan*/  GF20_PROT_CFG_TX_OP_ALLOW_GF20 ; 
 int /*<<< orphan*/  GF20_PROT_CFG_TX_OP_ALLOW_GF40 ; 
 int /*<<< orphan*/  GF20_PROT_CFG_TX_OP_ALLOW_MM20 ; 
 int /*<<< orphan*/  GF20_PROT_CFG_TX_OP_ALLOW_MM40 ; 
 int /*<<< orphan*/  GF20_PROT_CFG_TX_OP_ALLOW_OFDM ; 
 int /*<<< orphan*/  GF40_PROT_CFG ; 
 int /*<<< orphan*/  GF40_PROT_CFG_PROTECT_CTRL ; 
 int /*<<< orphan*/  GF40_PROT_CFG_PROTECT_NAV_SHORT ; 
 int /*<<< orphan*/  GF40_PROT_CFG_PROTECT_RATE ; 
 int /*<<< orphan*/  GF40_PROT_CFG_RTS_TH_EN ; 
 int /*<<< orphan*/  GF40_PROT_CFG_TX_OP_ALLOW_CCK ; 
 int /*<<< orphan*/  GF40_PROT_CFG_TX_OP_ALLOW_GF20 ; 
 int /*<<< orphan*/  GF40_PROT_CFG_TX_OP_ALLOW_GF40 ; 
 int /*<<< orphan*/  GF40_PROT_CFG_TX_OP_ALLOW_MM20 ; 
 int /*<<< orphan*/  GF40_PROT_CFG_TX_OP_ALLOW_MM40 ; 
 int /*<<< orphan*/  GF40_PROT_CFG_TX_OP_ALLOW_OFDM ; 
 int /*<<< orphan*/  HT_BASIC_RATE ; 
 int /*<<< orphan*/  HT_FBK_CFG0 ; 
 int /*<<< orphan*/  HT_FBK_CFG0_HTMCS0FBK ; 
 int /*<<< orphan*/  HT_FBK_CFG0_HTMCS1FBK ; 
 int /*<<< orphan*/  HT_FBK_CFG0_HTMCS2FBK ; 
 int /*<<< orphan*/  HT_FBK_CFG0_HTMCS3FBK ; 
 int /*<<< orphan*/  HT_FBK_CFG0_HTMCS4FBK ; 
 int /*<<< orphan*/  HT_FBK_CFG0_HTMCS5FBK ; 
 int /*<<< orphan*/  HT_FBK_CFG0_HTMCS6FBK ; 
 int /*<<< orphan*/  HT_FBK_CFG0_HTMCS7FBK ; 
 int /*<<< orphan*/  HT_FBK_CFG1 ; 
 int /*<<< orphan*/  HT_FBK_CFG1_HTMCS10FBK ; 
 int /*<<< orphan*/  HT_FBK_CFG1_HTMCS11FBK ; 
 int /*<<< orphan*/  HT_FBK_CFG1_HTMCS12FBK ; 
 int /*<<< orphan*/  HT_FBK_CFG1_HTMCS13FBK ; 
 int /*<<< orphan*/  HT_FBK_CFG1_HTMCS14FBK ; 
 int /*<<< orphan*/  HT_FBK_CFG1_HTMCS15FBK ; 
 int /*<<< orphan*/  HT_FBK_CFG1_HTMCS8FBK ; 
 int /*<<< orphan*/  HT_FBK_CFG1_HTMCS9FBK ; 
 int IEEE80211_MAX_RTS_THRESHOLD ; 
 int /*<<< orphan*/  INT_TIMER_CFG ; 
 int /*<<< orphan*/  INT_TIMER_CFG_PRE_TBTT_TIMER ; 
 int /*<<< orphan*/  LDO0_EN ; 
 int /*<<< orphan*/  LDO_BGSEL ; 
 int /*<<< orphan*/  LED_CFG ; 
 int /*<<< orphan*/  LED_CFG_G_LED_MODE ; 
 int /*<<< orphan*/  LED_CFG_LED_POLAR ; 
 int /*<<< orphan*/  LED_CFG_OFF_PERIOD ; 
 int /*<<< orphan*/  LED_CFG_ON_PERIOD ; 
 int /*<<< orphan*/  LED_CFG_R_LED_MODE ; 
 int /*<<< orphan*/  LED_CFG_SLOW_BLINK_PERIOD ; 
 int /*<<< orphan*/  LED_CFG_Y_LED_MODE ; 
 int /*<<< orphan*/  LEGACY_BASIC_RATE ; 
 int /*<<< orphan*/  LG_FBK_CFG0 ; 
 int /*<<< orphan*/  LG_FBK_CFG0_CCKMCS0FBK ; 
 int /*<<< orphan*/  LG_FBK_CFG0_CCKMCS1FBK ; 
 int /*<<< orphan*/  LG_FBK_CFG0_CCKMCS2FBK ; 
 int /*<<< orphan*/  LG_FBK_CFG0_CCKMCS3FBK ; 
 int /*<<< orphan*/  LG_FBK_CFG0_OFDMMCS0FBK ; 
 int /*<<< orphan*/  LG_FBK_CFG0_OFDMMCS1FBK ; 
 int /*<<< orphan*/  LG_FBK_CFG0_OFDMMCS2FBK ; 
 int /*<<< orphan*/  LG_FBK_CFG0_OFDMMCS3FBK ; 
 int /*<<< orphan*/  LG_FBK_CFG0_OFDMMCS4FBK ; 
 int /*<<< orphan*/  LG_FBK_CFG0_OFDMMCS5FBK ; 
 int /*<<< orphan*/  LG_FBK_CFG0_OFDMMCS6FBK ; 
 int /*<<< orphan*/  LG_FBK_CFG0_OFDMMCS7FBK ; 
 int /*<<< orphan*/  LG_FBK_CFG1 ; 
 int /*<<< orphan*/  MAC_IVEIV_ENTRY (unsigned int) ; 
 int /*<<< orphan*/  MAC_SYS_CTRL ; 
 int /*<<< orphan*/  MAX_LEN_CFG ; 
 int /*<<< orphan*/  MAX_LEN_CFG_MAX_MPDU ; 
 int /*<<< orphan*/  MAX_LEN_CFG_MAX_PSDU ; 
 int /*<<< orphan*/  MAX_LEN_CFG_MIN_MPDU ; 
 int /*<<< orphan*/  MAX_LEN_CFG_MIN_PSDU ; 
 int /*<<< orphan*/  MIMO_PS_CFG ; 
 int /*<<< orphan*/  MM20_PROT_CFG ; 
 int /*<<< orphan*/  MM20_PROT_CFG_PROTECT_CTRL ; 
 int /*<<< orphan*/  MM20_PROT_CFG_PROTECT_NAV_SHORT ; 
 int /*<<< orphan*/  MM20_PROT_CFG_PROTECT_RATE ; 
 int /*<<< orphan*/  MM20_PROT_CFG_RTS_TH_EN ; 
 int /*<<< orphan*/  MM20_PROT_CFG_TX_OP_ALLOW_CCK ; 
 int /*<<< orphan*/  MM20_PROT_CFG_TX_OP_ALLOW_GF20 ; 
 int /*<<< orphan*/  MM20_PROT_CFG_TX_OP_ALLOW_GF40 ; 
 int /*<<< orphan*/  MM20_PROT_CFG_TX_OP_ALLOW_MM20 ; 
 int /*<<< orphan*/  MM20_PROT_CFG_TX_OP_ALLOW_MM40 ; 
 int /*<<< orphan*/  MM20_PROT_CFG_TX_OP_ALLOW_OFDM ; 
 int /*<<< orphan*/  MM40_PROT_CFG ; 
 int /*<<< orphan*/  MM40_PROT_CFG_PROTECT_CTRL ; 
 int /*<<< orphan*/  MM40_PROT_CFG_PROTECT_NAV_SHORT ; 
 int /*<<< orphan*/  MM40_PROT_CFG_PROTECT_RATE ; 
 int /*<<< orphan*/  MM40_PROT_CFG_RTS_TH_EN ; 
 int /*<<< orphan*/  MM40_PROT_CFG_TX_OP_ALLOW_CCK ; 
 int /*<<< orphan*/  MM40_PROT_CFG_TX_OP_ALLOW_GF20 ; 
 int /*<<< orphan*/  MM40_PROT_CFG_TX_OP_ALLOW_GF40 ; 
 int /*<<< orphan*/  MM40_PROT_CFG_TX_OP_ALLOW_MM20 ; 
 int /*<<< orphan*/  MM40_PROT_CFG_TX_OP_ALLOW_MM40 ; 
 int /*<<< orphan*/  MM40_PROT_CFG_TX_OP_ALLOW_OFDM ; 
 int /*<<< orphan*/  OFDM_PROT_CFG ; 
 int /*<<< orphan*/  OFDM_PROT_CFG_PROTECT_CTRL ; 
 int /*<<< orphan*/  OFDM_PROT_CFG_PROTECT_NAV_SHORT ; 
 int /*<<< orphan*/  OFDM_PROT_CFG_PROTECT_RATE ; 
 int /*<<< orphan*/  OFDM_PROT_CFG_RTS_TH_EN ; 
 int /*<<< orphan*/  OFDM_PROT_CFG_TX_OP_ALLOW_CCK ; 
 int /*<<< orphan*/  OFDM_PROT_CFG_TX_OP_ALLOW_GF20 ; 
 int /*<<< orphan*/  OFDM_PROT_CFG_TX_OP_ALLOW_GF40 ; 
 int /*<<< orphan*/  OFDM_PROT_CFG_TX_OP_ALLOW_MM20 ; 
 int /*<<< orphan*/  OFDM_PROT_CFG_TX_OP_ALLOW_MM40 ; 
 int /*<<< orphan*/  OFDM_PROT_CFG_TX_OP_ALLOW_OFDM ; 
 int /*<<< orphan*/  OSC_CAL_REQ ; 
 int /*<<< orphan*/  OSC_CTRL ; 
 int /*<<< orphan*/  OSC_REF_CYCLE ; 
 int /*<<< orphan*/  OSC_ROSC_EN ; 
 int /*<<< orphan*/  PBF_CFG ; 
 int /*<<< orphan*/  PBF_MAX_PCNT ; 
 int /*<<< orphan*/  PCIE_APP0_CLK_REQ ; 
 int /*<<< orphan*/  PLL_CONTROL ; 
 int /*<<< orphan*/  PLL_CTRL ; 
 int /*<<< orphan*/  PWR_PIN_CFG ; 
 int /*<<< orphan*/  REV_RT2872E ; 
 int /*<<< orphan*/  REV_RT3070E ; 
 int /*<<< orphan*/  REV_RT3070F ; 
 int /*<<< orphan*/  REV_RT3071E ; 
 int /*<<< orphan*/  REV_RT3090E ; 
 int /*<<< orphan*/  REV_RT3390E ; 
 int /*<<< orphan*/  REV_RT3593E ; 
 int /*<<< orphan*/  RT2872 ; 
 int /*<<< orphan*/  RT2883 ; 
 int /*<<< orphan*/  RT3070 ; 
 int /*<<< orphan*/  RT3071 ; 
 int /*<<< orphan*/  RT3090 ; 
 int /*<<< orphan*/  RT3290 ; 
 int /*<<< orphan*/  RT3352 ; 
 int /*<<< orphan*/  RT3390 ; 
 int /*<<< orphan*/  RT3572 ; 
 int /*<<< orphan*/  RT3593 ; 
 int /*<<< orphan*/  RT5350 ; 
 int /*<<< orphan*/  RT5390 ; 
 int /*<<< orphan*/  RT5392 ; 
 int /*<<< orphan*/  RT5592 ; 
 int /*<<< orphan*/  RT6352 ; 
 int /*<<< orphan*/  RX_STA_CNT0 ; 
 int /*<<< orphan*/  RX_STA_CNT1 ; 
 int /*<<< orphan*/  RX_STA_CNT2 ; 
 int /*<<< orphan*/  SHARED_KEY_MODE_ENTRY (unsigned int) ; 
 int /*<<< orphan*/  TX0_BB_GAIN_ATTEN ; 
 int /*<<< orphan*/  TX0_RF_GAIN_ATTEN ; 
 int /*<<< orphan*/  TX0_RF_GAIN_CORRECT ; 
 int /*<<< orphan*/  TX1_BB_GAIN_ATTEN ; 
 int /*<<< orphan*/  TX1_RF_GAIN_ATTEN ; 
 int /*<<< orphan*/  TX1_RF_GAIN_CORRECT ; 
 int /*<<< orphan*/  TXOP_CTRL_CFG ; 
 int /*<<< orphan*/  TXOP_CTRL_CFG_AC_TRUN_EN ; 
 int /*<<< orphan*/  TXOP_CTRL_CFG_EXT_CCA_DLY ; 
 int /*<<< orphan*/  TXOP_CTRL_CFG_EXT_CCA_EN ; 
 int /*<<< orphan*/  TXOP_CTRL_CFG_EXT_CWMIN ; 
 int /*<<< orphan*/  TXOP_CTRL_CFG_LSIG_TXOP_EN ; 
 int /*<<< orphan*/  TXOP_CTRL_CFG_MIMO_PS_TRUN_EN ; 
 int /*<<< orphan*/  TXOP_CTRL_CFG_RESERVED_TRUN_EN ; 
 int /*<<< orphan*/  TXOP_CTRL_CFG_TIMEOUT_TRUN_EN ; 
 int /*<<< orphan*/  TXOP_CTRL_CFG_TXRATEGRP_TRUN_EN ; 
 int /*<<< orphan*/  TXOP_CTRL_CFG_USER_MODE_TRUN_EN ; 
 int /*<<< orphan*/  TXOP_HLDR_ET ; 
 int /*<<< orphan*/  TX_ALC_CFG_1 ; 
 int /*<<< orphan*/  TX_ALC_CFG_1_ROS_BUSY_EN ; 
 int /*<<< orphan*/  TX_ALC_VGA3 ; 
 int /*<<< orphan*/  TX_LINK_CFG ; 
 int /*<<< orphan*/  TX_LINK_CFG_MFB_ENABLE ; 
 int /*<<< orphan*/  TX_LINK_CFG_REMOTE_MFB ; 
 int /*<<< orphan*/  TX_LINK_CFG_REMOTE_MFB_LIFETIME ; 
 int /*<<< orphan*/  TX_LINK_CFG_REMOTE_MFS ; 
 int /*<<< orphan*/  TX_LINK_CFG_REMOTE_UMFS_ENABLE ; 
 int /*<<< orphan*/  TX_LINK_CFG_TX_CF_ACK_EN ; 
 int /*<<< orphan*/  TX_LINK_CFG_TX_MRQ_EN ; 
 int /*<<< orphan*/  TX_LINK_CFG_TX_RDG_EN ; 
 int /*<<< orphan*/  TX_PIN_CFG ; 
 int /*<<< orphan*/  TX_RTS_CFG ; 
 int /*<<< orphan*/  TX_RTS_CFG_AUTO_RTS_RETRY_LIMIT ; 
 int /*<<< orphan*/  TX_RTS_CFG_RTS_FBK_EN ; 
 int /*<<< orphan*/  TX_RTS_CFG_RTS_THRES ; 
 int /*<<< orphan*/  TX_RTY_CFG ; 
 int /*<<< orphan*/  TX_RTY_CFG_AGG_RTY_MODE ; 
 int /*<<< orphan*/  TX_RTY_CFG_LONG_RTY_LIMIT ; 
 int /*<<< orphan*/  TX_RTY_CFG_LONG_RTY_THRE ; 
 int /*<<< orphan*/  TX_RTY_CFG_NON_AGG_RTY_MODE ; 
 int /*<<< orphan*/  TX_RTY_CFG_SHORT_RTY_LIMIT ; 
 int /*<<< orphan*/  TX_RTY_CFG_TX_AUTO_FB_ENABLE ; 
 int /*<<< orphan*/  TX_STA_CNT0 ; 
 int /*<<< orphan*/  TX_STA_CNT1 ; 
 int /*<<< orphan*/  TX_STA_CNT2 ; 
 int /*<<< orphan*/  TX_SW_CFG0 ; 
 int /*<<< orphan*/  TX_SW_CFG1 ; 
 int /*<<< orphan*/  TX_SW_CFG2 ; 
 int /*<<< orphan*/  TX_TIMEOUT_CFG ; 
 int /*<<< orphan*/  TX_TIMEOUT_CFG_MPDU_LIFETIME ; 
 int /*<<< orphan*/  TX_TIMEOUT_CFG_RX_ACK_TIMEOUT ; 
 int /*<<< orphan*/  TX_TIMEOUT_CFG_TX_OP_TIMEOUT ; 
 int /*<<< orphan*/  US_CYC_CNT ; 
 int /*<<< orphan*/  US_CYC_CNT_CLOCK_CYCLE ; 
 int /*<<< orphan*/  WLAN_EN ; 
 int /*<<< orphan*/  WLAN_FUN_CTRL ; 
 int /*<<< orphan*/  WL_COEX_CFG0 ; 
 int /*<<< orphan*/  WL_COEX_CFG1 ; 
 int /*<<< orphan*/  WPDMA_GLO_CFG ; 
 int /*<<< orphan*/  WPDMA_GLO_CFG_BIG_ENDIAN ; 
 int /*<<< orphan*/  WPDMA_GLO_CFG_ENABLE_RX_DMA ; 
 int /*<<< orphan*/  WPDMA_GLO_CFG_ENABLE_TX_DMA ; 
 int /*<<< orphan*/  WPDMA_GLO_CFG_HDR_SEG_LEN ; 
 int /*<<< orphan*/  WPDMA_GLO_CFG_RX_DMA_BUSY ; 
 int /*<<< orphan*/  WPDMA_GLO_CFG_RX_HDR_SCATTER ; 
 int /*<<< orphan*/  WPDMA_GLO_CFG_TX_DMA_BUSY ; 
 int /*<<< orphan*/  WPDMA_GLO_CFG_TX_WRITEBACK_DONE ; 
 int /*<<< orphan*/  WPDMA_GLO_CFG_WP_DMA_BURST_SIZE ; 
 int /*<<< orphan*/  XIFS_TIME_CFG ; 
 int /*<<< orphan*/  XIFS_TIME_CFG_BB_RXEND_ENABLE ; 
 int /*<<< orphan*/  XIFS_TIME_CFG_CCKM_SIFS_TIME ; 
 int /*<<< orphan*/  XIFS_TIME_CFG_EIFS ; 
 int /*<<< orphan*/  XIFS_TIME_CFG_OFDM_SIFS_TIME ; 
 int /*<<< orphan*/  XIFS_TIME_CFG_OFDM_XIFS_TIME ; 
 int /*<<< orphan*/  rt2800_clear_beacon_register (struct rt2x00_dev*,unsigned int) ; 
 int /*<<< orphan*/  rt2800_config_filter (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2800_config_wcid (struct rt2x00_dev*,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  rt2800_delete_wcid_attr (struct rt2x00_dev*,unsigned int) ; 
 int /*<<< orphan*/  rt2800_disable_wpdma (struct rt2x00_dev*) ; 
 int rt2800_drv_init_registers (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2800_eeprom_read (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ rt2800_is_305x_soc (struct rt2x00_dev*) ; 
 int rt2800_register_read (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2800_register_write (struct rt2x00_dev*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ rt2x00_get_field16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rt2x00_get_field32 (int,int /*<<< orphan*/ ) ; 
 scalar_t__ rt2x00_is_pcie (struct rt2x00_dev*) ; 
 scalar_t__ rt2x00_is_usb (struct rt2x00_dev*) ; 
 scalar_t__ rt2x00_rt (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ rt2x00_rt_rev_gte (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rt2x00_rt_rev_lt (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00_set_field32 (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int rt2800_init_registers(struct rt2x00_dev *rt2x00dev)
{
	struct rt2800_drv_data *drv_data = rt2x00dev->drv_data;
	u32 reg;
	u16 eeprom;
	unsigned int i;
	int ret;

	rt2800_disable_wpdma(rt2x00dev);

	ret = rt2800_drv_init_registers(rt2x00dev);
	if (ret)
		return ret;

	rt2800_register_write(rt2x00dev, LEGACY_BASIC_RATE, 0x0000013f);
	rt2800_register_write(rt2x00dev, HT_BASIC_RATE, 0x00008003);

	rt2800_register_write(rt2x00dev, MAC_SYS_CTRL, 0x00000000);

	reg = rt2800_register_read(rt2x00dev, BCN_TIME_CFG);
	rt2x00_set_field32(&reg, BCN_TIME_CFG_BEACON_INTERVAL, 1600);
	rt2x00_set_field32(&reg, BCN_TIME_CFG_TSF_TICKING, 0);
	rt2x00_set_field32(&reg, BCN_TIME_CFG_TSF_SYNC, 0);
	rt2x00_set_field32(&reg, BCN_TIME_CFG_TBTT_ENABLE, 0);
	rt2x00_set_field32(&reg, BCN_TIME_CFG_BEACON_GEN, 0);
	rt2x00_set_field32(&reg, BCN_TIME_CFG_TX_TIME_COMPENSATE, 0);
	rt2800_register_write(rt2x00dev, BCN_TIME_CFG, reg);

	rt2800_config_filter(rt2x00dev, FIF_ALLMULTI);

	reg = rt2800_register_read(rt2x00dev, BKOFF_SLOT_CFG);
	rt2x00_set_field32(&reg, BKOFF_SLOT_CFG_SLOT_TIME, 9);
	rt2x00_set_field32(&reg, BKOFF_SLOT_CFG_CC_DELAY_TIME, 2);
	rt2800_register_write(rt2x00dev, BKOFF_SLOT_CFG, reg);

	if (rt2x00_rt(rt2x00dev, RT3290)) {
		reg = rt2800_register_read(rt2x00dev, WLAN_FUN_CTRL);
		if (rt2x00_get_field32(reg, WLAN_EN) == 1) {
			rt2x00_set_field32(&reg, PCIE_APP0_CLK_REQ, 1);
			rt2800_register_write(rt2x00dev, WLAN_FUN_CTRL, reg);
		}

		reg = rt2800_register_read(rt2x00dev, CMB_CTRL);
		if (!(rt2x00_get_field32(reg, LDO0_EN) == 1)) {
			rt2x00_set_field32(&reg, LDO0_EN, 1);
			rt2x00_set_field32(&reg, LDO_BGSEL, 3);
			rt2800_register_write(rt2x00dev, CMB_CTRL, reg);
		}

		reg = rt2800_register_read(rt2x00dev, OSC_CTRL);
		rt2x00_set_field32(&reg, OSC_ROSC_EN, 1);
		rt2x00_set_field32(&reg, OSC_CAL_REQ, 1);
		rt2x00_set_field32(&reg, OSC_REF_CYCLE, 0x27);
		rt2800_register_write(rt2x00dev, OSC_CTRL, reg);

		reg = rt2800_register_read(rt2x00dev, COEX_CFG0);
		rt2x00_set_field32(&reg, COEX_CFG_ANT, 0x5e);
		rt2800_register_write(rt2x00dev, COEX_CFG0, reg);

		reg = rt2800_register_read(rt2x00dev, COEX_CFG2);
		rt2x00_set_field32(&reg, BT_COEX_CFG1, 0x00);
		rt2x00_set_field32(&reg, BT_COEX_CFG0, 0x17);
		rt2x00_set_field32(&reg, WL_COEX_CFG1, 0x93);
		rt2x00_set_field32(&reg, WL_COEX_CFG0, 0x7f);
		rt2800_register_write(rt2x00dev, COEX_CFG2, reg);

		reg = rt2800_register_read(rt2x00dev, PLL_CTRL);
		rt2x00_set_field32(&reg, PLL_CONTROL, 1);
		rt2800_register_write(rt2x00dev, PLL_CTRL, reg);
	}

	if (rt2x00_rt(rt2x00dev, RT3071) ||
	    rt2x00_rt(rt2x00dev, RT3090) ||
	    rt2x00_rt(rt2x00dev, RT3290) ||
	    rt2x00_rt(rt2x00dev, RT3390)) {

		if (rt2x00_rt(rt2x00dev, RT3290))
			rt2800_register_write(rt2x00dev, TX_SW_CFG0,
					      0x00000404);
		else
			rt2800_register_write(rt2x00dev, TX_SW_CFG0,
					      0x00000400);

		rt2800_register_write(rt2x00dev, TX_SW_CFG1, 0x00000000);
		if (rt2x00_rt_rev_lt(rt2x00dev, RT3071, REV_RT3071E) ||
		    rt2x00_rt_rev_lt(rt2x00dev, RT3090, REV_RT3090E) ||
		    rt2x00_rt_rev_lt(rt2x00dev, RT3390, REV_RT3390E)) {
			eeprom = rt2800_eeprom_read(rt2x00dev, EEPROM_NIC_CONF1);
			if (rt2x00_get_field16(eeprom, EEPROM_NIC_CONF1_DAC_TEST))
				rt2800_register_write(rt2x00dev, TX_SW_CFG2,
						      0x0000002c);
			else
				rt2800_register_write(rt2x00dev, TX_SW_CFG2,
						      0x0000000f);
		} else {
			rt2800_register_write(rt2x00dev, TX_SW_CFG2, 0x00000000);
		}
	} else if (rt2x00_rt(rt2x00dev, RT3070)) {
		rt2800_register_write(rt2x00dev, TX_SW_CFG0, 0x00000400);

		if (rt2x00_rt_rev_lt(rt2x00dev, RT3070, REV_RT3070F)) {
			rt2800_register_write(rt2x00dev, TX_SW_CFG1, 0x00000000);
			rt2800_register_write(rt2x00dev, TX_SW_CFG2, 0x0000002c);
		} else {
			rt2800_register_write(rt2x00dev, TX_SW_CFG1, 0x00080606);
			rt2800_register_write(rt2x00dev, TX_SW_CFG2, 0x00000000);
		}
	} else if (rt2800_is_305x_soc(rt2x00dev)) {
		rt2800_register_write(rt2x00dev, TX_SW_CFG0, 0x00000400);
		rt2800_register_write(rt2x00dev, TX_SW_CFG1, 0x00000000);
		rt2800_register_write(rt2x00dev, TX_SW_CFG2, 0x00000030);
	} else if (rt2x00_rt(rt2x00dev, RT3352)) {
		rt2800_register_write(rt2x00dev, TX_SW_CFG0, 0x00000402);
		rt2800_register_write(rt2x00dev, TX_SW_CFG1, 0x00080606);
		rt2800_register_write(rt2x00dev, TX_SW_CFG2, 0x00000000);
	} else if (rt2x00_rt(rt2x00dev, RT3572)) {
		rt2800_register_write(rt2x00dev, TX_SW_CFG0, 0x00000400);
		rt2800_register_write(rt2x00dev, TX_SW_CFG1, 0x00080606);
	} else if (rt2x00_rt(rt2x00dev, RT3593)) {
		rt2800_register_write(rt2x00dev, TX_SW_CFG0, 0x00000402);
		rt2800_register_write(rt2x00dev, TX_SW_CFG1, 0x00000000);
		if (rt2x00_rt_rev_lt(rt2x00dev, RT3593, REV_RT3593E)) {
			eeprom = rt2800_eeprom_read(rt2x00dev, EEPROM_NIC_CONF1);
			if (rt2x00_get_field16(eeprom,
					       EEPROM_NIC_CONF1_DAC_TEST))
				rt2800_register_write(rt2x00dev, TX_SW_CFG2,
						      0x0000001f);
			else
				rt2800_register_write(rt2x00dev, TX_SW_CFG2,
						      0x0000000f);
		} else {
			rt2800_register_write(rt2x00dev, TX_SW_CFG2,
					      0x00000000);
		}
	} else if (rt2x00_rt(rt2x00dev, RT5390) ||
		   rt2x00_rt(rt2x00dev, RT5392) ||
		   rt2x00_rt(rt2x00dev, RT6352)) {
		rt2800_register_write(rt2x00dev, TX_SW_CFG0, 0x00000404);
		rt2800_register_write(rt2x00dev, TX_SW_CFG1, 0x00080606);
		rt2800_register_write(rt2x00dev, TX_SW_CFG2, 0x00000000);
	} else if (rt2x00_rt(rt2x00dev, RT5592)) {
		rt2800_register_write(rt2x00dev, TX_SW_CFG0, 0x00000404);
		rt2800_register_write(rt2x00dev, TX_SW_CFG1, 0x00000000);
		rt2800_register_write(rt2x00dev, TX_SW_CFG2, 0x00000000);
	} else if (rt2x00_rt(rt2x00dev, RT5350)) {
		rt2800_register_write(rt2x00dev, TX_SW_CFG0, 0x00000404);
	} else if (rt2x00_rt(rt2x00dev, RT6352)) {
		rt2800_register_write(rt2x00dev, TX_SW_CFG0, 0x00000401);
		rt2800_register_write(rt2x00dev, TX_SW_CFG1, 0x000C0000);
		rt2800_register_write(rt2x00dev, TX_SW_CFG2, 0x00000000);
		rt2800_register_write(rt2x00dev, MIMO_PS_CFG, 0x00000002);
		rt2800_register_write(rt2x00dev, TX_PIN_CFG, 0x00150F0F);
		rt2800_register_write(rt2x00dev, TX_ALC_VGA3, 0x06060606);
		rt2800_register_write(rt2x00dev, TX0_BB_GAIN_ATTEN, 0x0);
		rt2800_register_write(rt2x00dev, TX1_BB_GAIN_ATTEN, 0x0);
		rt2800_register_write(rt2x00dev, TX0_RF_GAIN_ATTEN, 0x6C6C666C);
		rt2800_register_write(rt2x00dev, TX1_RF_GAIN_ATTEN, 0x6C6C666C);
		rt2800_register_write(rt2x00dev, TX0_RF_GAIN_CORRECT,
				      0x3630363A);
		rt2800_register_write(rt2x00dev, TX1_RF_GAIN_CORRECT,
				      0x3630363A);
		reg = rt2800_register_read(rt2x00dev, TX_ALC_CFG_1);
		rt2x00_set_field32(&reg, TX_ALC_CFG_1_ROS_BUSY_EN, 0);
		rt2800_register_write(rt2x00dev, TX_ALC_CFG_1, reg);
	} else {
		rt2800_register_write(rt2x00dev, TX_SW_CFG0, 0x00000000);
		rt2800_register_write(rt2x00dev, TX_SW_CFG1, 0x00080606);
	}

	reg = rt2800_register_read(rt2x00dev, TX_LINK_CFG);
	rt2x00_set_field32(&reg, TX_LINK_CFG_REMOTE_MFB_LIFETIME, 32);
	rt2x00_set_field32(&reg, TX_LINK_CFG_MFB_ENABLE, 0);
	rt2x00_set_field32(&reg, TX_LINK_CFG_REMOTE_UMFS_ENABLE, 0);
	rt2x00_set_field32(&reg, TX_LINK_CFG_TX_MRQ_EN, 0);
	rt2x00_set_field32(&reg, TX_LINK_CFG_TX_RDG_EN, 0);
	rt2x00_set_field32(&reg, TX_LINK_CFG_TX_CF_ACK_EN, 1);
	rt2x00_set_field32(&reg, TX_LINK_CFG_REMOTE_MFB, 0);
	rt2x00_set_field32(&reg, TX_LINK_CFG_REMOTE_MFS, 0);
	rt2800_register_write(rt2x00dev, TX_LINK_CFG, reg);

	reg = rt2800_register_read(rt2x00dev, TX_TIMEOUT_CFG);
	rt2x00_set_field32(&reg, TX_TIMEOUT_CFG_MPDU_LIFETIME, 9);
	rt2x00_set_field32(&reg, TX_TIMEOUT_CFG_RX_ACK_TIMEOUT, 32);
	rt2x00_set_field32(&reg, TX_TIMEOUT_CFG_TX_OP_TIMEOUT, 10);
	rt2800_register_write(rt2x00dev, TX_TIMEOUT_CFG, reg);

	reg = rt2800_register_read(rt2x00dev, MAX_LEN_CFG);
	rt2x00_set_field32(&reg, MAX_LEN_CFG_MAX_MPDU, AGGREGATION_SIZE);
	if (rt2x00_is_usb(rt2x00dev)) {
		drv_data->max_psdu = 3;
	} else if (rt2x00_rt_rev_gte(rt2x00dev, RT2872, REV_RT2872E) ||
		   rt2x00_rt(rt2x00dev, RT2883) ||
		   rt2x00_rt_rev_lt(rt2x00dev, RT3070, REV_RT3070E)) {
		drv_data->max_psdu = 2;
	} else {
		drv_data->max_psdu = 1;
	}
	rt2x00_set_field32(&reg, MAX_LEN_CFG_MAX_PSDU, drv_data->max_psdu);
	rt2x00_set_field32(&reg, MAX_LEN_CFG_MIN_PSDU, 10);
	rt2x00_set_field32(&reg, MAX_LEN_CFG_MIN_MPDU, 10);
	rt2800_register_write(rt2x00dev, MAX_LEN_CFG, reg);

	reg = rt2800_register_read(rt2x00dev, LED_CFG);
	rt2x00_set_field32(&reg, LED_CFG_ON_PERIOD, 70);
	rt2x00_set_field32(&reg, LED_CFG_OFF_PERIOD, 30);
	rt2x00_set_field32(&reg, LED_CFG_SLOW_BLINK_PERIOD, 3);
	rt2x00_set_field32(&reg, LED_CFG_R_LED_MODE, 3);
	rt2x00_set_field32(&reg, LED_CFG_G_LED_MODE, 3);
	rt2x00_set_field32(&reg, LED_CFG_Y_LED_MODE, 3);
	rt2x00_set_field32(&reg, LED_CFG_LED_POLAR, 1);
	rt2800_register_write(rt2x00dev, LED_CFG, reg);

	rt2800_register_write(rt2x00dev, PBF_MAX_PCNT, 0x1f3fbf9f);

	reg = rt2800_register_read(rt2x00dev, TX_RTY_CFG);
	rt2x00_set_field32(&reg, TX_RTY_CFG_SHORT_RTY_LIMIT, 2);
	rt2x00_set_field32(&reg, TX_RTY_CFG_LONG_RTY_LIMIT, 2);
	rt2x00_set_field32(&reg, TX_RTY_CFG_LONG_RTY_THRE, 2000);
	rt2x00_set_field32(&reg, TX_RTY_CFG_NON_AGG_RTY_MODE, 0);
	rt2x00_set_field32(&reg, TX_RTY_CFG_AGG_RTY_MODE, 0);
	rt2x00_set_field32(&reg, TX_RTY_CFG_TX_AUTO_FB_ENABLE, 1);
	rt2800_register_write(rt2x00dev, TX_RTY_CFG, reg);

	reg = rt2800_register_read(rt2x00dev, AUTO_RSP_CFG);
	rt2x00_set_field32(&reg, AUTO_RSP_CFG_AUTORESPONDER, 1);
	rt2x00_set_field32(&reg, AUTO_RSP_CFG_BAC_ACK_POLICY, 1);
	rt2x00_set_field32(&reg, AUTO_RSP_CFG_CTS_40_MMODE, 1);
	rt2x00_set_field32(&reg, AUTO_RSP_CFG_CTS_40_MREF, 0);
	rt2x00_set_field32(&reg, AUTO_RSP_CFG_AR_PREAMBLE, 0);
	rt2x00_set_field32(&reg, AUTO_RSP_CFG_DUAL_CTS_EN, 0);
	rt2x00_set_field32(&reg, AUTO_RSP_CFG_ACK_CTS_PSM_BIT, 0);
	rt2800_register_write(rt2x00dev, AUTO_RSP_CFG, reg);

	reg = rt2800_register_read(rt2x00dev, CCK_PROT_CFG);
	rt2x00_set_field32(&reg, CCK_PROT_CFG_PROTECT_RATE, 3);
	rt2x00_set_field32(&reg, CCK_PROT_CFG_PROTECT_CTRL, 0);
	rt2x00_set_field32(&reg, CCK_PROT_CFG_PROTECT_NAV_SHORT, 1);
	rt2x00_set_field32(&reg, CCK_PROT_CFG_TX_OP_ALLOW_CCK, 1);
	rt2x00_set_field32(&reg, CCK_PROT_CFG_TX_OP_ALLOW_OFDM, 1);
	rt2x00_set_field32(&reg, CCK_PROT_CFG_TX_OP_ALLOW_MM20, 1);
	rt2x00_set_field32(&reg, CCK_PROT_CFG_TX_OP_ALLOW_MM40, 0);
	rt2x00_set_field32(&reg, CCK_PROT_CFG_TX_OP_ALLOW_GF20, 1);
	rt2x00_set_field32(&reg, CCK_PROT_CFG_TX_OP_ALLOW_GF40, 0);
	rt2x00_set_field32(&reg, CCK_PROT_CFG_RTS_TH_EN, 1);
	rt2800_register_write(rt2x00dev, CCK_PROT_CFG, reg);

	reg = rt2800_register_read(rt2x00dev, OFDM_PROT_CFG);
	rt2x00_set_field32(&reg, OFDM_PROT_CFG_PROTECT_RATE, 3);
	rt2x00_set_field32(&reg, OFDM_PROT_CFG_PROTECT_CTRL, 0);
	rt2x00_set_field32(&reg, OFDM_PROT_CFG_PROTECT_NAV_SHORT, 1);
	rt2x00_set_field32(&reg, OFDM_PROT_CFG_TX_OP_ALLOW_CCK, 1);
	rt2x00_set_field32(&reg, OFDM_PROT_CFG_TX_OP_ALLOW_OFDM, 1);
	rt2x00_set_field32(&reg, OFDM_PROT_CFG_TX_OP_ALLOW_MM20, 1);
	rt2x00_set_field32(&reg, OFDM_PROT_CFG_TX_OP_ALLOW_MM40, 0);
	rt2x00_set_field32(&reg, OFDM_PROT_CFG_TX_OP_ALLOW_GF20, 1);
	rt2x00_set_field32(&reg, OFDM_PROT_CFG_TX_OP_ALLOW_GF40, 0);
	rt2x00_set_field32(&reg, OFDM_PROT_CFG_RTS_TH_EN, 1);
	rt2800_register_write(rt2x00dev, OFDM_PROT_CFG, reg);

	reg = rt2800_register_read(rt2x00dev, MM20_PROT_CFG);
	rt2x00_set_field32(&reg, MM20_PROT_CFG_PROTECT_RATE, 0x4004);
	rt2x00_set_field32(&reg, MM20_PROT_CFG_PROTECT_CTRL, 1);
	rt2x00_set_field32(&reg, MM20_PROT_CFG_PROTECT_NAV_SHORT, 1);
	rt2x00_set_field32(&reg, MM20_PROT_CFG_TX_OP_ALLOW_CCK, 0);
	rt2x00_set_field32(&reg, MM20_PROT_CFG_TX_OP_ALLOW_OFDM, 1);
	rt2x00_set_field32(&reg, MM20_PROT_CFG_TX_OP_ALLOW_MM20, 1);
	rt2x00_set_field32(&reg, MM20_PROT_CFG_TX_OP_ALLOW_MM40, 0);
	rt2x00_set_field32(&reg, MM20_PROT_CFG_TX_OP_ALLOW_GF20, 1);
	rt2x00_set_field32(&reg, MM20_PROT_CFG_TX_OP_ALLOW_GF40, 0);
	rt2x00_set_field32(&reg, MM20_PROT_CFG_RTS_TH_EN, 0);
	rt2800_register_write(rt2x00dev, MM20_PROT_CFG, reg);

	reg = rt2800_register_read(rt2x00dev, MM40_PROT_CFG);
	rt2x00_set_field32(&reg, MM40_PROT_CFG_PROTECT_RATE, 0x4084);
	rt2x00_set_field32(&reg, MM40_PROT_CFG_PROTECT_CTRL, 1);
	rt2x00_set_field32(&reg, MM40_PROT_CFG_PROTECT_NAV_SHORT, 1);
	rt2x00_set_field32(&reg, MM40_PROT_CFG_TX_OP_ALLOW_CCK, 0);
	rt2x00_set_field32(&reg, MM40_PROT_CFG_TX_OP_ALLOW_OFDM, 1);
	rt2x00_set_field32(&reg, MM40_PROT_CFG_TX_OP_ALLOW_MM20, 1);
	rt2x00_set_field32(&reg, MM40_PROT_CFG_TX_OP_ALLOW_MM40, 1);
	rt2x00_set_field32(&reg, MM40_PROT_CFG_TX_OP_ALLOW_GF20, 1);
	rt2x00_set_field32(&reg, MM40_PROT_CFG_TX_OP_ALLOW_GF40, 1);
	rt2x00_set_field32(&reg, MM40_PROT_CFG_RTS_TH_EN, 0);
	rt2800_register_write(rt2x00dev, MM40_PROT_CFG, reg);

	reg = rt2800_register_read(rt2x00dev, GF20_PROT_CFG);
	rt2x00_set_field32(&reg, GF20_PROT_CFG_PROTECT_RATE, 0x4004);
	rt2x00_set_field32(&reg, GF20_PROT_CFG_PROTECT_CTRL, 1);
	rt2x00_set_field32(&reg, GF20_PROT_CFG_PROTECT_NAV_SHORT, 1);
	rt2x00_set_field32(&reg, GF20_PROT_CFG_TX_OP_ALLOW_CCK, 0);
	rt2x00_set_field32(&reg, GF20_PROT_CFG_TX_OP_ALLOW_OFDM, 1);
	rt2x00_set_field32(&reg, GF20_PROT_CFG_TX_OP_ALLOW_MM20, 1);
	rt2x00_set_field32(&reg, GF20_PROT_CFG_TX_OP_ALLOW_MM40, 0);
	rt2x00_set_field32(&reg, GF20_PROT_CFG_TX_OP_ALLOW_GF20, 1);
	rt2x00_set_field32(&reg, GF20_PROT_CFG_TX_OP_ALLOW_GF40, 0);
	rt2x00_set_field32(&reg, GF20_PROT_CFG_RTS_TH_EN, 0);
	rt2800_register_write(rt2x00dev, GF20_PROT_CFG, reg);

	reg = rt2800_register_read(rt2x00dev, GF40_PROT_CFG);
	rt2x00_set_field32(&reg, GF40_PROT_CFG_PROTECT_RATE, 0x4084);
	rt2x00_set_field32(&reg, GF40_PROT_CFG_PROTECT_CTRL, 1);
	rt2x00_set_field32(&reg, GF40_PROT_CFG_PROTECT_NAV_SHORT, 1);
	rt2x00_set_field32(&reg, GF40_PROT_CFG_TX_OP_ALLOW_CCK, 0);
	rt2x00_set_field32(&reg, GF40_PROT_CFG_TX_OP_ALLOW_OFDM, 1);
	rt2x00_set_field32(&reg, GF40_PROT_CFG_TX_OP_ALLOW_MM20, 1);
	rt2x00_set_field32(&reg, GF40_PROT_CFG_TX_OP_ALLOW_MM40, 1);
	rt2x00_set_field32(&reg, GF40_PROT_CFG_TX_OP_ALLOW_GF20, 1);
	rt2x00_set_field32(&reg, GF40_PROT_CFG_TX_OP_ALLOW_GF40, 1);
	rt2x00_set_field32(&reg, GF40_PROT_CFG_RTS_TH_EN, 0);
	rt2800_register_write(rt2x00dev, GF40_PROT_CFG, reg);

	if (rt2x00_is_usb(rt2x00dev)) {
		rt2800_register_write(rt2x00dev, PBF_CFG, 0xf40006);

		reg = rt2800_register_read(rt2x00dev, WPDMA_GLO_CFG);
		rt2x00_set_field32(&reg, WPDMA_GLO_CFG_ENABLE_TX_DMA, 0);
		rt2x00_set_field32(&reg, WPDMA_GLO_CFG_TX_DMA_BUSY, 0);
		rt2x00_set_field32(&reg, WPDMA_GLO_CFG_ENABLE_RX_DMA, 0);
		rt2x00_set_field32(&reg, WPDMA_GLO_CFG_RX_DMA_BUSY, 0);
		rt2x00_set_field32(&reg, WPDMA_GLO_CFG_WP_DMA_BURST_SIZE, 3);
		rt2x00_set_field32(&reg, WPDMA_GLO_CFG_TX_WRITEBACK_DONE, 0);
		rt2x00_set_field32(&reg, WPDMA_GLO_CFG_BIG_ENDIAN, 0);
		rt2x00_set_field32(&reg, WPDMA_GLO_CFG_RX_HDR_SCATTER, 0);
		rt2x00_set_field32(&reg, WPDMA_GLO_CFG_HDR_SEG_LEN, 0);
		rt2800_register_write(rt2x00dev, WPDMA_GLO_CFG, reg);
	}

	/*
	 * The legacy driver also sets TXOP_CTRL_CFG_RESERVED_TRUN_EN to 1
	 * although it is reserved.
	 */
	reg = rt2800_register_read(rt2x00dev, TXOP_CTRL_CFG);
	rt2x00_set_field32(&reg, TXOP_CTRL_CFG_TIMEOUT_TRUN_EN, 1);
	rt2x00_set_field32(&reg, TXOP_CTRL_CFG_AC_TRUN_EN, 1);
	rt2x00_set_field32(&reg, TXOP_CTRL_CFG_TXRATEGRP_TRUN_EN, 1);
	rt2x00_set_field32(&reg, TXOP_CTRL_CFG_USER_MODE_TRUN_EN, 1);
	rt2x00_set_field32(&reg, TXOP_CTRL_CFG_MIMO_PS_TRUN_EN, 1);
	rt2x00_set_field32(&reg, TXOP_CTRL_CFG_RESERVED_TRUN_EN, 1);
	rt2x00_set_field32(&reg, TXOP_CTRL_CFG_LSIG_TXOP_EN, 0);
	rt2x00_set_field32(&reg, TXOP_CTRL_CFG_EXT_CCA_EN, 0);
	rt2x00_set_field32(&reg, TXOP_CTRL_CFG_EXT_CCA_DLY, 88);
	rt2x00_set_field32(&reg, TXOP_CTRL_CFG_EXT_CWMIN, 0);
	rt2800_register_write(rt2x00dev, TXOP_CTRL_CFG, reg);

	reg = rt2x00_rt(rt2x00dev, RT5592) ? 0x00000082 : 0x00000002;
	rt2800_register_write(rt2x00dev, TXOP_HLDR_ET, reg);

	reg = rt2800_register_read(rt2x00dev, TX_RTS_CFG);
	rt2x00_set_field32(&reg, TX_RTS_CFG_AUTO_RTS_RETRY_LIMIT, 7);
	rt2x00_set_field32(&reg, TX_RTS_CFG_RTS_THRES,
			   IEEE80211_MAX_RTS_THRESHOLD);
	rt2x00_set_field32(&reg, TX_RTS_CFG_RTS_FBK_EN, 1);
	rt2800_register_write(rt2x00dev, TX_RTS_CFG, reg);

	rt2800_register_write(rt2x00dev, EXP_ACK_TIME, 0x002400ca);

	/*
	 * Usually the CCK SIFS time should be set to 10 and the OFDM SIFS
	 * time should be set to 16. However, the original Ralink driver uses
	 * 16 for both and indeed using a value of 10 for CCK SIFS results in
	 * connection problems with 11g + CTS protection. Hence, use the same
	 * defaults as the Ralink driver: 16 for both, CCK and OFDM SIFS.
	 */
	reg = rt2800_register_read(rt2x00dev, XIFS_TIME_CFG);
	rt2x00_set_field32(&reg, XIFS_TIME_CFG_CCKM_SIFS_TIME, 16);
	rt2x00_set_field32(&reg, XIFS_TIME_CFG_OFDM_SIFS_TIME, 16);
	rt2x00_set_field32(&reg, XIFS_TIME_CFG_OFDM_XIFS_TIME, 4);
	rt2x00_set_field32(&reg, XIFS_TIME_CFG_EIFS, 314);
	rt2x00_set_field32(&reg, XIFS_TIME_CFG_BB_RXEND_ENABLE, 1);
	rt2800_register_write(rt2x00dev, XIFS_TIME_CFG, reg);

	rt2800_register_write(rt2x00dev, PWR_PIN_CFG, 0x00000003);

	/*
	 * ASIC will keep garbage value after boot, clear encryption keys.
	 */
	for (i = 0; i < 4; i++)
		rt2800_register_write(rt2x00dev,
					 SHARED_KEY_MODE_ENTRY(i), 0);

	for (i = 0; i < 256; i++) {
		rt2800_config_wcid(rt2x00dev, NULL, i);
		rt2800_delete_wcid_attr(rt2x00dev, i);
		rt2800_register_write(rt2x00dev, MAC_IVEIV_ENTRY(i), 0);
	}

	/*
	 * Clear all beacons
	 */
	for (i = 0; i < 8; i++)
		rt2800_clear_beacon_register(rt2x00dev, i);

	if (rt2x00_is_usb(rt2x00dev)) {
		reg = rt2800_register_read(rt2x00dev, US_CYC_CNT);
		rt2x00_set_field32(&reg, US_CYC_CNT_CLOCK_CYCLE, 30);
		rt2800_register_write(rt2x00dev, US_CYC_CNT, reg);
	} else if (rt2x00_is_pcie(rt2x00dev)) {
		reg = rt2800_register_read(rt2x00dev, US_CYC_CNT);
		rt2x00_set_field32(&reg, US_CYC_CNT_CLOCK_CYCLE, 125);
		rt2800_register_write(rt2x00dev, US_CYC_CNT, reg);
	}

	reg = rt2800_register_read(rt2x00dev, HT_FBK_CFG0);
	rt2x00_set_field32(&reg, HT_FBK_CFG0_HTMCS0FBK, 0);
	rt2x00_set_field32(&reg, HT_FBK_CFG0_HTMCS1FBK, 0);
	rt2x00_set_field32(&reg, HT_FBK_CFG0_HTMCS2FBK, 1);
	rt2x00_set_field32(&reg, HT_FBK_CFG0_HTMCS3FBK, 2);
	rt2x00_set_field32(&reg, HT_FBK_CFG0_HTMCS4FBK, 3);
	rt2x00_set_field32(&reg, HT_FBK_CFG0_HTMCS5FBK, 4);
	rt2x00_set_field32(&reg, HT_FBK_CFG0_HTMCS6FBK, 5);
	rt2x00_set_field32(&reg, HT_FBK_CFG0_HTMCS7FBK, 6);
	rt2800_register_write(rt2x00dev, HT_FBK_CFG0, reg);

	reg = rt2800_register_read(rt2x00dev, HT_FBK_CFG1);
	rt2x00_set_field32(&reg, HT_FBK_CFG1_HTMCS8FBK, 8);
	rt2x00_set_field32(&reg, HT_FBK_CFG1_HTMCS9FBK, 8);
	rt2x00_set_field32(&reg, HT_FBK_CFG1_HTMCS10FBK, 9);
	rt2x00_set_field32(&reg, HT_FBK_CFG1_HTMCS11FBK, 10);
	rt2x00_set_field32(&reg, HT_FBK_CFG1_HTMCS12FBK, 11);
	rt2x00_set_field32(&reg, HT_FBK_CFG1_HTMCS13FBK, 12);
	rt2x00_set_field32(&reg, HT_FBK_CFG1_HTMCS14FBK, 13);
	rt2x00_set_field32(&reg, HT_FBK_CFG1_HTMCS15FBK, 14);
	rt2800_register_write(rt2x00dev, HT_FBK_CFG1, reg);

	reg = rt2800_register_read(rt2x00dev, LG_FBK_CFG0);
	rt2x00_set_field32(&reg, LG_FBK_CFG0_OFDMMCS0FBK, 8);
	rt2x00_set_field32(&reg, LG_FBK_CFG0_OFDMMCS1FBK, 8);
	rt2x00_set_field32(&reg, LG_FBK_CFG0_OFDMMCS2FBK, 9);
	rt2x00_set_field32(&reg, LG_FBK_CFG0_OFDMMCS3FBK, 10);
	rt2x00_set_field32(&reg, LG_FBK_CFG0_OFDMMCS4FBK, 11);
	rt2x00_set_field32(&reg, LG_FBK_CFG0_OFDMMCS5FBK, 12);
	rt2x00_set_field32(&reg, LG_FBK_CFG0_OFDMMCS6FBK, 13);
	rt2x00_set_field32(&reg, LG_FBK_CFG0_OFDMMCS7FBK, 14);
	rt2800_register_write(rt2x00dev, LG_FBK_CFG0, reg);

	reg = rt2800_register_read(rt2x00dev, LG_FBK_CFG1);
	rt2x00_set_field32(&reg, LG_FBK_CFG0_CCKMCS0FBK, 0);
	rt2x00_set_field32(&reg, LG_FBK_CFG0_CCKMCS1FBK, 0);
	rt2x00_set_field32(&reg, LG_FBK_CFG0_CCKMCS2FBK, 1);
	rt2x00_set_field32(&reg, LG_FBK_CFG0_CCKMCS3FBK, 2);
	rt2800_register_write(rt2x00dev, LG_FBK_CFG1, reg);

	/*
	 * Do not force the BA window size, we use the TXWI to set it
	 */
	reg = rt2800_register_read(rt2x00dev, AMPDU_BA_WINSIZE);
	rt2x00_set_field32(&reg, AMPDU_BA_WINSIZE_FORCE_WINSIZE_ENABLE, 0);
	rt2x00_set_field32(&reg, AMPDU_BA_WINSIZE_FORCE_WINSIZE, 0);
	rt2800_register_write(rt2x00dev, AMPDU_BA_WINSIZE, reg);

	/*
	 * We must clear the error counters.
	 * These registers are cleared on read,
	 * so we may pass a useless variable to store the value.
	 */
	reg = rt2800_register_read(rt2x00dev, RX_STA_CNT0);
	reg = rt2800_register_read(rt2x00dev, RX_STA_CNT1);
	reg = rt2800_register_read(rt2x00dev, RX_STA_CNT2);
	reg = rt2800_register_read(rt2x00dev, TX_STA_CNT0);
	reg = rt2800_register_read(rt2x00dev, TX_STA_CNT1);
	reg = rt2800_register_read(rt2x00dev, TX_STA_CNT2);

	/*
	 * Setup leadtime for pre tbtt interrupt to 6ms
	 */
	reg = rt2800_register_read(rt2x00dev, INT_TIMER_CFG);
	rt2x00_set_field32(&reg, INT_TIMER_CFG_PRE_TBTT_TIMER, 6 << 4);
	rt2800_register_write(rt2x00dev, INT_TIMER_CFG, reg);

	/*
	 * Set up channel statistics timer
	 */
	reg = rt2800_register_read(rt2x00dev, CH_TIME_CFG);
	rt2x00_set_field32(&reg, CH_TIME_CFG_EIFS_BUSY, 1);
	rt2x00_set_field32(&reg, CH_TIME_CFG_NAV_BUSY, 1);
	rt2x00_set_field32(&reg, CH_TIME_CFG_RX_BUSY, 1);
	rt2x00_set_field32(&reg, CH_TIME_CFG_TX_BUSY, 1);
	rt2x00_set_field32(&reg, CH_TIME_CFG_TMR_EN, 1);
	rt2800_register_write(rt2x00dev, CH_TIME_CFG, reg);

	return 0;
}