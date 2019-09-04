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
struct TYPE_2__ {int /*<<< orphan*/  sw_led1; int /*<<< orphan*/  sw_led0; } ;
struct rtl_priv {TYPE_1__ ledctl; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LED_PIN_LED0 ; 
 int /*<<< orphan*/  LED_PIN_LED1 ; 
 int /*<<< orphan*/  _rtl92se_init_led (struct ieee80211_hw*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

void rtl92se_init_sw_leds(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);

	_rtl92se_init_led(hw, &rtlpriv->ledctl.sw_led0, LED_PIN_LED0);
	_rtl92se_init_led(hw, &rtlpriv->ledctl.sw_led1, LED_PIN_LED1);
}