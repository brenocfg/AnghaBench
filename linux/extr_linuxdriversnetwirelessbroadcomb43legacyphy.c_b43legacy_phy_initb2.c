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
struct b43legacy_phy {int radio_ver; int /*<<< orphan*/  channel; } ;
struct b43legacy_wldev {struct b43legacy_phy phy; } ;

/* Variables and functions */
 int B43legacy_MMIO_CHANNEL_EXT ; 
 int /*<<< orphan*/  b43legacy_phy_init_pctl (struct b43legacy_wldev*) ; 
 int /*<<< orphan*/  b43legacy_phy_lo_b_measure (struct b43legacy_wldev*) ; 
 int /*<<< orphan*/  b43legacy_phy_write (struct b43legacy_wldev*,int,int) ; 
 int /*<<< orphan*/  b43legacy_radio_init2050 (struct b43legacy_wldev*) ; 
 int /*<<< orphan*/  b43legacy_radio_selectchannel (struct b43legacy_wldev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43legacy_radio_set_txpower_bg (struct b43legacy_wldev*,int,int,int) ; 
 int /*<<< orphan*/  b43legacy_radio_write16 (struct b43legacy_wldev*,int,int) ; 
 int /*<<< orphan*/  b43legacy_write16 (struct b43legacy_wldev*,int,int) ; 

__attribute__((used)) static void b43legacy_phy_initb2(struct b43legacy_wldev *dev)
{
	struct b43legacy_phy *phy = &dev->phy;
	u16 offset;
	int val;

	b43legacy_write16(dev, 0x03EC, 0x3F22);
	b43legacy_phy_write(dev, 0x0020, 0x301C);
	b43legacy_phy_write(dev, 0x0026, 0x0000);
	b43legacy_phy_write(dev, 0x0030, 0x00C6);
	b43legacy_phy_write(dev, 0x0088, 0x3E00);
	val = 0x3C3D;
	for (offset = 0x0089; offset < 0x00A7; offset++) {
		b43legacy_phy_write(dev, offset, val);
		val -= 0x0202;
	}
	b43legacy_phy_write(dev, 0x03E4, 0x3000);
	b43legacy_radio_selectchannel(dev, phy->channel, 0);
	if (phy->radio_ver != 0x2050) {
		b43legacy_radio_write16(dev, 0x0075, 0x0080);
		b43legacy_radio_write16(dev, 0x0079, 0x0081);
	}
	b43legacy_radio_write16(dev, 0x0050, 0x0020);
	b43legacy_radio_write16(dev, 0x0050, 0x0023);
	if (phy->radio_ver == 0x2050) {
		b43legacy_radio_write16(dev, 0x0050, 0x0020);
		b43legacy_radio_write16(dev, 0x005A, 0x0070);
		b43legacy_radio_write16(dev, 0x005B, 0x007B);
		b43legacy_radio_write16(dev, 0x005C, 0x00B0);
		b43legacy_radio_write16(dev, 0x007A, 0x000F);
		b43legacy_phy_write(dev, 0x0038, 0x0677);
		b43legacy_radio_init2050(dev);
	}
	b43legacy_phy_write(dev, 0x0014, 0x0080);
	b43legacy_phy_write(dev, 0x0032, 0x00CA);
	b43legacy_phy_write(dev, 0x0032, 0x00CC);
	b43legacy_phy_write(dev, 0x0035, 0x07C2);
	b43legacy_phy_lo_b_measure(dev);
	b43legacy_phy_write(dev, 0x0026, 0xCC00);
	if (phy->radio_ver != 0x2050)
		b43legacy_phy_write(dev, 0x0026, 0xCE00);
	b43legacy_write16(dev, B43legacy_MMIO_CHANNEL_EXT, 0x1000);
	b43legacy_phy_write(dev, 0x002A, 0x88A3);
	if (phy->radio_ver != 0x2050)
		b43legacy_phy_write(dev, 0x002A, 0x88C2);
	b43legacy_radio_set_txpower_bg(dev, 0xFFFF, 0xFFFF, 0xFFFF);
	b43legacy_phy_init_pctl(dev);
}