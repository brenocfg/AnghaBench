#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int macphymode; } ;
struct rtl_priv {TYPE_1__ rtlhal; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
#define  DUALMAC_DUALPHY 130 
#define  DUALMAC_SINGLEPHY 129 
 int /*<<< orphan*/  REG_DMC ; 
 int /*<<< orphan*/  REG_RX_PKT_LIMIT ; 
 int /*<<< orphan*/  REG_TRXFF_BNDY ; 
#define  SINGLEMAC_SINGLEPHY 128 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_write_byte (struct rtl_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtl_write_word (struct rtl_priv*,int /*<<< orphan*/ ,int) ; 

void rtl92d_phy_config_maccoexist_rfpage(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);

	switch (rtlpriv->rtlhal.macphymode) {
	case DUALMAC_DUALPHY:
		rtl_write_byte(rtlpriv, REG_DMC, 0x0);
		rtl_write_byte(rtlpriv, REG_RX_PKT_LIMIT, 0x08);
		rtl_write_word(rtlpriv, REG_TRXFF_BNDY + 2, 0x13ff);
		break;
	case DUALMAC_SINGLEPHY:
		rtl_write_byte(rtlpriv, REG_DMC, 0xf8);
		rtl_write_byte(rtlpriv, REG_RX_PKT_LIMIT, 0x08);
		rtl_write_word(rtlpriv, REG_TRXFF_BNDY + 2, 0x13ff);
		break;
	case SINGLEMAC_SINGLEPHY:
		rtl_write_byte(rtlpriv, REG_DMC, 0x0);
		rtl_write_byte(rtlpriv, REG_RX_PKT_LIMIT, 0x10);
		rtl_write_word(rtlpriv, (REG_TRXFF_BNDY + 2), 0x27FF);
		break;
	default:
		break;
	}
}