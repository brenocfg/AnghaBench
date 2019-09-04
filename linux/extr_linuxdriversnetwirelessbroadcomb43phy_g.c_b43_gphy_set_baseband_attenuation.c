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
typedef  int u16 ;
struct b43_phy {int analog; } ;
struct b43_wldev {struct b43_phy phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43_MMIO_PHY0 ; 
 int /*<<< orphan*/  B43_PHY_DACCTL ; 
 int /*<<< orphan*/  b43_phy_maskset (struct b43_wldev*,int /*<<< orphan*/ ,int,int) ; 
 int b43_read16 (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_write16 (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 

void b43_gphy_set_baseband_attenuation(struct b43_wldev *dev,
				       u16 baseband_attenuation)
{
	struct b43_phy *phy = &dev->phy;

	if (phy->analog == 0) {
		b43_write16(dev, B43_MMIO_PHY0, (b43_read16(dev, B43_MMIO_PHY0)
						 & 0xFFF0) |
			    baseband_attenuation);
	} else if (phy->analog > 1) {
		b43_phy_maskset(dev, B43_PHY_DACCTL, 0xFFC3, (baseband_attenuation << 2));
	} else {
		b43_phy_maskset(dev, B43_PHY_DACCTL, 0xFF87, (baseband_attenuation << 3));
	}
}