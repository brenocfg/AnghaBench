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
typedef  int /*<<< orphan*/  u8 ;
struct ieee80211_hw {int /*<<< orphan*/  wiphy; } ;
struct TYPE_3__ {int /*<<< orphan*/  radio_on; } ;
struct b43legacy_wldev {TYPE_2__* wl; int /*<<< orphan*/  led_assoc; TYPE_1__ phy; int /*<<< orphan*/  led_radio; int /*<<< orphan*/  led_rx; int /*<<< orphan*/  led_tx; } ;
typedef  int /*<<< orphan*/  name ;
typedef  enum b43legacy_led_behaviour { ____Placeholder_b43legacy_led_behaviour } b43legacy_led_behaviour ;
struct TYPE_4__ {struct ieee80211_hw* hw; } ;

/* Variables and functions */
#define  B43legacy_LED_ACTIVITY 139 
#define  B43legacy_LED_APTRANSFER 138 
#define  B43legacy_LED_ASSOC 137 
#define  B43legacy_LED_INACTIVE 136 
 int /*<<< orphan*/  B43legacy_LED_MAX_NAME_LEN ; 
#define  B43legacy_LED_MODE_BG 135 
#define  B43legacy_LED_OFF 134 
#define  B43legacy_LED_ON 133 
#define  B43legacy_LED_RADIO_A 132 
#define  B43legacy_LED_RADIO_ALL 131 
#define  B43legacy_LED_RADIO_B 130 
#define  B43legacy_LED_TRANSFER 129 
#define  B43legacy_LED_WEIRD 128 
 int /*<<< orphan*/  b43legacy_is_hw_radio_enabled (struct b43legacy_wldev*) ; 
 int /*<<< orphan*/  b43legacy_led_turn_off (struct b43legacy_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43legacy_led_turn_on (struct b43legacy_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43legacy_register_led (struct b43legacy_wldev*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43legacywarn (TYPE_2__*,char*,int) ; 
 int /*<<< orphan*/  ieee80211_get_assoc_led_name (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  ieee80211_get_radio_led_name (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  ieee80211_get_rx_led_name (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  ieee80211_get_tx_led_name (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 char* wiphy_name (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void b43legacy_map_led(struct b43legacy_wldev *dev,
			u8 led_index,
			enum b43legacy_led_behaviour behaviour,
			bool activelow)
{
	struct ieee80211_hw *hw = dev->wl->hw;
	char name[B43legacy_LED_MAX_NAME_LEN + 1];

	/* Map the b43 specific LED behaviour value to the
	 * generic LED triggers. */
	switch (behaviour) {
	case B43legacy_LED_INACTIVE:
		break;
	case B43legacy_LED_OFF:
		b43legacy_led_turn_off(dev, led_index, activelow);
		break;
	case B43legacy_LED_ON:
		b43legacy_led_turn_on(dev, led_index, activelow);
		break;
	case B43legacy_LED_ACTIVITY:
	case B43legacy_LED_TRANSFER:
	case B43legacy_LED_APTRANSFER:
		snprintf(name, sizeof(name),
			 "b43legacy-%s::tx", wiphy_name(hw->wiphy));
		b43legacy_register_led(dev, &dev->led_tx, name,
				 ieee80211_get_tx_led_name(hw),
				 led_index, activelow);
		snprintf(name, sizeof(name),
			 "b43legacy-%s::rx", wiphy_name(hw->wiphy));
		b43legacy_register_led(dev, &dev->led_rx, name,
				 ieee80211_get_rx_led_name(hw),
				 led_index, activelow);
		break;
	case B43legacy_LED_RADIO_ALL:
	case B43legacy_LED_RADIO_A:
	case B43legacy_LED_RADIO_B:
	case B43legacy_LED_MODE_BG:
		snprintf(name, sizeof(name),
			 "b43legacy-%s::radio", wiphy_name(hw->wiphy));
		b43legacy_register_led(dev, &dev->led_radio, name,
				 ieee80211_get_radio_led_name(hw),
				 led_index, activelow);
		/* Sync the RF-kill LED state with radio and switch states. */
		if (dev->phy.radio_on && b43legacy_is_hw_radio_enabled(dev))
			b43legacy_led_turn_on(dev, led_index, activelow);
		break;
	case B43legacy_LED_WEIRD:
	case B43legacy_LED_ASSOC:
		snprintf(name, sizeof(name),
			 "b43legacy-%s::assoc", wiphy_name(hw->wiphy));
		b43legacy_register_led(dev, &dev->led_assoc, name,
				 ieee80211_get_assoc_led_name(hw),
				 led_index, activelow);
		break;
	default:
		b43legacywarn(dev->wl, "LEDs: Unknown behaviour 0x%02X\n",
			behaviour);
		break;
	}
}