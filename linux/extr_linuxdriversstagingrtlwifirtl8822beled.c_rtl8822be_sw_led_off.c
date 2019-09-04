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
struct rtl_priv {int dummy; } ;
struct rtl_led {int ledpin; int ledon; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_ERR ; 
 int /*<<< orphan*/  COMP_LED ; 
 int /*<<< orphan*/  DBG_LOUD ; 
#define  LED_PIN_GPIO0 130 
#define  LED_PIN_LED0 129 
#define  LED_PIN_LED1 128 
 int /*<<< orphan*/  REG_LEDCFG2_8822B ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

void rtl8822be_sw_led_off(struct ieee80211_hw *hw, struct rtl_led *pled)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);

	RT_TRACE(rtlpriv, COMP_LED, DBG_LOUD, "LedAddr:%X ledpin=%d\n",
		 REG_LEDCFG2_8822B, pled->ledpin);

	switch (pled->ledpin) {
	case LED_PIN_GPIO0:
		break;
	case LED_PIN_LED0:
		break;
	case LED_PIN_LED1:

		break;
	default:
		RT_TRACE(rtlpriv, COMP_ERR, DBG_LOUD,
			 "switch case not process\n");
		break;
	}
	pled->ledon = false;
}