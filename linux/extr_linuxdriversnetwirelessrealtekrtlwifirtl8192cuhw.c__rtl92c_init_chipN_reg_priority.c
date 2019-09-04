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
 int /*<<< orphan*/  REG_TRXDMA_CTRL ; 
 int _TXDMA_BEQ_MAP (int) ; 
 int _TXDMA_BKQ_MAP (int) ; 
 int _TXDMA_HIQ_MAP (int) ; 
 int _TXDMA_MGQ_MAP (int) ; 
 int _TXDMA_VIQ_MAP (int) ; 
 int _TXDMA_VOQ_MAP (int) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int rtl_read_word (struct rtl_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_write_word (struct rtl_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void _rtl92c_init_chipN_reg_priority(struct ieee80211_hw *hw, u16 beQ,
					    u16 bkQ, u16 viQ, u16 voQ,
					    u16 mgtQ, u16 hiQ)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	u16 value16 = (rtl_read_word(rtlpriv, REG_TRXDMA_CTRL) & 0x7);

	value16 |= _TXDMA_BEQ_MAP(beQ) | _TXDMA_BKQ_MAP(bkQ) |
		   _TXDMA_VIQ_MAP(viQ) | _TXDMA_VOQ_MAP(voQ) |
		   _TXDMA_MGQ_MAP(mgtQ) | _TXDMA_HIQ_MAP(hiQ);
	rtl_write_word(rtlpriv,  REG_TRXDMA_CTRL, value16);
}