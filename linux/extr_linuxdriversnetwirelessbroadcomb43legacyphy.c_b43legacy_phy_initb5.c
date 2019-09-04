#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u16 ;
struct b43legacy_phy {int analog; int radio_ver; int channel; scalar_t__ gmode; } ;
struct b43legacy_wldev {scalar_t__ bad_frames_preempt; TYPE_3__* dev; struct b43legacy_phy phy; } ;
struct TYPE_6__ {TYPE_2__* bus; } ;
struct TYPE_4__ {int type; } ;
struct TYPE_5__ {TYPE_1__ boardinfo; } ;

/* Variables and functions */
 int B43legacy_MMIO_PHY_RADIO ; 
 int B43legacy_PHY_RADIO_BITFIELD ; 
 int b43legacy_phy_read (struct b43legacy_wldev*,int) ; 
 int /*<<< orphan*/  b43legacy_phy_write (struct b43legacy_wldev*,int,int) ; 
 int b43legacy_radio_read16 (struct b43legacy_wldev*,int) ; 
 int /*<<< orphan*/  b43legacy_radio_selectchannel (struct b43legacy_wldev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43legacy_radio_set_txpower_bg (struct b43legacy_wldev*,int,int,int) ; 
 int /*<<< orphan*/  b43legacy_radio_write16 (struct b43legacy_wldev*,int,int) ; 
 int b43legacy_read16 (struct b43legacy_wldev*,int) ; 
 int /*<<< orphan*/  b43legacy_write16 (struct b43legacy_wldev*,int,int) ; 
 int /*<<< orphan*/  is_bcm_board_vendor (struct b43legacy_wldev*) ; 

__attribute__((used)) static void b43legacy_phy_initb5(struct b43legacy_wldev *dev)
{
	struct b43legacy_phy *phy = &dev->phy;
	u16 offset;
	u16 value;
	u8 old_channel;

	if (phy->analog == 1)
		b43legacy_radio_write16(dev, 0x007A,
					b43legacy_radio_read16(dev, 0x007A)
					| 0x0050);
	if (!is_bcm_board_vendor(dev) &&
	    (dev->dev->bus->boardinfo.type != 0x0416)) {
		value = 0x2120;
		for (offset = 0x00A8 ; offset < 0x00C7; offset++) {
			b43legacy_phy_write(dev, offset, value);
			value += 0x0202;
		}
	}
	b43legacy_phy_write(dev, 0x0035,
			    (b43legacy_phy_read(dev, 0x0035) & 0xF0FF)
			    | 0x0700);
	if (phy->radio_ver == 0x2050)
		b43legacy_phy_write(dev, 0x0038, 0x0667);

	if (phy->gmode) {
		if (phy->radio_ver == 0x2050) {
			b43legacy_radio_write16(dev, 0x007A,
					b43legacy_radio_read16(dev, 0x007A)
					| 0x0020);
			b43legacy_radio_write16(dev, 0x0051,
					b43legacy_radio_read16(dev, 0x0051)
					| 0x0004);
		}
		b43legacy_write16(dev, B43legacy_MMIO_PHY_RADIO, 0x0000);

		b43legacy_phy_write(dev, 0x0802, b43legacy_phy_read(dev, 0x0802)
				    | 0x0100);
		b43legacy_phy_write(dev, 0x042B, b43legacy_phy_read(dev, 0x042B)
				    | 0x2000);

		b43legacy_phy_write(dev, 0x001C, 0x186A);

		b43legacy_phy_write(dev, 0x0013, (b43legacy_phy_read(dev,
				    0x0013) & 0x00FF) | 0x1900);
		b43legacy_phy_write(dev, 0x0035, (b43legacy_phy_read(dev,
				    0x0035) & 0xFFC0) | 0x0064);
		b43legacy_phy_write(dev, 0x005D, (b43legacy_phy_read(dev,
				    0x005D) & 0xFF80) | 0x000A);
		b43legacy_phy_write(dev, 0x5B, 0x0000);
		b43legacy_phy_write(dev, 0x5C, 0x0000);
	}

	if (dev->bad_frames_preempt)
		b43legacy_phy_write(dev, B43legacy_PHY_RADIO_BITFIELD,
				    b43legacy_phy_read(dev,
				    B43legacy_PHY_RADIO_BITFIELD) | (1 << 12));

	if (phy->analog == 1) {
		b43legacy_phy_write(dev, 0x0026, 0xCE00);
		b43legacy_phy_write(dev, 0x0021, 0x3763);
		b43legacy_phy_write(dev, 0x0022, 0x1BC3);
		b43legacy_phy_write(dev, 0x0023, 0x06F9);
		b43legacy_phy_write(dev, 0x0024, 0x037E);
	} else
		b43legacy_phy_write(dev, 0x0026, 0xCC00);
	b43legacy_phy_write(dev, 0x0030, 0x00C6);
	b43legacy_write16(dev, 0x03EC, 0x3F22);

	if (phy->analog == 1)
		b43legacy_phy_write(dev, 0x0020, 0x3E1C);
	else
		b43legacy_phy_write(dev, 0x0020, 0x301C);

	if (phy->analog == 0)
		b43legacy_write16(dev, 0x03E4, 0x3000);

	old_channel = (phy->channel == 0xFF) ? 1 : phy->channel;
	/* Force to channel 7, even if not supported. */
	b43legacy_radio_selectchannel(dev, 7, 0);

	if (phy->radio_ver != 0x2050) {
		b43legacy_radio_write16(dev, 0x0075, 0x0080);
		b43legacy_radio_write16(dev, 0x0079, 0x0081);
	}

	b43legacy_radio_write16(dev, 0x0050, 0x0020);
	b43legacy_radio_write16(dev, 0x0050, 0x0023);

	if (phy->radio_ver == 0x2050) {
		b43legacy_radio_write16(dev, 0x0050, 0x0020);
		b43legacy_radio_write16(dev, 0x005A, 0x0070);
	}

	b43legacy_radio_write16(dev, 0x005B, 0x007B);
	b43legacy_radio_write16(dev, 0x005C, 0x00B0);

	b43legacy_radio_write16(dev, 0x007A, b43legacy_radio_read16(dev,
				0x007A) | 0x0007);

	b43legacy_radio_selectchannel(dev, old_channel, 0);

	b43legacy_phy_write(dev, 0x0014, 0x0080);
	b43legacy_phy_write(dev, 0x0032, 0x00CA);
	b43legacy_phy_write(dev, 0x002A, 0x88A3);

	b43legacy_radio_set_txpower_bg(dev, 0xFFFF, 0xFFFF, 0xFFFF);

	if (phy->radio_ver == 0x2050)
		b43legacy_radio_write16(dev, 0x005D, 0x000D);

	b43legacy_write16(dev, 0x03E4, (b43legacy_read16(dev, 0x03E4) &
			  0xFFC0) | 0x0004);
}