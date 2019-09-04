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
typedef  scalar_t__ u16 ;
struct b43_wldev {scalar_t__ mac_suspended; int /*<<< orphan*/  wl; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43_DBG_FIRMWARE ; 
 int /*<<< orphan*/  B43_IRQ_MAC_SUSPENDED ; 
 int /*<<< orphan*/  B43_MACCTL_ENABLED ; 
 int /*<<< orphan*/  B43_MMIO_GEN_IRQ_REASON ; 
 int /*<<< orphan*/  B43_MMIO_MACCTL ; 
 int /*<<< orphan*/  B43_SHM_SHARED ; 
 int /*<<< orphan*/  B43_SHM_SH_UCODESTAT ; 
 scalar_t__ B43_SHM_SH_UCODESTAT_SLEEP ; 
 scalar_t__ B43_SHM_SH_UCODESTAT_SUSP ; 
 int /*<<< orphan*/  B43_WARN_ON (int) ; 
 scalar_t__ b43_debug (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_maskset32 (struct b43_wldev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_power_saving_ctl_bits (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_read32 (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 scalar_t__ b43_shm_read16 (struct b43_wldev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_write32 (struct b43_wldev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43err (int /*<<< orphan*/ ,char*,scalar_t__) ; 

void b43_mac_enable(struct b43_wldev *dev)
{
	if (b43_debug(dev, B43_DBG_FIRMWARE)) {
		u16 fwstate;

		fwstate = b43_shm_read16(dev, B43_SHM_SHARED,
					 B43_SHM_SH_UCODESTAT);
		if ((fwstate != B43_SHM_SH_UCODESTAT_SUSP) &&
		    (fwstate != B43_SHM_SH_UCODESTAT_SLEEP)) {
			b43err(dev->wl, "b43_mac_enable(): The firmware "
			       "should be suspended, but current state is %u\n",
			       fwstate);
		}
	}

	dev->mac_suspended--;
	B43_WARN_ON(dev->mac_suspended < 0);
	if (dev->mac_suspended == 0) {
		b43_maskset32(dev, B43_MMIO_MACCTL, ~0, B43_MACCTL_ENABLED);
		b43_write32(dev, B43_MMIO_GEN_IRQ_REASON,
			    B43_IRQ_MAC_SUSPENDED);
		/* Commit writes */
		b43_read32(dev, B43_MMIO_MACCTL);
		b43_read32(dev, B43_MMIO_GEN_IRQ_REASON);
		b43_power_saving_ctl_bits(dev, 0);
	}
}