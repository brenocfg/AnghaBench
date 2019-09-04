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
typedef  int u32 ;
struct b43_wldev {scalar_t__ mac_suspended; int /*<<< orphan*/  wl; } ;

/* Variables and functions */
 int B43_IRQ_MAC_SUSPENDED ; 
 int /*<<< orphan*/  B43_MACCTL_ENABLED ; 
 int /*<<< orphan*/  B43_MMIO_GEN_IRQ_REASON ; 
 int /*<<< orphan*/  B43_MMIO_MACCTL ; 
 int /*<<< orphan*/  B43_PS_AWAKE ; 
 int /*<<< orphan*/  B43_WARN_ON (int) ; 
 int /*<<< orphan*/  b43_maskset32 (struct b43_wldev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_power_saving_ctl_bits (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 int b43_read32 (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  might_sleep () ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  udelay (int) ; 

void b43_mac_suspend(struct b43_wldev *dev)
{
	int i;
	u32 tmp;

	might_sleep();
	B43_WARN_ON(dev->mac_suspended < 0);

	if (dev->mac_suspended == 0) {
		b43_power_saving_ctl_bits(dev, B43_PS_AWAKE);
		b43_maskset32(dev, B43_MMIO_MACCTL, ~B43_MACCTL_ENABLED, 0);
		/* force pci to flush the write */
		b43_read32(dev, B43_MMIO_MACCTL);
		for (i = 35; i; i--) {
			tmp = b43_read32(dev, B43_MMIO_GEN_IRQ_REASON);
			if (tmp & B43_IRQ_MAC_SUSPENDED)
				goto out;
			udelay(10);
		}
		/* Hm, it seems this will take some time. Use msleep(). */
		for (i = 40; i; i--) {
			tmp = b43_read32(dev, B43_MMIO_GEN_IRQ_REASON);
			if (tmp & B43_IRQ_MAC_SUSPENDED)
				goto out;
			msleep(1);
		}
		b43err(dev->wl, "MAC suspend failed\n");
	}
out:
	dev->mac_suspended++;
}