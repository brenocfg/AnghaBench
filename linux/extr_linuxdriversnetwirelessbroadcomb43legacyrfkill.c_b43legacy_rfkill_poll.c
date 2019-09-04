#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ssb_bus {int dummy; } ;
struct ieee80211_hw {int /*<<< orphan*/  wiphy; } ;
struct TYPE_4__ {int radio_on; } ;
struct b43legacy_wldev {int radio_hw_enable; TYPE_2__* dev; TYPE_1__ phy; } ;
struct b43legacy_wl {int /*<<< orphan*/  mutex; struct b43legacy_wldev* current_dev; } ;
struct TYPE_5__ {struct ssb_bus* bus; } ;

/* Variables and functions */
 scalar_t__ B43legacy_STAT_INITIALIZED ; 
 int b43legacy_is_hw_radio_enabled (struct b43legacy_wldev*) ; 
 int /*<<< orphan*/  b43legacy_radio_turn_off (struct b43legacy_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43legacy_radio_turn_on (struct b43legacy_wldev*) ; 
 scalar_t__ b43legacy_status (struct b43legacy_wldev*) ; 
 int /*<<< orphan*/  b43legacyinfo (struct b43legacy_wl*,char*,char*) ; 
 struct b43legacy_wl* hw_to_b43legacy_wl (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ssb_bus_may_powerdown (struct ssb_bus*) ; 
 scalar_t__ ssb_bus_powerup (struct ssb_bus*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssb_device_disable (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssb_device_enable (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wiphy_rfkill_set_hw_state (int /*<<< orphan*/ ,int) ; 

void b43legacy_rfkill_poll(struct ieee80211_hw *hw)
{
	struct b43legacy_wl *wl = hw_to_b43legacy_wl(hw);
	struct b43legacy_wldev *dev = wl->current_dev;
	struct ssb_bus *bus = dev->dev->bus;
	bool enabled;
	bool brought_up = false;

	mutex_lock(&wl->mutex);
	if (unlikely(b43legacy_status(dev) < B43legacy_STAT_INITIALIZED)) {
		if (ssb_bus_powerup(bus, 0)) {
			mutex_unlock(&wl->mutex);
			return;
		}
		ssb_device_enable(dev->dev, 0);
		brought_up = true;
	}

	enabled = b43legacy_is_hw_radio_enabled(dev);

	if (unlikely(enabled != dev->radio_hw_enable)) {
		dev->radio_hw_enable = enabled;
		b43legacyinfo(wl, "Radio hardware status changed to %s\n",
			enabled ? "ENABLED" : "DISABLED");
		wiphy_rfkill_set_hw_state(hw->wiphy, !enabled);
		if (enabled != dev->phy.radio_on) {
			if (enabled)
				b43legacy_radio_turn_on(dev);
			else
				b43legacy_radio_turn_off(dev, 0);
		}
	}

	if (brought_up) {
		ssb_device_disable(dev->dev, 0);
		ssb_bus_may_powerdown(bus);
	}

	mutex_unlock(&wl->mutex);
}