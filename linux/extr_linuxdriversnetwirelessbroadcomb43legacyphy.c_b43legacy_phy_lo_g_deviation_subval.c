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
struct b43legacy_phy {scalar_t__ gmode; } ;
struct b43legacy_wldev {struct b43legacy_phy phy; } ;

/* Variables and functions */
 int b43legacy_phy_read (struct b43legacy_wldev*,int) ; 
 int /*<<< orphan*/  b43legacy_phy_write (struct b43legacy_wldev*,int,int) ; 
 int /*<<< orphan*/  b43legacy_voluntary_preempt () ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static inline
u16 b43legacy_phy_lo_g_deviation_subval(struct b43legacy_wldev *dev,
					u16 control)
{
	struct b43legacy_phy *phy = &dev->phy;
	u16 ret;
	unsigned long flags;

	local_irq_save(flags);
	if (phy->gmode) {
		b43legacy_phy_write(dev, 0x15, 0xE300);
		control <<= 8;
		b43legacy_phy_write(dev, 0x0812, control | 0x00B0);
		udelay(5);
		b43legacy_phy_write(dev, 0x0812, control | 0x00B2);
		udelay(2);
		b43legacy_phy_write(dev, 0x0812, control | 0x00B3);
		udelay(4);
		b43legacy_phy_write(dev, 0x0015, 0xF300);
		udelay(8);
	} else {
		b43legacy_phy_write(dev, 0x0015, control | 0xEFA0);
		udelay(2);
		b43legacy_phy_write(dev, 0x0015, control | 0xEFE0);
		udelay(4);
		b43legacy_phy_write(dev, 0x0015, control | 0xFFE0);
		udelay(8);
	}
	ret = b43legacy_phy_read(dev, 0x002D);
	local_irq_restore(flags);
	b43legacy_voluntary_preempt();

	return ret;
}