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
typedef  int u8 ;
struct rtl_hal {int during_mac0init_radiob; int during_mac1init_radioa; } ;
struct rtl_priv {struct rtl_hal rtlhal; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  COMP_INIT ; 
 int /*<<< orphan*/  COMP_RF ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int MAC0_ON ; 
 int MAC1_ON ; 
 int REG_MAC0 ; 
 int REG_MAC1 ; 
 int /*<<< orphan*/  REG_SYS_ISO_CTRL ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int rtl92de_read_dword_dbi (struct ieee80211_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtl92de_write_dword_dbi (struct ieee80211_hw*,int /*<<< orphan*/ ,int,int) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int rtl_read_byte (struct rtl_priv*,int) ; 

bool rtl92d_phy_enable_anotherphy(struct ieee80211_hw *hw, bool bmac0)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_hal *rtlhal = &(rtlpriv->rtlhal);
	u8 u1btmp;
	u8 direct = bmac0 ? BIT(3) | BIT(2) : BIT(3);
	u8 mac_reg = bmac0 ? REG_MAC1 : REG_MAC0;
	u8 mac_on_bit = bmac0 ? MAC1_ON : MAC0_ON;
	bool bresult = true; /* true: need to enable BB/RF power */

	rtlhal->during_mac0init_radiob = false;
	rtlhal->during_mac1init_radioa = false;
	RT_TRACE(rtlpriv, COMP_RF, DBG_LOUD, "===>\n");
	/* MAC0 Need PHY1 load radio_b.txt . Driver use DBI to write. */
	u1btmp = rtl_read_byte(rtlpriv, mac_reg);
	if (!(u1btmp & mac_on_bit)) {
		RT_TRACE(rtlpriv, COMP_INIT, DBG_LOUD, "enable BB & RF\n");
		/* Enable BB and RF power */
		rtl92de_write_dword_dbi(hw, REG_SYS_ISO_CTRL,
			rtl92de_read_dword_dbi(hw, REG_SYS_ISO_CTRL, direct) |
				BIT(29) | BIT(16) | BIT(17), direct);
	} else {
		/* We think if MAC1 is ON,then radio_a.txt
		 * and radio_b.txt has been load. */
		bresult = false;
	}
	RT_TRACE(rtlpriv, COMP_RF, DBG_LOUD, "<===\n");
	return bresult;

}