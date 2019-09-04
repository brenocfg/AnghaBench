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
typedef  int u8 ;
typedef  int u16 ;
struct b43_phy {int analog; int radio_ver; int rev; int channel; scalar_t__ gmode; struct b43_phy_g* g; } ;
struct b43_wldev {scalar_t__ bad_frames_preempt; TYPE_1__* dev; struct b43_phy phy; } ;
struct b43_phy_g {int /*<<< orphan*/  tx_control; int /*<<< orphan*/  rfatt; int /*<<< orphan*/  bbatt; } ;
struct TYPE_2__ {scalar_t__ board_vendor; scalar_t__ board_type; } ;

/* Variables and functions */
 int B43_MMIO_PHY_RADIO ; 
 int B43_PHY_RADIO_BITFIELD ; 
 scalar_t__ SSB_BOARDVENDOR_BCM ; 
 scalar_t__ SSB_BOARD_BU4306 ; 
 int /*<<< orphan*/  b43_gphy_channel_switch (struct b43_wldev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_phy_maskset (struct b43_wldev*,int,int,int) ; 
 int /*<<< orphan*/  b43_phy_set (struct b43_wldev*,int,int) ; 
 int /*<<< orphan*/  b43_phy_write (struct b43_wldev*,int,int) ; 
 int /*<<< orphan*/  b43_radio_set (struct b43_wldev*,int,int) ; 
 int /*<<< orphan*/  b43_radio_write16 (struct b43_wldev*,int,int) ; 
 int b43_read16 (struct b43_wldev*,int) ; 
 int /*<<< orphan*/  b43_set_txpower_g (struct b43_wldev*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_write16 (struct b43_wldev*,int,int) ; 

__attribute__((used)) static void b43_phy_initb5(struct b43_wldev *dev)
{
	struct b43_phy *phy = &dev->phy;
	struct b43_phy_g *gphy = phy->g;
	u16 offset, value;
	u8 old_channel;

	if (phy->analog == 1) {
		b43_radio_set(dev, 0x007A, 0x0050);
	}
	if ((dev->dev->board_vendor != SSB_BOARDVENDOR_BCM) &&
	    (dev->dev->board_type != SSB_BOARD_BU4306)) {
		value = 0x2120;
		for (offset = 0x00A8; offset < 0x00C7; offset++) {
			b43_phy_write(dev, offset, value);
			value += 0x202;
		}
	}
	b43_phy_maskset(dev, 0x0035, 0xF0FF, 0x0700);
	if (phy->radio_ver == 0x2050)
		b43_phy_write(dev, 0x0038, 0x0667);

	if (phy->gmode || phy->rev >= 2) {
		if (phy->radio_ver == 0x2050) {
			b43_radio_set(dev, 0x007A, 0x0020);
			b43_radio_set(dev, 0x0051, 0x0004);
		}
		b43_write16(dev, B43_MMIO_PHY_RADIO, 0x0000);

		b43_phy_set(dev, 0x0802, 0x0100);
		b43_phy_set(dev, 0x042B, 0x2000);

		b43_phy_write(dev, 0x001C, 0x186A);

		b43_phy_maskset(dev, 0x0013, 0x00FF, 0x1900);
		b43_phy_maskset(dev, 0x0035, 0xFFC0, 0x0064);
		b43_phy_maskset(dev, 0x005D, 0xFF80, 0x000A);
	}

	if (dev->bad_frames_preempt) {
		b43_phy_set(dev, B43_PHY_RADIO_BITFIELD, (1 << 11));
	}

	if (phy->analog == 1) {
		b43_phy_write(dev, 0x0026, 0xCE00);
		b43_phy_write(dev, 0x0021, 0x3763);
		b43_phy_write(dev, 0x0022, 0x1BC3);
		b43_phy_write(dev, 0x0023, 0x06F9);
		b43_phy_write(dev, 0x0024, 0x037E);
	} else
		b43_phy_write(dev, 0x0026, 0xCC00);
	b43_phy_write(dev, 0x0030, 0x00C6);
	b43_write16(dev, 0x03EC, 0x3F22);

	if (phy->analog == 1)
		b43_phy_write(dev, 0x0020, 0x3E1C);
	else
		b43_phy_write(dev, 0x0020, 0x301C);

	if (phy->analog == 0)
		b43_write16(dev, 0x03E4, 0x3000);

	old_channel = phy->channel;
	/* Force to channel 7, even if not supported. */
	b43_gphy_channel_switch(dev, 7, 0);

	if (phy->radio_ver != 0x2050) {
		b43_radio_write16(dev, 0x0075, 0x0080);
		b43_radio_write16(dev, 0x0079, 0x0081);
	}

	b43_radio_write16(dev, 0x0050, 0x0020);
	b43_radio_write16(dev, 0x0050, 0x0023);

	if (phy->radio_ver == 0x2050) {
		b43_radio_write16(dev, 0x0050, 0x0020);
		b43_radio_write16(dev, 0x005A, 0x0070);
	}

	b43_radio_write16(dev, 0x005B, 0x007B);
	b43_radio_write16(dev, 0x005C, 0x00B0);

	b43_radio_set(dev, 0x007A, 0x0007);

	b43_gphy_channel_switch(dev, old_channel, 0);

	b43_phy_write(dev, 0x0014, 0x0080);
	b43_phy_write(dev, 0x0032, 0x00CA);
	b43_phy_write(dev, 0x002A, 0x88A3);

	b43_set_txpower_g(dev, &gphy->bbatt, &gphy->rfatt, gphy->tx_control);

	if (phy->radio_ver == 0x2050)
		b43_radio_write16(dev, 0x005D, 0x000D);

	b43_write16(dev, 0x03E4, (b43_read16(dev, 0x03E4) & 0xFFC0) | 0x0004);
}