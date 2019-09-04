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
struct b43legacy_phy {int calibrated; scalar_t__ type; int rev; } ;
struct b43legacy_wldev {struct b43legacy_phy phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43legacy_MMIO_MACCTL ; 
 scalar_t__ B43legacy_PHYTYPE_G ; 
 int /*<<< orphan*/  B43legacy_TMSLOW_GMODE ; 
 int /*<<< orphan*/  b43legacy_phy_initg (struct b43legacy_wldev*) ; 
 int /*<<< orphan*/  b43legacy_read32 (struct b43legacy_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43legacy_wireless_core_reset (struct b43legacy_wldev*,int /*<<< orphan*/ ) ; 

void b43legacy_phy_calibrate(struct b43legacy_wldev *dev)
{
	struct b43legacy_phy *phy = &dev->phy;

	b43legacy_read32(dev, B43legacy_MMIO_MACCTL); /* Dummy read. */
	if (phy->calibrated)
		return;
	if (phy->type == B43legacy_PHYTYPE_G && phy->rev == 1) {
		b43legacy_wireless_core_reset(dev, 0);
		b43legacy_phy_initg(dev);
		b43legacy_wireless_core_reset(dev, B43legacy_TMSLOW_GMODE);
	}
	phy->calibrated = 1;
}