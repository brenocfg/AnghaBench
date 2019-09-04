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
struct rtl_priv {int dummy; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 scalar_t__ SYS_CLKR ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int rtl_read_byte (struct rtl_priv*,scalar_t__) ; 
 int /*<<< orphan*/  rtl_write_byte (struct rtl_priv*,scalar_t__,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static u8 _rtl92se_halset_sysclk(struct ieee80211_hw *hw, u8 data)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	u8 waitcount = 100;
	bool bresult = false;
	u8 tmpvalue;

	rtl_write_byte(rtlpriv, SYS_CLKR + 1, data);

	/* Wait the MAC synchronized. */
	udelay(400);

	/* Check if it is set ready. */
	tmpvalue = rtl_read_byte(rtlpriv, SYS_CLKR + 1);
	bresult = ((tmpvalue & BIT(7)) == (data & BIT(7)));

	if ((data & (BIT(6) | BIT(7))) == false) {
		waitcount = 100;
		tmpvalue = 0;

		while (1) {
			waitcount--;

			tmpvalue = rtl_read_byte(rtlpriv, SYS_CLKR + 1);
			if ((tmpvalue & BIT(6)))
				break;

			pr_err("wait for BIT(6) return value %x\n", tmpvalue);
			if (waitcount == 0)
				break;

			udelay(10);
		}

		if (waitcount == 0)
			bresult = false;
		else
			bresult = true;
	}

	return bresult;
}