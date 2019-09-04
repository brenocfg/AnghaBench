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
struct b43legacy_wldev {int /*<<< orphan*/  wl; TYPE_2__* dev; } ;
struct TYPE_3__ {int revision; } ;
struct TYPE_4__ {TYPE_1__ id; } ;

/* Variables and functions */
 int /*<<< orphan*/  NL80211_IFTYPE_AP ; 
 int /*<<< orphan*/  b43legacy_is_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43legacy_mac_enable (struct b43legacy_wldev*) ; 
 int /*<<< orphan*/  b43legacy_power_saving_ctl_bits (struct b43legacy_wldev*,int,int) ; 

void b43legacy_phy_unlock(struct b43legacy_wldev *dev)
{
#if B43legacy_DEBUG
	B43legacy_WARN_ON(!dev->phy.phy_locked);
	dev->phy.phy_locked = 0;
#endif

	if (dev->dev->id.revision < 3) {
		b43legacy_mac_enable(dev);
	} else {
		if (!b43legacy_is_mode(dev->wl, NL80211_IFTYPE_AP))
			b43legacy_power_saving_ctl_bits(dev, -1, -1);
	}
}