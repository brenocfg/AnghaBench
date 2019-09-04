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
typedef  int u8 ;
struct TYPE_2__ {int eeprom_did; } ;
struct rtl_priv {TYPE_1__ efuse; } ;
struct rtl_led {int ledpin; int ledon; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  COMP_LED ; 
 int /*<<< orphan*/  DBG_LOUD ; 
#define  LED_PIN_GPIO0 130 
#define  LED_PIN_LED0 129 
#define  LED_PIN_LED1 128 
 int /*<<< orphan*/  REG_LEDCFG1 ; 
 int /*<<< orphan*/  REG_LEDCFG2 ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int rtl_read_byte (struct rtl_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_write_byte (struct rtl_priv*,int /*<<< orphan*/ ,int) ; 

void rtl92de_sw_led_on(struct ieee80211_hw *hw, struct rtl_led *pled)
{
	u8 ledcfg;
	struct rtl_priv *rtlpriv = rtl_priv(hw);

	RT_TRACE(rtlpriv, COMP_LED, DBG_LOUD, "LedAddr:%X ledpin=%d\n",
		 REG_LEDCFG2, pled->ledpin);

	switch (pled->ledpin) {
	case LED_PIN_GPIO0:
		break;
	case LED_PIN_LED0:
		ledcfg = rtl_read_byte(rtlpriv, REG_LEDCFG2);

		if ((rtlpriv->efuse.eeprom_did == 0x8176) ||
			(rtlpriv->efuse.eeprom_did == 0x8193))
			/* BIT7 of REG_LEDCFG2 should be set to
			 * make sure we could emit the led2. */
			rtl_write_byte(rtlpriv, REG_LEDCFG2, (ledcfg & 0xf0) |
				       BIT(7) | BIT(5) | BIT(6));
		else
			rtl_write_byte(rtlpriv, REG_LEDCFG2, (ledcfg & 0xf0) |
				       BIT(7) | BIT(5));
		break;
	case LED_PIN_LED1:
		ledcfg = rtl_read_byte(rtlpriv, REG_LEDCFG1);

		rtl_write_byte(rtlpriv, REG_LEDCFG2, (ledcfg & 0x0f) | BIT(5));
		break;
	default:
		pr_err("switch case %#x not processed\n",
		       pled->ledpin);
		break;
	}
	pled->ledon = true;
}