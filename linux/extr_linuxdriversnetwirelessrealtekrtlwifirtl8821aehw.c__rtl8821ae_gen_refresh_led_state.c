#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rtl_ps_ctl {scalar_t__ rfoff_reason; } ;
struct TYPE_3__ {scalar_t__ up_first_time; } ;
struct rtl_led {int dummy; } ;
struct TYPE_4__ {struct rtl_led sw_led0; } ;
struct rtl_priv {TYPE_1__ rtlhal; TYPE_2__ ledctl; } ;
struct rtl_hal {scalar_t__ hw_type; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ HARDWARE_TYPE_RTL8812AE ; 
 scalar_t__ RF_CHANGE_BY_INIT ; 
 scalar_t__ RF_CHANGE_BY_IPS ; 
 int /*<<< orphan*/  rtl8812ae_sw_led_off (struct ieee80211_hw*,struct rtl_led*) ; 
 int /*<<< orphan*/  rtl8812ae_sw_led_on (struct ieee80211_hw*,struct rtl_led*) ; 
 int /*<<< orphan*/  rtl8821ae_sw_led_off (struct ieee80211_hw*,struct rtl_led*) ; 
 int /*<<< orphan*/  rtl8821ae_sw_led_on (struct ieee80211_hw*,struct rtl_led*) ; 
 struct rtl_hal* rtl_hal (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 struct rtl_ps_ctl* rtl_psc (struct rtl_priv*) ; 

__attribute__((used)) static void _rtl8821ae_gen_refresh_led_state(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	struct rtl_led *pled0 = &rtlpriv->ledctl.sw_led0;
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));

	if (rtlpriv->rtlhal.up_first_time)
		return;

	if (ppsc->rfoff_reason == RF_CHANGE_BY_IPS)
		if (rtlhal->hw_type == HARDWARE_TYPE_RTL8812AE)
			rtl8812ae_sw_led_on(hw, pled0);
		else
			rtl8821ae_sw_led_on(hw, pled0);
	else if (ppsc->rfoff_reason == RF_CHANGE_BY_INIT)
		if (rtlhal->hw_type == HARDWARE_TYPE_RTL8812AE)
			rtl8812ae_sw_led_on(hw, pled0);
		else
			rtl8821ae_sw_led_on(hw, pled0);
	else
		if (rtlhal->hw_type == HARDWARE_TYPE_RTL8812AE)
			rtl8812ae_sw_led_off(hw, pled0);
		else
			rtl8821ae_sw_led_off(hw, pled0);
}