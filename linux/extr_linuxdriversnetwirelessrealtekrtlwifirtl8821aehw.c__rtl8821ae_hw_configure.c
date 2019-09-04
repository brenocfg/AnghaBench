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
struct rtl_priv {int dummy; } ;
struct rtl_pci {int reg_bcn_ctrl_val; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int RATE_ALL_CCK ; 
 int RATE_ALL_OFDM_AG ; 
 scalar_t__ REG_AMPDU_MAX_TIME ; 
 scalar_t__ REG_ARFR0 ; 
 scalar_t__ REG_ARFR1 ; 
 scalar_t__ REG_ARFR2 ; 
 scalar_t__ REG_ARFR3 ; 
 scalar_t__ REG_BCN_CTRL ; 
 scalar_t__ REG_DARFRC ; 
 scalar_t__ REG_FAST_EDCA_CTRL ; 
 int /*<<< orphan*/  REG_FWHW_TXQ_CTRL ; 
 scalar_t__ REG_HT_SINGLE_AMPDU ; 
 int /*<<< orphan*/  REG_MAX_AGGR_NUM ; 
 int /*<<< orphan*/  REG_NAV_PROT_LEN ; 
 scalar_t__ REG_RARFRC ; 
 int /*<<< orphan*/  REG_RL ; 
 scalar_t__ REG_RRSR ; 
 scalar_t__ REG_RX_PKT_LIMIT ; 
 scalar_t__ REG_TBTT_PROHIBIT ; 
 struct rtl_pci* rtl_pcidev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_pcipriv (struct ieee80211_hw*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_write_byte (struct rtl_priv*,scalar_t__,int) ; 
 int /*<<< orphan*/  rtl_write_dword (struct rtl_priv*,scalar_t__,int) ; 
 int /*<<< orphan*/  rtl_write_word (struct rtl_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void _rtl8821ae_hw_configure(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	u32 reg_rrsr;

	reg_rrsr = RATE_ALL_CCK | RATE_ALL_OFDM_AG;

	rtl_write_dword(rtlpriv, REG_RRSR, reg_rrsr);
	/* ARFB table 9 for 11ac 5G 2SS */
	rtl_write_dword(rtlpriv, REG_ARFR0 + 4, 0xfffff000);
	/* ARFB table 10 for 11ac 5G 1SS */
	rtl_write_dword(rtlpriv, REG_ARFR1 + 4, 0x003ff000);
	/* ARFB table 11 for 11ac 24G 1SS */
	rtl_write_dword(rtlpriv, REG_ARFR2, 0x00000015);
	rtl_write_dword(rtlpriv, REG_ARFR2 + 4, 0x003ff000);
	/* ARFB table 12 for 11ac 24G 1SS */
	rtl_write_dword(rtlpriv, REG_ARFR3, 0x00000015);
	rtl_write_dword(rtlpriv, REG_ARFR3 + 4, 0xffcff000);
	/* 0x420[7] = 0 , enable retry AMPDU in new AMPD not singal MPDU. */
	rtl_write_word(rtlpriv, REG_FWHW_TXQ_CTRL, 0x1F00);
	rtl_write_byte(rtlpriv, REG_AMPDU_MAX_TIME, 0x70);

	/*Set retry limit*/
	rtl_write_word(rtlpriv, REG_RL, 0x0707);

	/* Set Data / Response auto rate fallack retry count*/
	rtl_write_dword(rtlpriv, REG_DARFRC, 0x01000000);
	rtl_write_dword(rtlpriv, REG_DARFRC + 4, 0x07060504);
	rtl_write_dword(rtlpriv, REG_RARFRC, 0x01000000);
	rtl_write_dword(rtlpriv, REG_RARFRC + 4, 0x07060504);

	rtlpci->reg_bcn_ctrl_val = 0x1d;
	rtl_write_byte(rtlpriv, REG_BCN_CTRL, rtlpci->reg_bcn_ctrl_val);

	/* TBTT prohibit hold time. Suggested by designer TimChen. */
	rtl_write_byte(rtlpriv, REG_TBTT_PROHIBIT + 1, 0xff);

	/* AGGR_BK_TIME Reg51A 0x16 */
	rtl_write_word(rtlpriv, REG_NAV_PROT_LEN, 0x0040);

	/*For Rx TP. Suggested by SD1 Richard. Added by tynli. 2010.04.12.*/
	rtl_write_dword(rtlpriv, REG_FAST_EDCA_CTRL, 0x03086666);

	rtl_write_byte(rtlpriv, REG_HT_SINGLE_AMPDU, 0x80);
	rtl_write_byte(rtlpriv, REG_RX_PKT_LIMIT, 0x20);
	rtl_write_word(rtlpriv, REG_MAX_AGGR_NUM, 0x1F1F);
}