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
typedef  int u16 ;
struct b43legacy_phy {int rev; int radio_rev; int initval; int txctl2; int radio_ver; int txctl1; int* nrssi; scalar_t__ gmode; } ;
struct b43legacy_wldev {TYPE_3__* dev; struct b43legacy_phy phy; } ;
struct TYPE_6__ {TYPE_2__* bus; } ;
struct TYPE_4__ {int boardflags_lo; } ;
struct TYPE_5__ {int chip_id; int chip_package; TYPE_1__ sprom; } ;

/* Variables and functions */
 int B43legacy_BFL_PACTRL ; 
 int B43legacy_BFL_RSSI ; 
 int /*<<< orphan*/  B43legacy_WARN_ON (int) ; 
 int /*<<< orphan*/  b43legacy_calc_loopback_gain (struct b43legacy_wldev*) ; 
 int /*<<< orphan*/  b43legacy_calc_nrssi_slope (struct b43legacy_wldev*) ; 
 int /*<<< orphan*/  b43legacy_calc_nrssi_threshold (struct b43legacy_wldev*) ; 
 int /*<<< orphan*/  b43legacy_nrssi_hw_update (struct b43legacy_wldev*,int) ; 
 int /*<<< orphan*/  b43legacy_phy_init_pctl (struct b43legacy_wldev*) ; 
 int /*<<< orphan*/  b43legacy_phy_inita (struct b43legacy_wldev*) ; 
 int /*<<< orphan*/  b43legacy_phy_initb5 (struct b43legacy_wldev*) ; 
 int /*<<< orphan*/  b43legacy_phy_initb6 (struct b43legacy_wldev*) ; 
 int /*<<< orphan*/  b43legacy_phy_lo_adjust (struct b43legacy_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43legacy_phy_lo_g_measure (struct b43legacy_wldev*) ; 
 int b43legacy_phy_read (struct b43legacy_wldev*,int) ; 
 int /*<<< orphan*/  b43legacy_phy_write (struct b43legacy_wldev*,int,int) ; 
 int b43legacy_radio_init2050 (struct b43legacy_wldev*) ; 
 int b43legacy_radio_read16 (struct b43legacy_wldev*,int) ; 
 int /*<<< orphan*/  b43legacy_radio_write16 (struct b43legacy_wldev*,int,int) ; 

__attribute__((used)) static void b43legacy_phy_initg(struct b43legacy_wldev *dev)
{
	struct b43legacy_phy *phy = &dev->phy;
	u16 tmp;

	if (phy->rev == 1)
		b43legacy_phy_initb5(dev);
	else
		b43legacy_phy_initb6(dev);
	if (phy->rev >= 2 && phy->gmode)
		b43legacy_phy_inita(dev);

	if (phy->rev >= 2) {
		b43legacy_phy_write(dev, 0x0814, 0x0000);
		b43legacy_phy_write(dev, 0x0815, 0x0000);
	}
	if (phy->rev == 2) {
		b43legacy_phy_write(dev, 0x0811, 0x0000);
		b43legacy_phy_write(dev, 0x0015, 0x00C0);
	}
	if (phy->rev > 5) {
		b43legacy_phy_write(dev, 0x0811, 0x0400);
		b43legacy_phy_write(dev, 0x0015, 0x00C0);
	}
	if (phy->gmode) {
		tmp = b43legacy_phy_read(dev, 0x0400) & 0xFF;
		if (tmp == 3) {
			b43legacy_phy_write(dev, 0x04C2, 0x1816);
			b43legacy_phy_write(dev, 0x04C3, 0x8606);
		}
		if (tmp == 4 || tmp == 5) {
			b43legacy_phy_write(dev, 0x04C2, 0x1816);
			b43legacy_phy_write(dev, 0x04C3, 0x8006);
			b43legacy_phy_write(dev, 0x04CC,
					    (b43legacy_phy_read(dev,
					     0x04CC) & 0x00FF) |
					     0x1F00);
		}
		if (phy->rev >= 2)
			b43legacy_phy_write(dev, 0x047E, 0x0078);
	}
	if (phy->radio_rev == 8) {
		b43legacy_phy_write(dev, 0x0801, b43legacy_phy_read(dev, 0x0801)
				    | 0x0080);
		b43legacy_phy_write(dev, 0x043E, b43legacy_phy_read(dev, 0x043E)
				    | 0x0004);
	}
	if (phy->rev >= 2 && phy->gmode)
		b43legacy_calc_loopback_gain(dev);
	if (phy->radio_rev != 8) {
		if (phy->initval == 0xFFFF)
			phy->initval = b43legacy_radio_init2050(dev);
		else
			b43legacy_radio_write16(dev, 0x0078, phy->initval);
	}
	if (phy->txctl2 == 0xFFFF)
		b43legacy_phy_lo_g_measure(dev);
	else {
		if (phy->radio_ver == 0x2050 && phy->radio_rev == 8)
			b43legacy_radio_write16(dev, 0x0052,
						(phy->txctl1 << 4) |
						phy->txctl2);
		else
			b43legacy_radio_write16(dev, 0x0052,
						(b43legacy_radio_read16(dev,
						 0x0052) & 0xFFF0) |
						 phy->txctl1);
		if (phy->rev >= 6)
			b43legacy_phy_write(dev, 0x0036,
					    (b43legacy_phy_read(dev, 0x0036)
					     & 0x0FFF) | (phy->txctl2 << 12));
		if (dev->dev->bus->sprom.boardflags_lo &
		    B43legacy_BFL_PACTRL)
			b43legacy_phy_write(dev, 0x002E, 0x8075);
		else
			b43legacy_phy_write(dev, 0x002E, 0x807F);
		if (phy->rev < 2)
			b43legacy_phy_write(dev, 0x002F, 0x0101);
		else
			b43legacy_phy_write(dev, 0x002F, 0x0202);
	}
	if (phy->gmode) {
		b43legacy_phy_lo_adjust(dev, 0);
		b43legacy_phy_write(dev, 0x080F, 0x8078);
	}

	if (!(dev->dev->bus->sprom.boardflags_lo & B43legacy_BFL_RSSI)) {
		/* The specs state to update the NRSSI LT with
		 * the value 0x7FFFFFFF here. I think that is some weird
		 * compiler optimization in the original driver.
		 * Essentially, what we do here is resetting all NRSSI LT
		 * entries to -32 (see the clamp_val() in nrssi_hw_update())
		 */
		b43legacy_nrssi_hw_update(dev, 0xFFFF);
		b43legacy_calc_nrssi_threshold(dev);
	} else if (phy->gmode || phy->rev >= 2) {
		if (phy->nrssi[0] == -1000) {
			B43legacy_WARN_ON(phy->nrssi[1] != -1000);
			b43legacy_calc_nrssi_slope(dev);
		} else {
			B43legacy_WARN_ON(phy->nrssi[1] == -1000);
			b43legacy_calc_nrssi_threshold(dev);
		}
	}
	if (phy->radio_rev == 8)
		b43legacy_phy_write(dev, 0x0805, 0x3230);
	b43legacy_phy_init_pctl(dev);
	if (dev->dev->bus->chip_id == 0x4306
	    && dev->dev->bus->chip_package == 2) {
		b43legacy_phy_write(dev, 0x0429,
				    b43legacy_phy_read(dev, 0x0429) & 0xBFFF);
		b43legacy_phy_write(dev, 0x04C3,
				    b43legacy_phy_read(dev, 0x04C3) & 0x7FFF);
	}
}