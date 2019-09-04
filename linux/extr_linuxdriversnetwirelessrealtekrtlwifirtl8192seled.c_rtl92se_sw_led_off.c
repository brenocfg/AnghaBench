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
struct TYPE_2__ {int /*<<< orphan*/  led_opendrain; } ;
struct rtl_priv {TYPE_1__ ledctl; scalar_t__ max_fw_size; } ;
struct rtl_led {int ledpin; int ledon; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  COMP_LED ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  LEDCFG ; 
#define  LED_PIN_GPIO0 130 
#define  LED_PIN_LED0 129 
#define  LED_PIN_LED1 128 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int rtl_read_byte (struct rtl_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_write_byte (struct rtl_priv*,int /*<<< orphan*/ ,int) ; 

void rtl92se_sw_led_off(struct ieee80211_hw *hw, struct rtl_led *pled)
{
	struct rtl_priv *rtlpriv;
	u8 ledcfg;

	rtlpriv = rtl_priv(hw);
	if (!rtlpriv || rtlpriv->max_fw_size)
		return;
	RT_TRACE(rtlpriv, COMP_LED, DBG_LOUD, "LedAddr:%X ledpin=%d\n",
		 LEDCFG, pled->ledpin);

	ledcfg = rtl_read_byte(rtlpriv, LEDCFG);

	switch (pled->ledpin) {
	case LED_PIN_GPIO0:
		break;
	case LED_PIN_LED0:
		ledcfg &= 0xf0;
		if (rtlpriv->ledctl.led_opendrain)
			rtl_write_byte(rtlpriv, LEDCFG, (ledcfg | BIT(1)));
		else
			rtl_write_byte(rtlpriv, LEDCFG, (ledcfg | BIT(3)));
		break;
	case LED_PIN_LED1:
		ledcfg &= 0x0f;
		rtl_write_byte(rtlpriv, LEDCFG, (ledcfg | BIT(3)));
		break;
	default:
		pr_err("switch case %#x not processed\n",
		       pled->ledpin);
		break;
	}
	pled->ledon = false;
}