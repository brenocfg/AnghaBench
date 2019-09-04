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
typedef  int u8 ;
typedef  int u16 ;
struct b43_phy {int radio_rev; scalar_t__ type; int channel; int analog; struct b43_phy_g* g; } ;
struct b43_wldev {TYPE_2__* dev; struct b43_phy phy; } ;
struct b43_phy_g {int /*<<< orphan*/  tx_control; int /*<<< orphan*/  rfatt; int /*<<< orphan*/  bbatt; } ;
struct TYPE_4__ {TYPE_1__* bus_sprom; } ;
struct TYPE_3__ {int boardflags_lo; } ;

/* Variables and functions */
 int B43_BFL_ALTIQ ; 
 int B43_HF_TSSIRPSMW ; 
 scalar_t__ B43_PHYTYPE_B ; 
 scalar_t__ B43_PHYTYPE_G ; 
 int /*<<< orphan*/  B43_WARN_ON (int) ; 
 int /*<<< orphan*/  b43_gphy_channel_switch (struct b43_wldev*,int,int /*<<< orphan*/ ) ; 
 int b43_hf_read (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_hf_write (struct b43_wldev*,int) ; 
 int /*<<< orphan*/  b43_phy_mask (struct b43_wldev*,int,int) ; 
 int /*<<< orphan*/  b43_phy_maskset (struct b43_wldev*,int,int,int) ; 
 int /*<<< orphan*/  b43_phy_set (struct b43_wldev*,int,int) ; 
 int /*<<< orphan*/  b43_phy_write (struct b43_wldev*,int,int) ; 
 int /*<<< orphan*/  b43_radio_maskset (struct b43_wldev*,int,int,int) ; 
 int b43_radio_read16 (struct b43_wldev*,int) ; 
 int /*<<< orphan*/  b43_radio_set (struct b43_wldev*,int,int) ; 
 int /*<<< orphan*/  b43_radio_write16 (struct b43_wldev*,int,int) ; 
 int /*<<< orphan*/  b43_set_txpower_g (struct b43_wldev*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_write16 (struct b43_wldev*,int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void b43_phy_initb6(struct b43_wldev *dev)
{
	struct b43_phy *phy = &dev->phy;
	struct b43_phy_g *gphy = phy->g;
	u16 offset, val;
	u8 old_channel;

	b43_phy_write(dev, 0x003E, 0x817A);
	b43_radio_write16(dev, 0x007A,
			  (b43_radio_read16(dev, 0x007A) | 0x0058));
	if (phy->radio_rev == 4 || phy->radio_rev == 5) {
		b43_radio_write16(dev, 0x51, 0x37);
		b43_radio_write16(dev, 0x52, 0x70);
		b43_radio_write16(dev, 0x53, 0xB3);
		b43_radio_write16(dev, 0x54, 0x9B);
		b43_radio_write16(dev, 0x5A, 0x88);
		b43_radio_write16(dev, 0x5B, 0x88);
		b43_radio_write16(dev, 0x5D, 0x88);
		b43_radio_write16(dev, 0x5E, 0x88);
		b43_radio_write16(dev, 0x7D, 0x88);
		b43_hf_write(dev, b43_hf_read(dev)
			     | B43_HF_TSSIRPSMW);
	}
	B43_WARN_ON(phy->radio_rev == 6 || phy->radio_rev == 7);	/* We had code for these revs here... */
	if (phy->radio_rev == 8) {
		b43_radio_write16(dev, 0x51, 0);
		b43_radio_write16(dev, 0x52, 0x40);
		b43_radio_write16(dev, 0x53, 0xB7);
		b43_radio_write16(dev, 0x54, 0x98);
		b43_radio_write16(dev, 0x5A, 0x88);
		b43_radio_write16(dev, 0x5B, 0x6B);
		b43_radio_write16(dev, 0x5C, 0x0F);
		if (dev->dev->bus_sprom->boardflags_lo & B43_BFL_ALTIQ) {
			b43_radio_write16(dev, 0x5D, 0xFA);
			b43_radio_write16(dev, 0x5E, 0xD8);
		} else {
			b43_radio_write16(dev, 0x5D, 0xF5);
			b43_radio_write16(dev, 0x5E, 0xB8);
		}
		b43_radio_write16(dev, 0x0073, 0x0003);
		b43_radio_write16(dev, 0x007D, 0x00A8);
		b43_radio_write16(dev, 0x007C, 0x0001);
		b43_radio_write16(dev, 0x007E, 0x0008);
	}
	val = 0x1E1F;
	for (offset = 0x0088; offset < 0x0098; offset++) {
		b43_phy_write(dev, offset, val);
		val -= 0x0202;
	}
	val = 0x3E3F;
	for (offset = 0x0098; offset < 0x00A8; offset++) {
		b43_phy_write(dev, offset, val);
		val -= 0x0202;
	}
	val = 0x2120;
	for (offset = 0x00A8; offset < 0x00C8; offset++) {
		b43_phy_write(dev, offset, (val & 0x3F3F));
		val += 0x0202;
	}
	if (phy->type == B43_PHYTYPE_G) {
		b43_radio_set(dev, 0x007A, 0x0020);
		b43_radio_set(dev, 0x0051, 0x0004);
		b43_phy_set(dev, 0x0802, 0x0100);
		b43_phy_set(dev, 0x042B, 0x2000);
		b43_phy_write(dev, 0x5B, 0);
		b43_phy_write(dev, 0x5C, 0);
	}

	old_channel = phy->channel;
	if (old_channel >= 8)
		b43_gphy_channel_switch(dev, 1, 0);
	else
		b43_gphy_channel_switch(dev, 13, 0);

	b43_radio_write16(dev, 0x0050, 0x0020);
	b43_radio_write16(dev, 0x0050, 0x0023);
	udelay(40);
	if (phy->radio_rev < 6 || phy->radio_rev == 8) {
		b43_radio_write16(dev, 0x7C, (b43_radio_read16(dev, 0x7C)
					      | 0x0002));
		b43_radio_write16(dev, 0x50, 0x20);
	}
	if (phy->radio_rev <= 2) {
		b43_radio_write16(dev, 0x50, 0x20);
		b43_radio_write16(dev, 0x5A, 0x70);
		b43_radio_write16(dev, 0x5B, 0x7B);
		b43_radio_write16(dev, 0x5C, 0xB0);
	}
	b43_radio_maskset(dev, 0x007A, 0x00F8, 0x0007);

	b43_gphy_channel_switch(dev, old_channel, 0);

	b43_phy_write(dev, 0x0014, 0x0200);
	if (phy->radio_rev >= 6)
		b43_phy_write(dev, 0x2A, 0x88C2);
	else
		b43_phy_write(dev, 0x2A, 0x8AC0);
	b43_phy_write(dev, 0x0038, 0x0668);
	b43_set_txpower_g(dev, &gphy->bbatt, &gphy->rfatt, gphy->tx_control);
	if (phy->radio_rev == 4 || phy->radio_rev == 5)
		b43_phy_maskset(dev, 0x5D, 0xFF80, 0x0003);
	if (phy->radio_rev <= 2)
		b43_radio_write16(dev, 0x005D, 0x000D);

	if (phy->analog == 4) {
		b43_write16(dev, 0x3E4, 9);
		b43_phy_mask(dev, 0x61, 0x0FFF);
	} else {
		b43_phy_maskset(dev, 0x0002, 0xFFC0, 0x0004);
	}
	if (phy->type == B43_PHYTYPE_B)
		B43_WARN_ON(1);
	else if (phy->type == B43_PHYTYPE_G)
		b43_write16(dev, 0x03E6, 0x0);
}