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
typedef  int u16 ;
struct b43legacy_phy {int type; int radio_ver; int radio_rev; } ;
struct b43legacy_wldev {struct b43legacy_phy phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43legacy_BUG_ON (int) ; 
 int /*<<< orphan*/  B43legacy_MMIO_MACCTL ; 
#define  B43legacy_PHYTYPE_B 129 
#define  B43legacy_PHYTYPE_G 128 
 int /*<<< orphan*/  b43legacy_radio_write16 (struct b43legacy_wldev*,int,int) ; 
 int /*<<< orphan*/  b43legacy_ram_write (struct b43legacy_wldev*,unsigned int,int) ; 
 int b43legacy_read16 (struct b43legacy_wldev*,int) ; 
 int /*<<< orphan*/  b43legacy_read32 (struct b43legacy_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43legacy_write16 (struct b43legacy_wldev*,int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

void b43legacy_dummy_transmission(struct b43legacy_wldev *dev)
{
	struct b43legacy_phy *phy = &dev->phy;
	unsigned int i;
	unsigned int max_loop;
	u16 value;
	u32 buffer[5] = {
		0x00000000,
		0x00D40000,
		0x00000000,
		0x01000000,
		0x00000000,
	};

	switch (phy->type) {
	case B43legacy_PHYTYPE_B:
	case B43legacy_PHYTYPE_G:
		max_loop = 0xFA;
		buffer[0] = 0x000B846E;
		break;
	default:
		B43legacy_BUG_ON(1);
		return;
	}

	for (i = 0; i < 5; i++)
		b43legacy_ram_write(dev, i * 4, buffer[i]);

	/* dummy read follows */
	b43legacy_read32(dev, B43legacy_MMIO_MACCTL);

	b43legacy_write16(dev, 0x0568, 0x0000);
	b43legacy_write16(dev, 0x07C0, 0x0000);
	b43legacy_write16(dev, 0x050C, 0x0000);
	b43legacy_write16(dev, 0x0508, 0x0000);
	b43legacy_write16(dev, 0x050A, 0x0000);
	b43legacy_write16(dev, 0x054C, 0x0000);
	b43legacy_write16(dev, 0x056A, 0x0014);
	b43legacy_write16(dev, 0x0568, 0x0826);
	b43legacy_write16(dev, 0x0500, 0x0000);
	b43legacy_write16(dev, 0x0502, 0x0030);

	if (phy->radio_ver == 0x2050 && phy->radio_rev <= 0x5)
		b43legacy_radio_write16(dev, 0x0051, 0x0017);
	for (i = 0x00; i < max_loop; i++) {
		value = b43legacy_read16(dev, 0x050E);
		if (value & 0x0080)
			break;
		udelay(10);
	}
	for (i = 0x00; i < 0x0A; i++) {
		value = b43legacy_read16(dev, 0x050E);
		if (value & 0x0400)
			break;
		udelay(10);
	}
	for (i = 0x00; i < 0x0A; i++) {
		value = b43legacy_read16(dev, 0x0690);
		if (!(value & 0x0100))
			break;
		udelay(10);
	}
	if (phy->radio_ver == 0x2050 && phy->radio_rev <= 0x5)
		b43legacy_radio_write16(dev, 0x0051, 0x0037);
}