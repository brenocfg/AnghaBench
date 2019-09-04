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
typedef  int u16 ;
struct rtl_priv {int dummy; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int DIS_EDCA_CNT_DWN ; 
 int /*<<< orphan*/  REG_AGGR_BREAK_TIME ; 
 int /*<<< orphan*/  REG_ATIMWND ; 
 int /*<<< orphan*/  REG_BAR_MODE_CTRL ; 
 int /*<<< orphan*/  REG_BCNDMATIM ; 
 int /*<<< orphan*/  REG_EDCA_BE_PARAM ; 
 int /*<<< orphan*/  REG_EDCA_BK_PARAM ; 
 int /*<<< orphan*/  REG_EDCA_VI_PARAM ; 
 int /*<<< orphan*/  REG_EDCA_VO_PARAM ; 
 int /*<<< orphan*/  REG_NAV_PROT_LEN ; 
 int /*<<< orphan*/  REG_PIFS ; 
 int /*<<< orphan*/  REG_PROT_MODE_CTRL ; 
 int /*<<< orphan*/  REG_RD_CTRL ; 
 int /*<<< orphan*/  REG_SIFS_CCK ; 
 int /*<<< orphan*/  REG_SIFS_OFDM ; 
 int /*<<< orphan*/  rtl92c_set_cck_sifs (struct ieee80211_hw*,int,int) ; 
 int /*<<< orphan*/  rtl92c_set_ofdm_sifs (struct ieee80211_hw*,int,int) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int rtl_read_word (struct rtl_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_write_byte (struct rtl_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtl_write_dword (struct rtl_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtl_write_word (struct rtl_priv*,int /*<<< orphan*/ ,int) ; 

void rtl92c_init_edca(struct ieee80211_hw *hw)
{
	u16 value16;
	struct rtl_priv *rtlpriv = rtl_priv(hw);

	/* disable EDCCA count down, to reduce collison and retry */
	value16 = rtl_read_word(rtlpriv, REG_RD_CTRL);
	value16 |= DIS_EDCA_CNT_DWN;
	rtl_write_word(rtlpriv, REG_RD_CTRL, value16);
	/* Update SIFS timing.  ??????????
	 * pHalData->SifsTime = 0x0e0e0a0a; */
	rtl92c_set_cck_sifs(hw, 0xa, 0xa);
	rtl92c_set_ofdm_sifs(hw, 0xe, 0xe);
	/* Set CCK/OFDM SIFS to be 10us. */
	rtl_write_word(rtlpriv, REG_SIFS_CCK, 0x0a0a);
	rtl_write_word(rtlpriv, REG_SIFS_OFDM, 0x1010);
	rtl_write_word(rtlpriv, REG_PROT_MODE_CTRL, 0x0204);
	rtl_write_dword(rtlpriv, REG_BAR_MODE_CTRL, 0x014004);
	/* TXOP */
	rtl_write_dword(rtlpriv, REG_EDCA_BE_PARAM, 0x005EA42B);
	rtl_write_dword(rtlpriv, REG_EDCA_BK_PARAM, 0x0000A44F);
	rtl_write_dword(rtlpriv, REG_EDCA_VI_PARAM, 0x005EA324);
	rtl_write_dword(rtlpriv, REG_EDCA_VO_PARAM, 0x002FA226);
	/* PIFS */
	rtl_write_byte(rtlpriv, REG_PIFS, 0x1C);
	/* AGGR BREAK TIME Register */
	rtl_write_byte(rtlpriv, REG_AGGR_BREAK_TIME, 0x16);
	rtl_write_word(rtlpriv, REG_NAV_PROT_LEN, 0x0040);
	rtl_write_byte(rtlpriv, REG_BCNDMATIM, 0x02);
	rtl_write_byte(rtlpriv, REG_ATIMWND, 0x02);
}