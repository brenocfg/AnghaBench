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
typedef  int /*<<< orphan*/  u32 ;
struct b43_wldev {TYPE_1__* dev; } ;
struct TYPE_2__ {int bus_type; } ;

/* Variables and functions */

void b43_mac_phy_clock_set(struct b43_wldev *dev, bool on)
{
	u32 tmp;

	switch (dev->dev->bus_type) {
#ifdef CONFIG_B43_BCMA
	case B43_BUS_BCMA:
		tmp = bcma_aread32(dev->dev->bdev, BCMA_IOCTL);
		if (on)
			tmp |= B43_BCMA_IOCTL_MACPHYCLKEN;
		else
			tmp &= ~B43_BCMA_IOCTL_MACPHYCLKEN;
		bcma_awrite32(dev->dev->bdev, BCMA_IOCTL, tmp);
		break;
#endif
#ifdef CONFIG_B43_SSB
	case B43_BUS_SSB:
		tmp = ssb_read32(dev->dev->sdev, SSB_TMSLOW);
		if (on)
			tmp |= B43_TMSLOW_MACPHYCLKEN;
		else
			tmp &= ~B43_TMSLOW_MACPHYCLKEN;
		ssb_write32(dev->dev->sdev, SSB_TMSLOW, tmp);
		break;
#endif
	}
}