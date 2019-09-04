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
struct b43_wldev {int /*<<< orphan*/  wl; TYPE_1__* dev; } ;
struct TYPE_2__ {int core_rev; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43_WARN_ON (int) ; 
 int /*<<< orphan*/  NL80211_IFTYPE_AP ; 
 int /*<<< orphan*/  b43_is_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_power_saving_ctl_bits (struct b43_wldev*,int /*<<< orphan*/ ) ; 

void b43_phy_unlock(struct b43_wldev *dev)
{
#if B43_DEBUG
	B43_WARN_ON(!dev->phy.phy_locked);
	dev->phy.phy_locked = false;
#endif
	B43_WARN_ON(dev->dev->core_rev < 3);

	if (!b43_is_mode(dev->wl, NL80211_IFTYPE_AP))
		b43_power_saving_ctl_bits(dev, 0);
}