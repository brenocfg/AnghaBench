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
struct TYPE_2__ {int rev; } ;
struct b43_wldev {TYPE_1__ phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  b43_nphy_gain_ctl_workarounds_rev19 (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_nphy_gain_ctl_workarounds_rev1_2 (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_nphy_gain_ctl_workarounds_rev3 (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_nphy_gain_ctl_workarounds_rev7 (struct b43_wldev*) ; 

__attribute__((used)) static void b43_nphy_gain_ctl_workarounds(struct b43_wldev *dev)
{
	if (dev->phy.rev >= 19)
		b43_nphy_gain_ctl_workarounds_rev19(dev);
	else if (dev->phy.rev >= 7)
		b43_nphy_gain_ctl_workarounds_rev7(dev);
	else if (dev->phy.rev >= 3)
		b43_nphy_gain_ctl_workarounds_rev3(dev);
	else
		b43_nphy_gain_ctl_workarounds_rev1_2(dev);
}