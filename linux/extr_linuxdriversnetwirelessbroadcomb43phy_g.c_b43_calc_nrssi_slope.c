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
struct b43_phy {scalar_t__ type; int radio_rev; int rev; int /*<<< orphan*/  channel; struct b43_phy_g* g; } ;
struct b43_wldev {struct b43_phy phy; } ;
struct b43_phy_g {int nrssislope; int* nrssi; } ;
typedef  int s16 ;

/* Variables and functions */
 int B43_MMIO_CHANNEL_EXT ; 
 scalar_t__ B43_PHYTYPE_G ; 
 int B43_PHY_G_CRS ; 
 int B43_PHY_G_LO_CONTROL ; 
 int /*<<< orphan*/  B43_WARN_ON (int) ; 
 int /*<<< orphan*/  b43_calc_nrssi_offset (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_calc_nrssi_threshold (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_nrssi_mem_update (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_phy_mask (struct b43_wldev*,int,int) ; 
 int /*<<< orphan*/  b43_phy_maskset (struct b43_wldev*,int,int,int) ; 
 int b43_phy_read (struct b43_wldev*,int) ; 
 int /*<<< orphan*/  b43_phy_set (struct b43_wldev*,int,int) ; 
 int /*<<< orphan*/  b43_phy_write (struct b43_wldev*,int,int) ; 
 int /*<<< orphan*/  b43_radio_mask (struct b43_wldev*,int,int) ; 
 int b43_radio_read16 (struct b43_wldev*,int) ; 
 int /*<<< orphan*/  b43_radio_set (struct b43_wldev*,int,int) ; 
 int /*<<< orphan*/  b43_radio_write16 (struct b43_wldev*,int,int) ; 
 int b43_read16 (struct b43_wldev*,int) ; 
 int /*<<< orphan*/  b43_set_all_gains (struct b43_wldev*,int,int,int) ; 
 int /*<<< orphan*/  b43_set_original_gains (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_synth_pu_workaround (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_write16 (struct b43_wldev*,int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void b43_calc_nrssi_slope(struct b43_wldev *dev)
{
	struct b43_phy *phy = &dev->phy;
	struct b43_phy_g *gphy = phy->g;
	u16 backup[18] = { 0 };
	u16 tmp;
	s16 nrssi0, nrssi1;

	B43_WARN_ON(phy->type != B43_PHYTYPE_G);

	if (phy->radio_rev >= 9)
		return;
	if (phy->radio_rev == 8)
		b43_calc_nrssi_offset(dev);

	b43_phy_mask(dev, B43_PHY_G_CRS, 0x7FFF);
	b43_phy_mask(dev, 0x0802, 0xFFFC);
	backup[7] = b43_read16(dev, 0x03E2);
	b43_write16(dev, 0x03E2, b43_read16(dev, 0x03E2) | 0x8000);
	backup[0] = b43_radio_read16(dev, 0x007A);
	backup[1] = b43_radio_read16(dev, 0x0052);
	backup[2] = b43_radio_read16(dev, 0x0043);
	backup[3] = b43_phy_read(dev, 0x0015);
	backup[4] = b43_phy_read(dev, 0x005A);
	backup[5] = b43_phy_read(dev, 0x0059);
	backup[6] = b43_phy_read(dev, 0x0058);
	backup[8] = b43_read16(dev, 0x03E6);
	backup[9] = b43_read16(dev, B43_MMIO_CHANNEL_EXT);
	if (phy->rev >= 3) {
		backup[10] = b43_phy_read(dev, 0x002E);
		backup[11] = b43_phy_read(dev, 0x002F);
		backup[12] = b43_phy_read(dev, 0x080F);
		backup[13] = b43_phy_read(dev, B43_PHY_G_LO_CONTROL);
		backup[14] = b43_phy_read(dev, 0x0801);
		backup[15] = b43_phy_read(dev, 0x0060);
		backup[16] = b43_phy_read(dev, 0x0014);
		backup[17] = b43_phy_read(dev, 0x0478);
		b43_phy_write(dev, 0x002E, 0);
		b43_phy_write(dev, B43_PHY_G_LO_CONTROL, 0);
		switch (phy->rev) {
		case 4:
		case 6:
		case 7:
			b43_phy_set(dev, 0x0478, 0x0100);
			b43_phy_set(dev, 0x0801, 0x0040);
			break;
		case 3:
		case 5:
			b43_phy_mask(dev, 0x0801, 0xFFBF);
			break;
		}
		b43_phy_set(dev, 0x0060, 0x0040);
		b43_phy_set(dev, 0x0014, 0x0200);
	}
	b43_radio_set(dev, 0x007A, 0x0070);
	b43_set_all_gains(dev, 0, 8, 0);
	b43_radio_mask(dev, 0x007A, 0x00F7);
	if (phy->rev >= 2) {
		b43_phy_maskset(dev, 0x0811, 0xFFCF, 0x0030);
		b43_phy_maskset(dev, 0x0812, 0xFFCF, 0x0010);
	}
	b43_radio_set(dev, 0x007A, 0x0080);
	udelay(20);

	nrssi0 = (s16) ((b43_phy_read(dev, 0x047F) >> 8) & 0x003F);
	if (nrssi0 >= 0x0020)
		nrssi0 -= 0x0040;

	b43_radio_mask(dev, 0x007A, 0x007F);
	if (phy->rev >= 2) {
		b43_phy_maskset(dev, 0x0003, 0xFF9F, 0x0040);
	}

	b43_write16(dev, B43_MMIO_CHANNEL_EXT,
		    b43_read16(dev, B43_MMIO_CHANNEL_EXT)
		    | 0x2000);
	b43_radio_set(dev, 0x007A, 0x000F);
	b43_phy_write(dev, 0x0015, 0xF330);
	if (phy->rev >= 2) {
		b43_phy_maskset(dev, 0x0812, 0xFFCF, 0x0020);
		b43_phy_maskset(dev, 0x0811, 0xFFCF, 0x0020);
	}

	b43_set_all_gains(dev, 3, 0, 1);
	if (phy->radio_rev == 8) {
		b43_radio_write16(dev, 0x0043, 0x001F);
	} else {
		tmp = b43_radio_read16(dev, 0x0052) & 0xFF0F;
		b43_radio_write16(dev, 0x0052, tmp | 0x0060);
		tmp = b43_radio_read16(dev, 0x0043) & 0xFFF0;
		b43_radio_write16(dev, 0x0043, tmp | 0x0009);
	}
	b43_phy_write(dev, 0x005A, 0x0480);
	b43_phy_write(dev, 0x0059, 0x0810);
	b43_phy_write(dev, 0x0058, 0x000D);
	udelay(20);
	nrssi1 = (s16) ((b43_phy_read(dev, 0x047F) >> 8) & 0x003F);
	if (nrssi1 >= 0x0020)
		nrssi1 -= 0x0040;
	if (nrssi0 == nrssi1)
		gphy->nrssislope = 0x00010000;
	else
		gphy->nrssislope = 0x00400000 / (nrssi0 - nrssi1);
	if (nrssi0 >= -4) {
		gphy->nrssi[0] = nrssi1;
		gphy->nrssi[1] = nrssi0;
	}
	if (phy->rev >= 3) {
		b43_phy_write(dev, 0x002E, backup[10]);
		b43_phy_write(dev, 0x002F, backup[11]);
		b43_phy_write(dev, 0x080F, backup[12]);
		b43_phy_write(dev, B43_PHY_G_LO_CONTROL, backup[13]);
	}
	if (phy->rev >= 2) {
		b43_phy_mask(dev, 0x0812, 0xFFCF);
		b43_phy_mask(dev, 0x0811, 0xFFCF);
	}

	b43_radio_write16(dev, 0x007A, backup[0]);
	b43_radio_write16(dev, 0x0052, backup[1]);
	b43_radio_write16(dev, 0x0043, backup[2]);
	b43_write16(dev, 0x03E2, backup[7]);
	b43_write16(dev, 0x03E6, backup[8]);
	b43_write16(dev, B43_MMIO_CHANNEL_EXT, backup[9]);
	b43_phy_write(dev, 0x0015, backup[3]);
	b43_phy_write(dev, 0x005A, backup[4]);
	b43_phy_write(dev, 0x0059, backup[5]);
	b43_phy_write(dev, 0x0058, backup[6]);
	b43_synth_pu_workaround(dev, phy->channel);
	b43_phy_set(dev, 0x0802, (0x0001 | 0x0002));
	b43_set_original_gains(dev);
	b43_phy_set(dev, B43_PHY_G_CRS, 0x8000);
	if (phy->rev >= 3) {
		b43_phy_write(dev, 0x0801, backup[14]);
		b43_phy_write(dev, 0x0060, backup[15]);
		b43_phy_write(dev, 0x0014, backup[16]);
		b43_phy_write(dev, 0x0478, backup[17]);
	}
	b43_nrssi_mem_update(dev);
	b43_calc_nrssi_threshold(dev);
}