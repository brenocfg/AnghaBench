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
typedef  scalar_t__ u32 ;
struct rtl_priv {int dummy; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int rtl_read_byte (struct rtl_priv*,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static	void _rtl92s_phy_check_ephy_switchready(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	u32	delay = 100;
	u8	regu1;

	regu1 = rtl_read_byte(rtlpriv, 0x554);
	while ((regu1 & BIT(5)) && (delay > 0)) {
		regu1 = rtl_read_byte(rtlpriv, 0x554);
		delay--;
		/* We delay only 50us to prevent
		 * being scheduled out. */
		udelay(50);
	}
}