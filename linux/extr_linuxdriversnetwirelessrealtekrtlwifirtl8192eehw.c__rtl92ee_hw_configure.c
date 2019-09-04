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
 int REG_ACKTO ; 
 int REG_AGGR_BREAK_TIME ; 
 scalar_t__ REG_ARFR0 ; 
 scalar_t__ REG_ARFR1 ; 
 int REG_ATIMWND ; 
 scalar_t__ REG_BAR_MODE_CTRL ; 
 int REG_BCN_CTRL ; 
 int REG_BCN_CTRL_1 ; 
 int REG_BCN_MAX_ERR ; 
 scalar_t__ REG_DARFRC ; 
 scalar_t__ REG_FAST_EDCA_CTRL ; 
 int /*<<< orphan*/  REG_FWHW_TXQ_CTRL ; 
 int /*<<< orphan*/  REG_MAC_SPEC_SIFS ; 
 scalar_t__ REG_MAR ; 
 int /*<<< orphan*/  REG_MAX_AGGR_NUM ; 
 int /*<<< orphan*/  REG_NAV_PROT_LEN ; 
 int REG_PIFS ; 
 int /*<<< orphan*/  REG_PROT_MODE_CTRL ; 
 scalar_t__ REG_RARFRC ; 
 int /*<<< orphan*/  REG_RETRY_LIMIT ; 
 scalar_t__ REG_RRSR ; 
 int REG_RX_PKT_LIMIT ; 
 int /*<<< orphan*/  REG_SIFS_CTX ; 
 int /*<<< orphan*/  REG_SIFS_TRX ; 
 int REG_SLOT ; 
 int /*<<< orphan*/  REG_SPEC_SIFS ; 
 int REG_TBTT_PROHIBIT ; 
 struct rtl_pci* rtl_pcidev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_pcipriv (struct ieee80211_hw*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_write_byte (struct rtl_priv*,int,int) ; 
 int /*<<< orphan*/  rtl_write_dword (struct rtl_priv*,scalar_t__,int) ; 
 int /*<<< orphan*/  rtl_write_word (struct rtl_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void _rtl92ee_hw_configure(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	u32 reg_rrsr;

	reg_rrsr = RATE_ALL_CCK | RATE_ALL_OFDM_AG;
	/* Init value for RRSR. */
	rtl_write_dword(rtlpriv, REG_RRSR, reg_rrsr);

	/* ARFB table 9 for 11ac 5G 2SS */
	rtl_write_dword(rtlpriv, REG_ARFR0, 0x00000010);
	rtl_write_dword(rtlpriv, REG_ARFR0 + 4, 0x3e0ff000);

	/* ARFB table 10 for 11ac 5G 1SS */
	rtl_write_dword(rtlpriv, REG_ARFR1, 0x00000010);
	rtl_write_dword(rtlpriv, REG_ARFR1 + 4, 0x000ff000);

	/* Set SLOT time */
	rtl_write_byte(rtlpriv, REG_SLOT, 0x09);

	/* CF-End setting. */
	rtl_write_word(rtlpriv, REG_FWHW_TXQ_CTRL, 0x1F80);

	/* Set retry limit */
	rtl_write_word(rtlpriv, REG_RETRY_LIMIT, 0x0707);

	/* BAR settings */
	rtl_write_dword(rtlpriv, REG_BAR_MODE_CTRL, 0x0201ffff);

	/* Set Data / Response auto rate fallack retry count */
	rtl_write_dword(rtlpriv, REG_DARFRC, 0x01000000);
	rtl_write_dword(rtlpriv, REG_DARFRC + 4, 0x07060504);
	rtl_write_dword(rtlpriv, REG_RARFRC, 0x01000000);
	rtl_write_dword(rtlpriv, REG_RARFRC + 4, 0x07060504);

	/* Beacon related, for rate adaptive */
	rtl_write_byte(rtlpriv, REG_ATIMWND, 0x2);
	rtl_write_byte(rtlpriv, REG_BCN_MAX_ERR, 0xff);

	rtlpci->reg_bcn_ctrl_val = 0x1d;
	rtl_write_byte(rtlpriv, REG_BCN_CTRL, rtlpci->reg_bcn_ctrl_val);

	/* Marked out by Bruce, 2010-09-09.
	 * This register is configured for the 2nd Beacon (multiple BSSID).
	 * We shall disable this register if we only support 1 BSSID.
	 * vivi guess 92d also need this, also 92d now doesnot set this reg
	 */
	rtl_write_byte(rtlpriv, REG_BCN_CTRL_1, 0);

	/* TBTT prohibit hold time. Suggested by designer TimChen. */
	rtl_write_byte(rtlpriv, REG_TBTT_PROHIBIT + 1, 0xff); /* 8 ms */

	rtl_write_byte(rtlpriv, REG_PIFS, 0);
	rtl_write_byte(rtlpriv, REG_AGGR_BREAK_TIME, 0x16);

	rtl_write_word(rtlpriv, REG_NAV_PROT_LEN, 0x0040);
	rtl_write_word(rtlpriv, REG_PROT_MODE_CTRL, 0x08ff);

	/* For Rx TP. Suggested by SD1 Richard. Added by tynli. 2010.04.12.*/
	rtl_write_dword(rtlpriv, REG_FAST_EDCA_CTRL, 0x03086666);

	/* ACKTO for IOT issue. */
	rtl_write_byte(rtlpriv, REG_ACKTO, 0x40);

	/* Set Spec SIFS (used in NAV) */
	rtl_write_word(rtlpriv, REG_SPEC_SIFS, 0x100a);
	rtl_write_word(rtlpriv, REG_MAC_SPEC_SIFS, 0x100a);

	/* Set SIFS for CCK */
	rtl_write_word(rtlpriv, REG_SIFS_CTX, 0x100a);

	/* Set SIFS for OFDM */
	rtl_write_word(rtlpriv, REG_SIFS_TRX, 0x100a);

	/* Note Data sheet don't define */
	rtl_write_byte(rtlpriv, 0x4C7, 0x80);

	rtl_write_byte(rtlpriv, REG_RX_PKT_LIMIT, 0x20);

	rtl_write_word(rtlpriv, REG_MAX_AGGR_NUM, 0x1717);

	/* Set Multicast Address. 2009.01.07. by tynli. */
	rtl_write_dword(rtlpriv, REG_MAR, 0xffffffff);
	rtl_write_dword(rtlpriv, REG_MAR + 4, 0xffffffff);
}