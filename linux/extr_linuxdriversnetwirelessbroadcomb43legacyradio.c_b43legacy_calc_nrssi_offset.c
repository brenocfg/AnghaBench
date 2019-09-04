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
struct b43legacy_phy {int rev; scalar_t__ analog; } ;
struct b43legacy_wldev {struct b43legacy_phy phy; } ;
typedef  int s16 ;

/* Variables and functions */
 int b43legacy_phy_read (struct b43legacy_wldev*,int) ; 
 int /*<<< orphan*/  b43legacy_phy_write (struct b43legacy_wldev*,int,int) ; 
 int b43legacy_radio_read16 (struct b43legacy_wldev*,int) ; 
 int /*<<< orphan*/  b43legacy_radio_write16 (struct b43legacy_wldev*,int,int) ; 
 int /*<<< orphan*/  b43legacy_set_all_gains (struct b43legacy_wldev*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43legacy_set_original_gains (struct b43legacy_wldev*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void b43legacy_calc_nrssi_offset(struct b43legacy_wldev *dev)
{
	struct b43legacy_phy *phy = &dev->phy;
	u16 backup[20] = { 0 };
	s16 v47F;
	u16 i;
	u16 saved = 0xFFFF;

	backup[0] = b43legacy_phy_read(dev, 0x0001);
	backup[1] = b43legacy_phy_read(dev, 0x0811);
	backup[2] = b43legacy_phy_read(dev, 0x0812);
	backup[3] = b43legacy_phy_read(dev, 0x0814);
	backup[4] = b43legacy_phy_read(dev, 0x0815);
	backup[5] = b43legacy_phy_read(dev, 0x005A);
	backup[6] = b43legacy_phy_read(dev, 0x0059);
	backup[7] = b43legacy_phy_read(dev, 0x0058);
	backup[8] = b43legacy_phy_read(dev, 0x000A);
	backup[9] = b43legacy_phy_read(dev, 0x0003);
	backup[10] = b43legacy_radio_read16(dev, 0x007A);
	backup[11] = b43legacy_radio_read16(dev, 0x0043);

	b43legacy_phy_write(dev, 0x0429,
			    b43legacy_phy_read(dev, 0x0429) & 0x7FFF);
	b43legacy_phy_write(dev, 0x0001,
			    (b43legacy_phy_read(dev, 0x0001) & 0x3FFF)
			    | 0x4000);
	b43legacy_phy_write(dev, 0x0811,
			    b43legacy_phy_read(dev, 0x0811) | 0x000C);
	b43legacy_phy_write(dev, 0x0812,
			    (b43legacy_phy_read(dev, 0x0812) & 0xFFF3)
			    | 0x0004);
	b43legacy_phy_write(dev, 0x0802,
			    b43legacy_phy_read(dev, 0x0802) & ~(0x1 | 0x2));
	if (phy->rev >= 6) {
		backup[12] = b43legacy_phy_read(dev, 0x002E);
		backup[13] = b43legacy_phy_read(dev, 0x002F);
		backup[14] = b43legacy_phy_read(dev, 0x080F);
		backup[15] = b43legacy_phy_read(dev, 0x0810);
		backup[16] = b43legacy_phy_read(dev, 0x0801);
		backup[17] = b43legacy_phy_read(dev, 0x0060);
		backup[18] = b43legacy_phy_read(dev, 0x0014);
		backup[19] = b43legacy_phy_read(dev, 0x0478);

		b43legacy_phy_write(dev, 0x002E, 0);
		b43legacy_phy_write(dev, 0x002F, 0);
		b43legacy_phy_write(dev, 0x080F, 0);
		b43legacy_phy_write(dev, 0x0810, 0);
		b43legacy_phy_write(dev, 0x0478,
				    b43legacy_phy_read(dev, 0x0478) | 0x0100);
		b43legacy_phy_write(dev, 0x0801,
				    b43legacy_phy_read(dev, 0x0801) | 0x0040);
		b43legacy_phy_write(dev, 0x0060,
				    b43legacy_phy_read(dev, 0x0060) | 0x0040);
		b43legacy_phy_write(dev, 0x0014,
				    b43legacy_phy_read(dev, 0x0014) | 0x0200);
	}
	b43legacy_radio_write16(dev, 0x007A,
				b43legacy_radio_read16(dev, 0x007A) | 0x0070);
	b43legacy_radio_write16(dev, 0x007A,
				b43legacy_radio_read16(dev, 0x007A) | 0x0080);
	udelay(30);

	v47F = (s16)((b43legacy_phy_read(dev, 0x047F) >> 8) & 0x003F);
	if (v47F >= 0x20)
		v47F -= 0x40;
	if (v47F == 31) {
		for (i = 7; i >= 4; i--) {
			b43legacy_radio_write16(dev, 0x007B, i);
			udelay(20);
			v47F = (s16)((b43legacy_phy_read(dev, 0x047F) >> 8)
							 & 0x003F);
			if (v47F >= 0x20)
				v47F -= 0x40;
			if (v47F < 31 && saved == 0xFFFF)
				saved = i;
		}
		if (saved == 0xFFFF)
			saved = 4;
	} else {
		b43legacy_radio_write16(dev, 0x007A,
					b43legacy_radio_read16(dev, 0x007A)
					& 0x007F);
		b43legacy_phy_write(dev, 0x0814,
				    b43legacy_phy_read(dev, 0x0814) | 0x0001);
		b43legacy_phy_write(dev, 0x0815,
				    b43legacy_phy_read(dev, 0x0815) & 0xFFFE);
		b43legacy_phy_write(dev, 0x0811,
				    b43legacy_phy_read(dev, 0x0811) | 0x000C);
		b43legacy_phy_write(dev, 0x0812,
				    b43legacy_phy_read(dev, 0x0812) | 0x000C);
		b43legacy_phy_write(dev, 0x0811,
				    b43legacy_phy_read(dev, 0x0811) | 0x0030);
		b43legacy_phy_write(dev, 0x0812,
				    b43legacy_phy_read(dev, 0x0812) | 0x0030);
		b43legacy_phy_write(dev, 0x005A, 0x0480);
		b43legacy_phy_write(dev, 0x0059, 0x0810);
		b43legacy_phy_write(dev, 0x0058, 0x000D);
		if (phy->analog == 0)
			b43legacy_phy_write(dev, 0x0003, 0x0122);
		else
			b43legacy_phy_write(dev, 0x000A,
					    b43legacy_phy_read(dev, 0x000A)
					    | 0x2000);
		b43legacy_phy_write(dev, 0x0814,
				    b43legacy_phy_read(dev, 0x0814) | 0x0004);
		b43legacy_phy_write(dev, 0x0815,
				    b43legacy_phy_read(dev, 0x0815) & 0xFFFB);
		b43legacy_phy_write(dev, 0x0003,
				    (b43legacy_phy_read(dev, 0x0003) & 0xFF9F)
				    | 0x0040);
		b43legacy_radio_write16(dev, 0x007A,
					b43legacy_radio_read16(dev, 0x007A)
					| 0x000F);
		b43legacy_set_all_gains(dev, 3, 0, 1);
		b43legacy_radio_write16(dev, 0x0043,
					(b43legacy_radio_read16(dev, 0x0043)
					& 0x00F0) | 0x000F);
		udelay(30);
		v47F = (s16)((b43legacy_phy_read(dev, 0x047F) >> 8) & 0x003F);
		if (v47F >= 0x20)
			v47F -= 0x40;
		if (v47F == -32) {
			for (i = 0; i < 4; i++) {
				b43legacy_radio_write16(dev, 0x007B, i);
				udelay(20);
				v47F = (s16)((b43legacy_phy_read(dev, 0x047F) >>
								 8) & 0x003F);
				if (v47F >= 0x20)
					v47F -= 0x40;
				if (v47F > -31 && saved == 0xFFFF)
					saved = i;
			}
			if (saved == 0xFFFF)
				saved = 3;
		} else
			saved = 0;
	}
	b43legacy_radio_write16(dev, 0x007B, saved);

	if (phy->rev >= 6) {
		b43legacy_phy_write(dev, 0x002E, backup[12]);
		b43legacy_phy_write(dev, 0x002F, backup[13]);
		b43legacy_phy_write(dev, 0x080F, backup[14]);
		b43legacy_phy_write(dev, 0x0810, backup[15]);
	}
	b43legacy_phy_write(dev, 0x0814, backup[3]);
	b43legacy_phy_write(dev, 0x0815, backup[4]);
	b43legacy_phy_write(dev, 0x005A, backup[5]);
	b43legacy_phy_write(dev, 0x0059, backup[6]);
	b43legacy_phy_write(dev, 0x0058, backup[7]);
	b43legacy_phy_write(dev, 0x000A, backup[8]);
	b43legacy_phy_write(dev, 0x0003, backup[9]);
	b43legacy_radio_write16(dev, 0x0043, backup[11]);
	b43legacy_radio_write16(dev, 0x007A, backup[10]);
	b43legacy_phy_write(dev, 0x0802,
			    b43legacy_phy_read(dev, 0x0802) | 0x1 | 0x2);
	b43legacy_phy_write(dev, 0x0429,
			    b43legacy_phy_read(dev, 0x0429) | 0x8000);
	b43legacy_set_original_gains(dev);
	if (phy->rev >= 6) {
		b43legacy_phy_write(dev, 0x0801, backup[16]);
		b43legacy_phy_write(dev, 0x0060, backup[17]);
		b43legacy_phy_write(dev, 0x0014, backup[18]);
		b43legacy_phy_write(dev, 0x0478, backup[19]);
	}
	b43legacy_phy_write(dev, 0x0001, backup[0]);
	b43legacy_phy_write(dev, 0x0812, backup[2]);
	b43legacy_phy_write(dev, 0x0811, backup[1]);
}