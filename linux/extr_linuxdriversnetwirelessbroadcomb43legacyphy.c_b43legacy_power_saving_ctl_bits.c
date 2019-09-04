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
typedef  int /*<<< orphan*/  u32 ;
struct b43legacy_wldev {TYPE_2__* dev; } ;
struct TYPE_3__ {int revision; } ;
struct TYPE_4__ {TYPE_1__ id; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43legacy_MACCTL_AWAKE ; 
 int /*<<< orphan*/  B43legacy_MACCTL_HWPS ; 
 int /*<<< orphan*/  B43legacy_MMIO_MACCTL ; 
 int /*<<< orphan*/  B43legacy_SHM_SHARED ; 
 int /*<<< orphan*/  b43legacy_read32 (struct b43legacy_wldev*,int /*<<< orphan*/ ) ; 
 int b43legacy_shm_read32 (struct b43legacy_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43legacy_write32 (struct b43legacy_wldev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

void b43legacy_power_saving_ctl_bits(struct b43legacy_wldev *dev,
				     int bit25, int bit26)
{
	int i;
	u32 status;

/* FIXME: Force 25 to off and 26 to on for now: */
bit25 = 0;
bit26 = 1;

	if (bit25 == -1) {
		/* TODO: If powersave is not off and FIXME is not set and we
		 *	are not in adhoc and thus is not an AP and we arei
		 *	associated, set bit 25 */
	}
	if (bit26 == -1) {
		/* TODO: If the device is awake or this is an AP, or we are
		 *	scanning, or FIXME, or we are associated, or FIXME,
		 *	or the latest PS-Poll packet sent was successful,
		 *	set bit26  */
	}
	status = b43legacy_read32(dev, B43legacy_MMIO_MACCTL);
	if (bit25)
		status |= B43legacy_MACCTL_HWPS;
	else
		status &= ~B43legacy_MACCTL_HWPS;
	if (bit26)
		status |= B43legacy_MACCTL_AWAKE;
	else
		status &= ~B43legacy_MACCTL_AWAKE;
	b43legacy_write32(dev, B43legacy_MMIO_MACCTL, status);
	if (bit26 && dev->dev->id.revision >= 5) {
		for (i = 0; i < 100; i++) {
			if (b43legacy_shm_read32(dev, B43legacy_SHM_SHARED,
						 0x0040) != 4)
				break;
			udelay(10);
		}
	}
}