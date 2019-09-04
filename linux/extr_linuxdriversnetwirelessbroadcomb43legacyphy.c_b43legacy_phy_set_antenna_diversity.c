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
typedef  int u32 ;
typedef  int u16 ;
struct b43legacy_phy {int antenna_diversity; int type; int rev; } ;
struct b43legacy_wldev {TYPE_2__* dev; struct b43legacy_phy phy; } ;
struct TYPE_3__ {int revision; } ;
struct TYPE_4__ {TYPE_1__ id; } ;

/* Variables and functions */
#define  B43legacy_PHYTYPE_B 129 
#define  B43legacy_PHYTYPE_G 128 
 int /*<<< orphan*/  B43legacy_SHM_SHARED ; 
 int /*<<< orphan*/  B43legacy_UCODEFLAGS_OFFSET ; 
 int B43legacy_UCODEFLAG_AUTODIV ; 
 int /*<<< orphan*/  B43legacy_WARN_ON (int) ; 
 int b43legacy_phy_read (struct b43legacy_wldev*,int) ; 
 int /*<<< orphan*/  b43legacy_phy_write (struct b43legacy_wldev*,int,int) ; 
 int b43legacy_shm_read32 (struct b43legacy_wldev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43legacy_shm_write32 (struct b43legacy_wldev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void b43legacy_phy_set_antenna_diversity(struct b43legacy_wldev *dev)
{
	struct b43legacy_phy *phy = &dev->phy;
	u16 antennadiv;
	u16 offset;
	u16 value;
	u32 ucodeflags;

	antennadiv = phy->antenna_diversity;

	if (antennadiv == 0xFFFF)
		antennadiv = 3;
	B43legacy_WARN_ON(antennadiv > 3);

	ucodeflags = b43legacy_shm_read32(dev, B43legacy_SHM_SHARED,
					  B43legacy_UCODEFLAGS_OFFSET);
	b43legacy_shm_write32(dev, B43legacy_SHM_SHARED,
			      B43legacy_UCODEFLAGS_OFFSET,
			      ucodeflags & ~B43legacy_UCODEFLAG_AUTODIV);

	switch (phy->type) {
	case B43legacy_PHYTYPE_G:
		offset = 0x0400;

		if (antennadiv == 2)
			value = (3/*automatic*/ << 7);
		else
			value = (antennadiv << 7);
		b43legacy_phy_write(dev, offset + 1,
				    (b43legacy_phy_read(dev, offset + 1)
				    & 0x7E7F) | value);

		if (antennadiv >= 2) {
			if (antennadiv == 2)
				value = (antennadiv << 7);
			else
				value = (0/*force0*/ << 7);
			b43legacy_phy_write(dev, offset + 0x2B,
					    (b43legacy_phy_read(dev,
					    offset + 0x2B)
					    & 0xFEFF) | value);
		}

		if (phy->type == B43legacy_PHYTYPE_G) {
			if (antennadiv >= 2)
				b43legacy_phy_write(dev, 0x048C,
						    b43legacy_phy_read(dev,
						    0x048C) | 0x2000);
			else
				b43legacy_phy_write(dev, 0x048C,
						    b43legacy_phy_read(dev,
						    0x048C) & ~0x2000);
			if (phy->rev >= 2) {
				b43legacy_phy_write(dev, 0x0461,
						    b43legacy_phy_read(dev,
						    0x0461) | 0x0010);
				b43legacy_phy_write(dev, 0x04AD,
						    (b43legacy_phy_read(dev,
						    0x04AD)
						    & 0x00FF) | 0x0015);
				if (phy->rev == 2)
					b43legacy_phy_write(dev, 0x0427,
							    0x0008);
				else
					b43legacy_phy_write(dev, 0x0427,
						(b43legacy_phy_read(dev, 0x0427)
						 & 0x00FF) | 0x0008);
			} else if (phy->rev >= 6)
				b43legacy_phy_write(dev, 0x049B, 0x00DC);
		} else {
			if (phy->rev < 3)
				b43legacy_phy_write(dev, 0x002B,
						    (b43legacy_phy_read(dev,
						    0x002B) & 0x00FF)
						    | 0x0024);
			else {
				b43legacy_phy_write(dev, 0x0061,
						    b43legacy_phy_read(dev,
						    0x0061) | 0x0010);
				if (phy->rev == 3) {
					b43legacy_phy_write(dev, 0x0093,
							    0x001D);
					b43legacy_phy_write(dev, 0x0027,
							    0x0008);
				} else {
					b43legacy_phy_write(dev, 0x0093,
							    0x003A);
					b43legacy_phy_write(dev, 0x0027,
						(b43legacy_phy_read(dev, 0x0027)
						 & 0x00FF) | 0x0008);
				}
			}
		}
		break;
	case B43legacy_PHYTYPE_B:
		if (dev->dev->id.revision == 2)
			value = (3/*automatic*/ << 7);
		else
			value = (antennadiv << 7);
		b43legacy_phy_write(dev, 0x03E2,
				    (b43legacy_phy_read(dev, 0x03E2)
				    & 0xFE7F) | value);
		break;
	default:
		B43legacy_WARN_ON(1);
	}

	if (antennadiv >= 2) {
		ucodeflags = b43legacy_shm_read32(dev, B43legacy_SHM_SHARED,
						  B43legacy_UCODEFLAGS_OFFSET);
		b43legacy_shm_write32(dev, B43legacy_SHM_SHARED,
				      B43legacy_UCODEFLAGS_OFFSET,
				      ucodeflags | B43legacy_UCODEFLAG_AUTODIV);
	}

	phy->antenna_diversity = antennadiv;
}