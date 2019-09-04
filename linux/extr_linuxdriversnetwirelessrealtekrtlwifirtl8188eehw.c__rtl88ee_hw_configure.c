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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct rtl_priv {int dummy; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BW_OPMODE_20MHZ ; 
 int RATE_ALL_CCK ; 
 int RATE_ALL_OFDM_1SS ; 
 int RATE_ALL_OFDM_2SS ; 
 int RATE_ALL_OFDM_AG ; 
 int /*<<< orphan*/  REG_HWSEQ_CTRL ; 
 int /*<<< orphan*/  REG_RRSR ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_write_byte (struct rtl_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtl_write_dword (struct rtl_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void _rtl88ee_hw_configure(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	u8 reg_bw_opmode;
	u32 reg_ratr, reg_prsr;

	reg_bw_opmode = BW_OPMODE_20MHZ;
	reg_ratr = RATE_ALL_CCK | RATE_ALL_OFDM_AG |
	    RATE_ALL_OFDM_1SS | RATE_ALL_OFDM_2SS;
	reg_prsr = RATE_ALL_CCK | RATE_ALL_OFDM_AG;

	rtl_write_dword(rtlpriv, REG_RRSR, reg_prsr);
	rtl_write_byte(rtlpriv, REG_HWSEQ_CTRL, 0xFF);
}