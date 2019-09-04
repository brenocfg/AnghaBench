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
struct rtl_led {int dummy; } ;
struct TYPE_2__ {struct rtl_led sw_led0; } ;
struct rtl_pci_priv {TYPE_1__ ledctl; } ;
struct ieee80211_hw {int dummy; } ;
typedef  enum led_ctl_mode { ____Placeholder_led_ctl_mode } led_ctl_mode ;

/* Variables and functions */
#define  LED_CTL_LINK 131 
#define  LED_CTL_NO_LINK 130 
#define  LED_CTL_POWER_OFF 129 
#define  LED_CTL_POWER_ON 128 
 int /*<<< orphan*/  rtl8822be_sw_led_off (struct ieee80211_hw*,struct rtl_led*) ; 
 int /*<<< orphan*/  rtl8822be_sw_led_on (struct ieee80211_hw*,struct rtl_led*) ; 
 struct rtl_pci_priv* rtl_pcipriv (struct ieee80211_hw*) ; 

__attribute__((used)) static void _rtl8822be_sw_led_control(struct ieee80211_hw *hw,
				      enum led_ctl_mode ledaction)
{
	struct rtl_pci_priv *pcipriv = rtl_pcipriv(hw);
	struct rtl_led *led0 = &pcipriv->ledctl.sw_led0;

	switch (ledaction) {
	case LED_CTL_POWER_ON:
	case LED_CTL_LINK:
	case LED_CTL_NO_LINK:
		rtl8822be_sw_led_on(hw, led0);
		break;
	case LED_CTL_POWER_OFF:
		rtl8822be_sw_led_off(hw, led0);
		break;
	default:
		break;
	}
}