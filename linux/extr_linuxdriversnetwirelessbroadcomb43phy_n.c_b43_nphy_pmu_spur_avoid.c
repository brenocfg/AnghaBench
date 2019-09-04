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
struct b43_wldev {TYPE_1__* dev; } ;
struct TYPE_2__ {int bus_type; } ;

/* Variables and functions */

__attribute__((used)) static void b43_nphy_pmu_spur_avoid(struct b43_wldev *dev, bool avoid)
{
	switch (dev->dev->bus_type) {
#ifdef CONFIG_B43_BCMA
	case B43_BUS_BCMA:
		bcma_pmu_spuravoid_pllupdate(&dev->dev->bdev->bus->drv_cc,
					     avoid);
		break;
#endif
#ifdef CONFIG_B43_SSB
	case B43_BUS_SSB:
		ssb_pmu_spuravoid_pllupdate(&dev->dev->sdev->bus->chipco,
					    avoid);
		break;
#endif
	}
}