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
 int ERFOFF ; 
 int ERFON ; 
 int GPIOMUX_EN ; 
 int GPIOSEL_GPIO ; 
 int /*<<< orphan*/  GPIO_IN_SE ; 
 int /*<<< orphan*/  GPIO_IO_SEL ; 
 int HAL_8192S_HW_GPIO_OFF_BIT ; 
 int HAL_8192S_HW_GPIO_OFF_MASK ; 
 int /*<<< orphan*/  MAC_PINMUX_CFG ; 
 int /*<<< orphan*/  mdelay (int) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int rtl_read_byte (struct rtl_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_write_byte (struct rtl_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u8 _rtl92se_rf_onoff_detect(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	u8 u1tmp;
	u8 retval = ERFON;

	/* The following config GPIO function */
	rtl_write_byte(rtlpriv, MAC_PINMUX_CFG, (GPIOMUX_EN | GPIOSEL_GPIO));
	u1tmp = rtl_read_byte(rtlpriv, GPIO_IO_SEL);

	/* config GPIO3 to input */
	u1tmp &= HAL_8192S_HW_GPIO_OFF_MASK;
	rtl_write_byte(rtlpriv, GPIO_IO_SEL, u1tmp);

	/* On some of the platform, driver cannot read correct
	 * value without delay between Write_GPIO_SEL and Read_GPIO_IN */
	mdelay(10);

	/* check GPIO3 */
	u1tmp = rtl_read_byte(rtlpriv, GPIO_IN_SE);
	retval = (u1tmp & HAL_8192S_HW_GPIO_OFF_BIT) ? ERFON : ERFOFF;

	return retval;
}