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
struct rtl_phy {scalar_t__ current_chan_bw; } ;
struct rtl_priv {struct rtl_phy phy; } ;
struct rtl_hal {int /*<<< orphan*/  current_bandtype; } ;
struct ieee80211_hw {int dummy; } ;
typedef  enum radio_path { ____Placeholder_radio_path } radio_path ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  COMP_IQK ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 scalar_t__ HT_CHANNEL_WIDTH_80 ; 
#define  RF90_PATH_A 128 
 int RFREG_OFFSET_MASK ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  _rtl8821ae_iqk_rx_fill_iqc (struct ieee80211_hw*,int,int,int) ; 
 int /*<<< orphan*/  _rtl8821ae_iqk_tx_fill_iqc (struct ieee80211_hw*,int,int,int) ; 
 int cal_num ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int rtl_get_bbreg (struct ieee80211_hw*,int,int) ; 
 int rtl_get_rfreg (struct ieee80211_hw*,int,int,int) ; 
 struct rtl_hal* rtl_hal (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_set_bbreg (struct ieee80211_hw*,int,int,int) ; 
 int /*<<< orphan*/  rtl_set_rfreg (struct ieee80211_hw*,int,int,int,int) ; 
 int /*<<< orphan*/  rtl_write_dword (struct rtl_priv*,int,int) ; 

__attribute__((used)) static void _rtl8821ae_iqk_tx(struct ieee80211_hw *hw, enum radio_path path)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_phy *rtlphy = &rtlpriv->phy;
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));

	u32	tx_fail, rx_fail, delay_count, iqk_ready, cal_retry, cal = 0, temp_reg65;
	int	tx_x = 0, tx_y = 0, rx_x = 0, rx_y = 0, tx_average = 0, rx_average = 0;
	int	tx_x0[cal_num], tx_y0[cal_num], tx_x0_rxk[cal_num],
		tx_y0_rxk[cal_num], rx_x0[cal_num], rx_y0[cal_num],
		tx_dt[cal_num], rx_dt[cal_num];
	bool	tx0iqkok = false, rx0iqkok = false;
	bool	vdf_enable = false;
	int	i, k, vdf_y[3], vdf_x[3],
		ii, dx = 0, dy = 0, tx_finish = 0, rx_finish = 0;

	RT_TRACE(rtlpriv, COMP_IQK, DBG_LOUD,
			"BandWidth = %d.\n",
			 rtlphy->current_chan_bw);
	if (rtlphy->current_chan_bw == HT_CHANNEL_WIDTH_80)
		vdf_enable = true;

	while (cal < cal_num) {
		switch (path) {
		case RF90_PATH_A:
			temp_reg65 = rtl_get_rfreg(hw, path, 0x65, 0xffffffff);
			/* Path-A LOK */
			rtl_set_bbreg(hw, 0x82c, BIT(31), 0x0); /*[31] = 0 --> Page C*/
			/*========Path-A AFE all on========*/
			/*Port 0 DAC/ADC on*/
			rtl_write_dword(rtlpriv, 0xc60, 0x77777777);
			rtl_write_dword(rtlpriv, 0xc64, 0x77777777);
			rtl_write_dword(rtlpriv, 0xc68, 0x19791979);
			rtl_write_dword(rtlpriv, 0xc6c, 0x19791979);
			rtl_write_dword(rtlpriv, 0xc70, 0x19791979);
			rtl_write_dword(rtlpriv, 0xc74, 0x19791979);
			rtl_write_dword(rtlpriv, 0xc78, 0x19791979);
			rtl_write_dword(rtlpriv, 0xc7c, 0x19791979);
			rtl_write_dword(rtlpriv, 0xc80, 0x19791979);
			rtl_write_dword(rtlpriv, 0xc84, 0x19791979);

			rtl_set_bbreg(hw, 0xc00, 0xf, 0x4); /*hardware 3-wire off*/

			/* LOK Setting */
			/* ====== LOK ====== */
			/*DAC/ADC sampling rate (160 MHz)*/
			rtl_set_bbreg(hw, 0xc5c, BIT(26) | BIT(25) | BIT(24), 0x7);

			/* 2. LoK RF Setting (at BW = 20M) */
			rtl_set_rfreg(hw, path, 0xef, RFREG_OFFSET_MASK, 0x80002);
			rtl_set_rfreg(hw, path, 0x18, 0x00c00, 0x3);     /* BW 20M */
			rtl_set_rfreg(hw, path, 0x30, RFREG_OFFSET_MASK, 0x20000);
			rtl_set_rfreg(hw, path, 0x31, RFREG_OFFSET_MASK, 0x0003f);
			rtl_set_rfreg(hw, path, 0x32, RFREG_OFFSET_MASK, 0xf3fc3);
			rtl_set_rfreg(hw, path, 0x65, RFREG_OFFSET_MASK, 0x931d5);
			rtl_set_rfreg(hw, path, 0x8f, RFREG_OFFSET_MASK, 0x8a001);
			rtl_set_bbreg(hw, 0xcb8, 0xf, 0xd);
			rtl_write_dword(rtlpriv, 0x90c, 0x00008000);
			rtl_write_dword(rtlpriv, 0xb00, 0x03000100);
			rtl_set_bbreg(hw, 0xc94, BIT(0), 0x1);
			rtl_write_dword(rtlpriv, 0x978, 0x29002000);/* TX (X,Y) */
			rtl_write_dword(rtlpriv, 0x97c, 0xa9002000);/* RX (X,Y) */
			rtl_write_dword(rtlpriv, 0x984, 0x00462910);/* [0]:AGC_en, [15]:idac_K_Mask */

			rtl_set_bbreg(hw, 0x82c, BIT(31), 0x1); /* [31] = 1 --> Page C1 */
			rtl_write_dword(rtlpriv, 0xc88, 0x821403f4);

			if (rtlhal->current_bandtype)
				rtl_write_dword(rtlpriv, 0xc8c, 0x68163e96);
			else
				rtl_write_dword(rtlpriv, 0xc8c, 0x28163e96);

			rtl_write_dword(rtlpriv, 0xc80, 0x18008c10);/* TX_TONE_idx[9:0], TxK_Mask[29] TX_Tone = 16 */
			rtl_write_dword(rtlpriv, 0xc84, 0x38008c10);/* RX_TONE_idx[9:0], RxK_Mask[29] */
			rtl_write_dword(rtlpriv, 0xcb8, 0x00100000);/* cb8[20] \B1N SI/PI \A8ϥ\CE\C5v\A4\C1\B5\B9 iqk_dpk module */
			rtl_write_dword(rtlpriv, 0x980, 0xfa000000);
			rtl_write_dword(rtlpriv, 0x980, 0xf8000000);

			mdelay(10); /* Delay 10ms */
			rtl_write_dword(rtlpriv, 0xcb8, 0x00000000);

			rtl_set_bbreg(hw, 0x82c, BIT(31), 0x0); /* [31] = 0 --> Page C */
			rtl_set_rfreg(hw, path, 0x58, 0x7fe00, rtl_get_rfreg(hw, path, 0x8, 0xffc00)); /* Load LOK */

			switch (rtlphy->current_chan_bw) {
			case 1:
				rtl_set_rfreg(hw, path, 0x18, 0x00c00, 0x1);
				break;
			case 2:
				rtl_set_rfreg(hw, path, 0x18, 0x00c00, 0x0);
				break;
			default:
				break;
			}

			rtl_set_bbreg(hw, 0x82c, BIT(31), 0x1); /* [31] = 1 --> Page C1 */

			/* 3. TX RF Setting */
			rtl_set_bbreg(hw, 0x82c, BIT(31), 0x0); /* [31] = 0 --> Page C */
			rtl_set_rfreg(hw, path, 0xef, RFREG_OFFSET_MASK, 0x80000);
			rtl_set_rfreg(hw, path, 0x30, RFREG_OFFSET_MASK, 0x20000);
			rtl_set_rfreg(hw, path, 0x31, RFREG_OFFSET_MASK, 0x0003f);
			rtl_set_rfreg(hw, path, 0x32, RFREG_OFFSET_MASK, 0xf3fc3);
			rtl_set_rfreg(hw, path, 0x65, RFREG_OFFSET_MASK, 0x931d5);
			rtl_set_rfreg(hw, path, 0x8f, RFREG_OFFSET_MASK, 0x8a001);
			rtl_set_rfreg(hw, path, 0xef, RFREG_OFFSET_MASK, 0x00000);
			/* ODM_SetBBReg(pDM_Odm, 0xcb8, 0xf, 0xd); */
			rtl_write_dword(rtlpriv, 0x90c, 0x00008000);
			rtl_write_dword(rtlpriv, 0xb00, 0x03000100);
			rtl_set_bbreg(hw, 0xc94, BIT(0), 0x1);
			rtl_write_dword(rtlpriv, 0x978, 0x29002000);/* TX (X,Y) */
			rtl_write_dword(rtlpriv, 0x97c, 0xa9002000);/* RX (X,Y) */
			rtl_write_dword(rtlpriv, 0x984, 0x0046a910);/* [0]:AGC_en, [15]:idac_K_Mask */

			rtl_set_bbreg(hw, 0x82c, BIT(31), 0x1); /* [31] = 1 --> Page C1 */
			rtl_write_dword(rtlpriv, 0xc88, 0x821403f1);
			if (rtlhal->current_bandtype)
				rtl_write_dword(rtlpriv, 0xc8c, 0x40163e96);
			else
				rtl_write_dword(rtlpriv, 0xc8c, 0x00163e96);

			if (vdf_enable == 1) {
				RT_TRACE(rtlpriv, COMP_IQK, DBG_LOUD, "VDF_enable\n");
				for (k = 0; k <= 2; k++) {
					switch (k) {
					case 0:
						rtl_write_dword(rtlpriv, 0xc80, 0x18008c38);/* TX_TONE_idx[9:0], TxK_Mask[29] TX_Tone = 16 */
						rtl_write_dword(rtlpriv, 0xc84, 0x38008c38);/* RX_TONE_idx[9:0], RxK_Mask[29] */
						rtl_set_bbreg(hw, 0xce8, BIT(31), 0x0);
						break;
					case 1:
						rtl_set_bbreg(hw, 0xc80, BIT(28), 0x0);
						rtl_set_bbreg(hw, 0xc84, BIT(28), 0x0);
						rtl_set_bbreg(hw, 0xce8, BIT(31), 0x0);
						break;
					case 2:
						RT_TRACE(rtlpriv, COMP_IQK, DBG_LOUD,
							"vdf_y[1] = %x;;;vdf_y[0] = %x\n", vdf_y[1]>>21 & 0x00007ff, vdf_y[0]>>21 & 0x00007ff);
						RT_TRACE(rtlpriv, COMP_IQK, DBG_LOUD,
							"vdf_x[1] = %x;;;vdf_x[0] = %x\n", vdf_x[1]>>21 & 0x00007ff, vdf_x[0]>>21 & 0x00007ff);
						tx_dt[cal] = (vdf_y[1]>>20)-(vdf_y[0]>>20);
						tx_dt[cal] = ((16*tx_dt[cal])*10000/15708);
						tx_dt[cal] = (tx_dt[cal] >> 1)+(tx_dt[cal] & BIT(0));
						rtl_write_dword(rtlpriv, 0xc80, 0x18008c20);/* TX_TONE_idx[9:0], TxK_Mask[29] TX_Tone = 16 */
						rtl_write_dword(rtlpriv, 0xc84, 0x38008c20);/* RX_TONE_idx[9:0], RxK_Mask[29] */
						rtl_set_bbreg(hw, 0xce8, BIT(31), 0x1);
						rtl_set_bbreg(hw, 0xce8, 0x3fff0000, tx_dt[cal] & 0x00003fff);
						break;
					default:
						break;
					}
					rtl_write_dword(rtlpriv, 0xcb8, 0x00100000);/* cb8[20] \B1N SI/PI \A8ϥ\CE\C5v\A4\C1\B5\B9 iqk_dpk module */
					cal_retry = 0;
					while (1) {
						/* one shot */
						rtl_write_dword(rtlpriv, 0x980, 0xfa000000);
						rtl_write_dword(rtlpriv, 0x980, 0xf8000000);

						mdelay(10); /* Delay 10ms */
						rtl_write_dword(rtlpriv, 0xcb8, 0x00000000);
						delay_count = 0;
						while (1) {
							iqk_ready = rtl_get_bbreg(hw, 0xd00, BIT(10));
							if ((~iqk_ready) || (delay_count > 20))
								break;
							else{
								mdelay(1);
								delay_count++;
							}
						}

						if (delay_count < 20) {							/* If 20ms No Result, then cal_retry++ */
							/* ============TXIQK Check============== */
							tx_fail = rtl_get_bbreg(hw, 0xd00, BIT(12));

							if (~tx_fail) {
								rtl_write_dword(rtlpriv, 0xcb8, 0x02000000);
								vdf_x[k] = rtl_get_bbreg(hw, 0xd00, 0x07ff0000)<<21;
								rtl_write_dword(rtlpriv, 0xcb8, 0x04000000);
								vdf_y[k] = rtl_get_bbreg(hw, 0xd00, 0x07ff0000)<<21;
								tx0iqkok = true;
								break;
							} else {
								rtl_set_bbreg(hw, 0xccc, 0x000007ff, 0x0);
								rtl_set_bbreg(hw, 0xcd4, 0x000007ff, 0x200);
								tx0iqkok = false;
								cal_retry++;
								if (cal_retry == 10)
									break;
							}
						} else {
							tx0iqkok = false;
							cal_retry++;
							if (cal_retry == 10)
								break;
						}
					}
				}
				if (k == 3) {
					tx_x0[cal] = vdf_x[k-1];
					tx_y0[cal] = vdf_y[k-1];
				}
			} else {
				rtl_write_dword(rtlpriv, 0xc80, 0x18008c10);/* TX_TONE_idx[9:0], TxK_Mask[29] TX_Tone = 16 */
				rtl_write_dword(rtlpriv, 0xc84, 0x38008c10);/* RX_TONE_idx[9:0], RxK_Mask[29] */
				rtl_write_dword(rtlpriv, 0xcb8, 0x00100000);/* cb8[20] \B1N SI/PI \A8ϥ\CE\C5v\A4\C1\B5\B9 iqk_dpk module */
				cal_retry = 0;
				while (1) {
					/* one shot */
					rtl_write_dword(rtlpriv, 0x980, 0xfa000000);
					rtl_write_dword(rtlpriv, 0x980, 0xf8000000);

					mdelay(10); /* Delay 10ms */
					rtl_write_dword(rtlpriv, 0xcb8, 0x00000000);
					delay_count = 0;
					while (1) {
						iqk_ready = rtl_get_bbreg(hw, 0xd00, BIT(10));
						if ((~iqk_ready) || (delay_count > 20))
							break;
						else{
							mdelay(1);
							delay_count++;
						}
					}

					if (delay_count < 20) {							/* If 20ms No Result, then cal_retry++ */
						/* ============TXIQK Check============== */
						tx_fail = rtl_get_bbreg(hw, 0xd00, BIT(12));

						if (~tx_fail) {
							rtl_write_dword(rtlpriv, 0xcb8, 0x02000000);
							tx_x0[cal] = rtl_get_bbreg(hw, 0xd00, 0x07ff0000)<<21;
							rtl_write_dword(rtlpriv, 0xcb8, 0x04000000);
							tx_y0[cal] = rtl_get_bbreg(hw, 0xd00, 0x07ff0000)<<21;
							tx0iqkok = true;
							break;
						} else {
							rtl_set_bbreg(hw, 0xccc, 0x000007ff, 0x0);
							rtl_set_bbreg(hw, 0xcd4, 0x000007ff, 0x200);
							tx0iqkok = false;
							cal_retry++;
							if (cal_retry == 10)
								break;
						}
					} else {
						tx0iqkok = false;
						cal_retry++;
						if (cal_retry == 10)
							break;
					}
				}
			}

			if (tx0iqkok == false)
				break;				/* TXK fail, Don't do RXK */

			if (vdf_enable == 1) {
				rtl_set_bbreg(hw, 0xce8, BIT(31), 0x0);    /* TX VDF Disable */
				RT_TRACE(rtlpriv, COMP_IQK, DBG_LOUD, "RXVDF Start\n");
				for (k = 0; k <= 2; k++) {
					/* ====== RX mode TXK (RXK Step 1) ====== */
					rtl_set_bbreg(hw, 0x82c, BIT(31), 0x0); /* [31] = 0 --> Page C */
					/* 1. TX RF Setting */
					rtl_set_rfreg(hw, path, 0xef, RFREG_OFFSET_MASK, 0x80000);
					rtl_set_rfreg(hw, path, 0x30, RFREG_OFFSET_MASK, 0x30000);
					rtl_set_rfreg(hw, path, 0x31, RFREG_OFFSET_MASK, 0x00029);
					rtl_set_rfreg(hw, path, 0x32, RFREG_OFFSET_MASK, 0xd7ffb);
					rtl_set_rfreg(hw, path, 0x65, RFREG_OFFSET_MASK, temp_reg65);
					rtl_set_rfreg(hw, path, 0x8f, RFREG_OFFSET_MASK, 0x8a001);
					rtl_set_rfreg(hw, path, 0xef, RFREG_OFFSET_MASK, 0x00000);

					rtl_set_bbreg(hw, 0xcb8, 0xf, 0xd);
					rtl_write_dword(rtlpriv, 0x978, 0x29002000);/* TX (X,Y) */
					rtl_write_dword(rtlpriv, 0x97c, 0xa9002000);/* RX (X,Y) */
					rtl_write_dword(rtlpriv, 0x984, 0x0046a910);/* [0]:AGC_en, [15]:idac_K_Mask */
					rtl_write_dword(rtlpriv, 0x90c, 0x00008000);
					rtl_write_dword(rtlpriv, 0xb00, 0x03000100);
					rtl_set_bbreg(hw, 0x82c, BIT(31), 0x1); /* [31] = 1 --> Page C1 */
					switch (k) {
					case 0:
						{
							rtl_write_dword(rtlpriv, 0xc80, 0x18008c38);/* TX_TONE_idx[9:0], TxK_Mask[29] TX_Tone = 16 */
							rtl_write_dword(rtlpriv, 0xc84, 0x38008c38);/* RX_TONE_idx[9:0], RxK_Mask[29] */
							rtl_set_bbreg(hw, 0xce8, BIT(30), 0x0);
						}
						break;
					case 1:
						{
							rtl_write_dword(rtlpriv, 0xc80, 0x08008c38);/* TX_TONE_idx[9:0], TxK_Mask[29] TX_Tone = 16 */
							rtl_write_dword(rtlpriv, 0xc84, 0x28008c38);/* RX_TONE_idx[9:0], RxK_Mask[29] */
							rtl_set_bbreg(hw, 0xce8, BIT(30), 0x0);
						}
						break;
					case 2:
						{
							RT_TRACE(rtlpriv, COMP_IQK, DBG_LOUD,
							"VDF_Y[1] = %x;;;VDF_Y[0] = %x\n",
							vdf_y[1]>>21 & 0x00007ff, vdf_y[0]>>21 & 0x00007ff);
							RT_TRACE(rtlpriv, COMP_IQK, DBG_LOUD,
							"VDF_X[1] = %x;;;VDF_X[0] = %x\n",
							vdf_x[1]>>21 & 0x00007ff, vdf_x[0]>>21 & 0x00007ff);
							rx_dt[cal] = (vdf_y[1]>>20)-(vdf_y[0]>>20);
							RT_TRACE(rtlpriv, COMP_IQK, DBG_LOUD, "Rx_dt = %d\n", rx_dt[cal]);
							rx_dt[cal] = ((16*rx_dt[cal])*10000/13823);
							rx_dt[cal] = (rx_dt[cal] >> 1)+(rx_dt[cal] & BIT(0));
							rtl_write_dword(rtlpriv, 0xc80, 0x18008c20);/* TX_TONE_idx[9:0], TxK_Mask[29] TX_Tone = 16 */
							rtl_write_dword(rtlpriv, 0xc84, 0x38008c20);/* RX_TONE_idx[9:0], RxK_Mask[29] */
							rtl_set_bbreg(hw, 0xce8, 0x00003fff, rx_dt[cal] & 0x00003fff);
						}
						break;
					default:
						break;
					}
					rtl_write_dword(rtlpriv, 0xc88, 0x821603e0);
					rtl_write_dword(rtlpriv, 0xc8c, 0x68163e96);
					rtl_write_dword(rtlpriv, 0xcb8, 0x00100000);/* cb8[20] \B1N SI/PI \A8ϥ\CE\C5v\A4\C1\B5\B9 iqk_dpk module */
					cal_retry = 0;
					while (1) {
						/* one shot */
						rtl_write_dword(rtlpriv, 0x980, 0xfa000000);
						rtl_write_dword(rtlpriv, 0x980, 0xf8000000);

						mdelay(10); /* Delay 10ms */
						rtl_write_dword(rtlpriv, 0xcb8, 0x00000000);
						delay_count = 0;
						while (1) {
							iqk_ready = rtl_get_bbreg(hw, 0xd00, BIT(10));
							if ((~iqk_ready) || (delay_count > 20))
								break;
							else{
								mdelay(1);
								delay_count++;
							}
						}

						if (delay_count < 20) {							/* If 20ms No Result, then cal_retry++ */
							/* ============TXIQK Check============== */
							tx_fail = rtl_get_bbreg(hw, 0xd00, BIT(12));

							if (~tx_fail) {
								rtl_write_dword(rtlpriv, 0xcb8, 0x02000000);
								tx_x0_rxk[cal] = rtl_get_bbreg(hw, 0xd00, 0x07ff0000)<<21;
								rtl_write_dword(rtlpriv, 0xcb8, 0x04000000);
								tx_y0_rxk[cal] = rtl_get_bbreg(hw, 0xd00, 0x07ff0000)<<21;
								tx0iqkok = true;
								break;
							} else{
								tx0iqkok = false;
								cal_retry++;
								if (cal_retry == 10)
									break;
							}
						} else {
							tx0iqkok = false;
							cal_retry++;
							if (cal_retry == 10)
								break;
						}
					}

					if (tx0iqkok == false) {   /* If RX mode TXK fail, then take TXK Result */
						tx_x0_rxk[cal] = tx_x0[cal];
						tx_y0_rxk[cal] = tx_y0[cal];
						tx0iqkok = true;
						RT_TRACE(rtlpriv,
							 COMP_IQK,
							 DBG_LOUD,
							 "RXK Step 1 fail\n");
					}

					/* ====== RX IQK ====== */
					rtl_set_bbreg(hw, 0x82c, BIT(31), 0x0); /* [31] = 0 --> Page C */
					/* 1. RX RF Setting */
					rtl_set_rfreg(hw, path, 0xef, RFREG_OFFSET_MASK, 0x80000);
					rtl_set_rfreg(hw, path, 0x30, RFREG_OFFSET_MASK, 0x30000);
					rtl_set_rfreg(hw, path, 0x31, RFREG_OFFSET_MASK, 0x0002f);
					rtl_set_rfreg(hw, path, 0x32, RFREG_OFFSET_MASK, 0xfffbb);
					rtl_set_rfreg(hw, path, 0x8f, RFREG_OFFSET_MASK, 0x88001);
					rtl_set_rfreg(hw, path, 0x65, RFREG_OFFSET_MASK, 0x931d8);
					rtl_set_rfreg(hw, path, 0xef, RFREG_OFFSET_MASK, 0x00000);

					rtl_set_bbreg(hw, 0x978, 0x03FF8000, (tx_x0_rxk[cal])>>21&0x000007ff);
					rtl_set_bbreg(hw, 0x978, 0x000007FF, (tx_y0_rxk[cal])>>21&0x000007ff);
					rtl_set_bbreg(hw, 0x978, BIT(31), 0x1);
					rtl_set_bbreg(hw, 0x97c, BIT(31), 0x0);
					rtl_set_bbreg(hw, 0xcb8, 0xF, 0xe);
					rtl_write_dword(rtlpriv, 0x90c, 0x00008000);
					rtl_write_dword(rtlpriv, 0x984, 0x0046a911);

					rtl_set_bbreg(hw, 0x82c, BIT(31), 0x1); /* [31] = 1 --> Page C1 */
					rtl_set_bbreg(hw, 0xc80, BIT(29), 0x1);
					rtl_set_bbreg(hw, 0xc84, BIT(29), 0x0);
					rtl_write_dword(rtlpriv, 0xc88, 0x02140119);

					rtl_write_dword(rtlpriv, 0xc8c, 0x28160d00); /* pDM_Odm->SupportInterface == 1 */

					if (k == 2)
						rtl_set_bbreg(hw, 0xce8, BIT(30), 0x1);  /* RX VDF Enable */
					rtl_write_dword(rtlpriv, 0xcb8, 0x00100000);/* cb8[20] \B1N SI/PI \A8ϥ\CE\C5v\A4\C1\B5\B9 iqk_dpk module */

					cal_retry = 0;
					while (1) {
						/* one shot */
						rtl_write_dword(rtlpriv, 0x980, 0xfa000000);
						rtl_write_dword(rtlpriv, 0x980, 0xf8000000);

						mdelay(10); /* Delay 10ms */
						rtl_write_dword(rtlpriv, 0xcb8, 0x00000000);
						delay_count = 0;
						while (1) {
							iqk_ready = rtl_get_bbreg(hw, 0xd00, BIT(10));
							if ((~iqk_ready) || (delay_count > 20))
								break;
							else{
								mdelay(1);
								delay_count++;
							}
						}

						if (delay_count < 20) {	/* If 20ms No Result, then cal_retry++ */
							/* ============RXIQK Check============== */
							rx_fail = rtl_get_bbreg(hw, 0xd00, BIT(11));
							if (rx_fail == 0) {
								rtl_write_dword(rtlpriv, 0xcb8, 0x06000000);
								vdf_x[k] = rtl_get_bbreg(hw, 0xd00, 0x07ff0000)<<21;
								rtl_write_dword(rtlpriv, 0xcb8, 0x08000000);
								vdf_y[k] = rtl_get_bbreg(hw, 0xd00, 0x07ff0000)<<21;
								rx0iqkok = true;
								break;
							} else {
								rtl_set_bbreg(hw, 0xc10, 0x000003ff, 0x200>>1);
								rtl_set_bbreg(hw, 0xc10, 0x03ff0000, 0x0>>1);
								rx0iqkok = false;
								cal_retry++;
								if (cal_retry == 10)
									break;

							}
						} else{
							rx0iqkok = false;
							cal_retry++;
							if (cal_retry == 10)
								break;
						}
					}

				}
				if (k == 3) {
					rx_x0[cal] = vdf_x[k-1];
					rx_y0[cal] = vdf_y[k-1];
				}
				rtl_set_bbreg(hw, 0xce8, BIT(31), 0x1);    /* TX VDF Enable */
			}

			else{
				/* ====== RX mode TXK (RXK Step 1) ====== */
				rtl_set_bbreg(hw, 0x82c, BIT(31), 0x0); /* [31] = 0 --> Page C */
				/* 1. TX RF Setting */
				rtl_set_rfreg(hw, path, 0xef, RFREG_OFFSET_MASK, 0x80000);
				rtl_set_rfreg(hw, path, 0x30, RFREG_OFFSET_MASK, 0x30000);
				rtl_set_rfreg(hw, path, 0x31, RFREG_OFFSET_MASK, 0x00029);
				rtl_set_rfreg(hw, path, 0x32, RFREG_OFFSET_MASK, 0xd7ffb);
				rtl_set_rfreg(hw, path, 0x65, RFREG_OFFSET_MASK, temp_reg65);
				rtl_set_rfreg(hw, path, 0x8f, RFREG_OFFSET_MASK, 0x8a001);
				rtl_set_rfreg(hw, path, 0xef, RFREG_OFFSET_MASK, 0x00000);
				rtl_write_dword(rtlpriv, 0x90c, 0x00008000);
				rtl_write_dword(rtlpriv, 0xb00, 0x03000100);
				rtl_write_dword(rtlpriv, 0x984, 0x0046a910);/* [0]:AGC_en, [15]:idac_K_Mask */

				rtl_set_bbreg(hw, 0x82c, BIT(31), 0x1); /* [31] = 1 --> Page C1 */
				rtl_write_dword(rtlpriv, 0xc80, 0x18008c10);/* TX_TONE_idx[9:0], TxK_Mask[29] TX_Tone = 16 */
				rtl_write_dword(rtlpriv, 0xc84, 0x38008c10);/* RX_TONE_idx[9:0], RxK_Mask[29] */
				rtl_write_dword(rtlpriv, 0xc88, 0x821603e0);
				/* ODM_Write4Byte(pDM_Odm, 0xc8c, 0x68163e96); */
				rtl_write_dword(rtlpriv, 0xcb8, 0x00100000);/* cb8[20] \B1N SI/PI \A8ϥ\CE\C5v\A4\C1\B5\B9 iqk_dpk module */
				cal_retry = 0;
				while (1) {
					/* one shot */
					rtl_write_dword(rtlpriv, 0x980, 0xfa000000);
					rtl_write_dword(rtlpriv, 0x980, 0xf8000000);

					mdelay(10); /* Delay 10ms */
					rtl_write_dword(rtlpriv, 0xcb8, 0x00000000);
					delay_count = 0;
					while (1) {
						iqk_ready = rtl_get_bbreg(hw, 0xd00, BIT(10));
						if ((~iqk_ready) || (delay_count > 20))
							break;
						else{
							mdelay(1);
							delay_count++;
						}
					}

					if (delay_count < 20) {							/* If 20ms No Result, then cal_retry++ */
						/* ============TXIQK Check============== */
						tx_fail = rtl_get_bbreg(hw, 0xd00, BIT(12));

						if (~tx_fail) {
							rtl_write_dword(rtlpriv, 0xcb8, 0x02000000);
							tx_x0_rxk[cal] = rtl_get_bbreg(hw, 0xd00, 0x07ff0000)<<21;
							rtl_write_dword(rtlpriv, 0xcb8, 0x04000000);
							tx_y0_rxk[cal] = rtl_get_bbreg(hw, 0xd00, 0x07ff0000)<<21;
							tx0iqkok = true;
							break;
						} else {
							tx0iqkok = false;
							cal_retry++;
							if (cal_retry == 10)
								break;
						}
					} else{
						tx0iqkok = false;
						cal_retry++;
						if (cal_retry == 10)
							break;
					}
				}

				if (tx0iqkok == false) {   /* If RX mode TXK fail, then take TXK Result */
					tx_x0_rxk[cal] = tx_x0[cal];
					tx_y0_rxk[cal] = tx_y0[cal];
					tx0iqkok = true;
					RT_TRACE(rtlpriv, COMP_IQK,
						 DBG_LOUD, "1");
				}

				/* ====== RX IQK ====== */
				rtl_set_bbreg(hw, 0x82c, BIT(31), 0x0); /* [31] = 0 --> Page C */
				/* 1. RX RF Setting */
				rtl_set_rfreg(hw, path, 0xef, RFREG_OFFSET_MASK, 0x80000);
				rtl_set_rfreg(hw, path, 0x30, RFREG_OFFSET_MASK, 0x30000);
				rtl_set_rfreg(hw, path, 0x31, RFREG_OFFSET_MASK, 0x0002f);
				rtl_set_rfreg(hw, path, 0x32, RFREG_OFFSET_MASK, 0xfffbb);
				rtl_set_rfreg(hw, path, 0x8f, RFREG_OFFSET_MASK, 0x88001);
				rtl_set_rfreg(hw, path, 0x65, RFREG_OFFSET_MASK, 0x931d8);
				rtl_set_rfreg(hw, path, 0xef, RFREG_OFFSET_MASK, 0x00000);

				rtl_set_bbreg(hw, 0x978, 0x03FF8000, (tx_x0_rxk[cal])>>21&0x000007ff);
				rtl_set_bbreg(hw, 0x978, 0x000007FF, (tx_y0_rxk[cal])>>21&0x000007ff);
				rtl_set_bbreg(hw, 0x978, BIT(31), 0x1);
				rtl_set_bbreg(hw, 0x97c, BIT(31), 0x0);
				/* ODM_SetBBReg(pDM_Odm, 0xcb8, 0xF, 0xe); */
				rtl_write_dword(rtlpriv, 0x90c, 0x00008000);
				rtl_write_dword(rtlpriv, 0x984, 0x0046a911);

				rtl_set_bbreg(hw, 0x82c, BIT(31), 0x1); /* [31] = 1 --> Page C1 */
				rtl_write_dword(rtlpriv, 0xc80, 0x38008c10);/* TX_TONE_idx[9:0], TxK_Mask[29] TX_Tone = 16 */
				rtl_write_dword(rtlpriv, 0xc84, 0x18008c10);/* RX_TONE_idx[9:0], RxK_Mask[29] */
				rtl_write_dword(rtlpriv, 0xc88, 0x02140119);

				rtl_write_dword(rtlpriv, 0xc8c, 0x28160d00); /*pDM_Odm->SupportInterface == 1*/

				rtl_write_dword(rtlpriv, 0xcb8, 0x00100000);/* cb8[20] \B1N SI/PI \A8ϥ\CE\C5v\A4\C1\B5\B9 iqk_dpk module */

				cal_retry = 0;
				while (1) {
					/* one shot */
					rtl_write_dword(rtlpriv, 0x980, 0xfa000000);
					rtl_write_dword(rtlpriv, 0x980, 0xf8000000);

					mdelay(10); /* Delay 10ms */
					rtl_write_dword(rtlpriv, 0xcb8, 0x00000000);
					delay_count = 0;
					while (1) {
						iqk_ready = rtl_get_bbreg(hw, 0xd00, BIT(10));
						if ((~iqk_ready) || (delay_count > 20))
							break;
						else{
							mdelay(1);
							delay_count++;
						}
					}

					if (delay_count < 20) {	/* If 20ms No Result, then cal_retry++ */
						/* ============RXIQK Check============== */
						rx_fail = rtl_get_bbreg(hw, 0xd00, BIT(11));
						if (rx_fail == 0) {
							rtl_write_dword(rtlpriv, 0xcb8, 0x06000000);
							rx_x0[cal] = rtl_get_bbreg(hw, 0xd00, 0x07ff0000)<<21;
							rtl_write_dword(rtlpriv, 0xcb8, 0x08000000);
							rx_y0[cal] = rtl_get_bbreg(hw, 0xd00, 0x07ff0000)<<21;
							rx0iqkok = true;
							break;
						} else{
							rtl_set_bbreg(hw, 0xc10, 0x000003ff, 0x200>>1);
							rtl_set_bbreg(hw, 0xc10, 0x03ff0000, 0x0>>1);
							rx0iqkok = false;
							cal_retry++;
							if (cal_retry == 10)
								break;

						}
					} else{
						rx0iqkok = false;
						cal_retry++;
						if (cal_retry == 10)
							break;
					}
				}
			}

			if (tx0iqkok)
				tx_average++;
			if (rx0iqkok)
				rx_average++;
			rtl_set_bbreg(hw, 0x82c, BIT(31), 0x0); /* [31] = 0 --> Page C */
			rtl_set_rfreg(hw, path, 0x65, RFREG_OFFSET_MASK, temp_reg65);
			break;
		default:
			break;
		}
		cal++;
	}

	/* FillIQK Result */
	switch (path) {
	case RF90_PATH_A:
		RT_TRACE(rtlpriv, COMP_IQK, DBG_LOUD,
			 "========Path_A =======\n");
		if (tx_average == 0)
			break;

		for (i = 0; i < tx_average; i++) {
			RT_TRACE(rtlpriv, COMP_IQK, DBG_LOUD,
				 "TX_X0_RXK[%d] = %x ;; TX_Y0_RXK[%d] = %x\n", i,
				 (tx_x0_rxk[i])>>21&0x000007ff, i,
				 (tx_y0_rxk[i])>>21&0x000007ff);
			RT_TRACE(rtlpriv, COMP_IQK, DBG_LOUD,
				 "TX_X0[%d] = %x ;; TX_Y0[%d] = %x\n", i,
				 (tx_x0[i])>>21&0x000007ff, i,
				 (tx_y0[i])>>21&0x000007ff);
		}
		for (i = 0; i < tx_average; i++) {
			for (ii = i+1; ii < tx_average; ii++) {
				dx = (tx_x0[i]>>21) - (tx_x0[ii]>>21);
				if (dx < 3 && dx > -3) {
					dy = (tx_y0[i]>>21) - (tx_y0[ii]>>21);
					if (dy < 3 && dy > -3) {
						tx_x = ((tx_x0[i]>>21) + (tx_x0[ii]>>21))/2;
						tx_y = ((tx_y0[i]>>21) + (tx_y0[ii]>>21))/2;
						tx_finish = 1;
						break;
					}
				}
			}
			if (tx_finish == 1)
				break;
		}

		if (tx_finish == 1)
			_rtl8821ae_iqk_tx_fill_iqc(hw, path, tx_x, tx_y); /* ? */
		else
			_rtl8821ae_iqk_tx_fill_iqc(hw, path, 0x200, 0x0);

		if (rx_average == 0)
			break;

		for (i = 0; i < rx_average; i++)
			RT_TRACE(rtlpriv, COMP_IQK, DBG_LOUD,
				"RX_X0[%d] = %x ;; RX_Y0[%d] = %x\n", i,
				(rx_x0[i])>>21&0x000007ff, i,
				(rx_y0[i])>>21&0x000007ff);
		for (i = 0; i < rx_average; i++) {
			for (ii = i+1; ii < rx_average; ii++) {
				dx = (rx_x0[i]>>21) - (rx_x0[ii]>>21);
				if (dx < 4 && dx > -4) {
					dy = (rx_y0[i]>>21) - (rx_y0[ii]>>21);
					if (dy < 4 && dy > -4) {
						rx_x = ((rx_x0[i]>>21) + (rx_x0[ii]>>21))/2;
						rx_y = ((rx_y0[i]>>21) + (rx_y0[ii]>>21))/2;
						rx_finish = 1;
						break;
					}
				}
			}
			if (rx_finish == 1)
				break;
		}

		if (rx_finish == 1)
			_rtl8821ae_iqk_rx_fill_iqc(hw, path, rx_x, rx_y);
		else
			_rtl8821ae_iqk_rx_fill_iqc(hw, path, 0x200, 0x0);
		break;
	default:
		break;
	}
}