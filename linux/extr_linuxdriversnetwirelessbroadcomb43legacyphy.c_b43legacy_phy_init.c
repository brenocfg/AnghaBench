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
struct b43legacy_phy {int type; int /*<<< orphan*/  rev; } ;
struct b43legacy_wldev {int /*<<< orphan*/  wl; struct b43legacy_phy phy; } ;

/* Variables and functions */
#define  B43legacy_PHYTYPE_B 129 
#define  B43legacy_PHYTYPE_G 128 
 int ENODEV ; 
 int /*<<< orphan*/  b43legacy_phy_initb2 (struct b43legacy_wldev*) ; 
 int /*<<< orphan*/  b43legacy_phy_initb4 (struct b43legacy_wldev*) ; 
 int /*<<< orphan*/  b43legacy_phy_initb5 (struct b43legacy_wldev*) ; 
 int /*<<< orphan*/  b43legacy_phy_initb6 (struct b43legacy_wldev*) ; 
 int /*<<< orphan*/  b43legacy_phy_initg (struct b43legacy_wldev*) ; 
 int /*<<< orphan*/  b43legacyerr (int /*<<< orphan*/ ,char*) ; 

int b43legacy_phy_init(struct b43legacy_wldev *dev)
{
	struct b43legacy_phy *phy = &dev->phy;
	int err = -ENODEV;

	switch (phy->type) {
	case B43legacy_PHYTYPE_B:
		switch (phy->rev) {
		case 2:
			b43legacy_phy_initb2(dev);
			err = 0;
			break;
		case 4:
			b43legacy_phy_initb4(dev);
			err = 0;
			break;
		case 5:
			b43legacy_phy_initb5(dev);
			err = 0;
			break;
		case 6:
			b43legacy_phy_initb6(dev);
			err = 0;
			break;
		}
		break;
	case B43legacy_PHYTYPE_G:
		b43legacy_phy_initg(dev);
		err = 0;
		break;
	}
	if (err)
		b43legacyerr(dev->wl, "Unknown PHYTYPE found\n");

	return err;
}