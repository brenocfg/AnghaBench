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
struct init2050_saved_values {int radio_43; int radio_51; int radio_52; int phy_pgactl; int phy_cck_5A; int phy_cck_59; int phy_cck_58; int phy_cck_30; int reg_3EC; int phy_rfover; int phy_rfoverval; int phy_analogover; int phy_analogoverval; int phy_crs0; int phy_classctl; int phy_lo_mask; int phy_lo_ctl; int phy_syncctl; int reg_3E6; int reg_3F4; } ;
struct b43_phy {scalar_t__ type; int rev; int analog; int radio_rev; scalar_t__ gmode; int /*<<< orphan*/  channel; } ;
struct b43_wldev {struct b43_phy phy; } ;
typedef  int /*<<< orphan*/  sav ;

/* Variables and functions */
 int B43_MMIO_CHANNEL_EXT ; 
 int B43_MMIO_PHY_RADIO ; 
 scalar_t__ B43_PHYTYPE_B ; 
 int /*<<< orphan*/  B43_PHY_ANALOGOVER ; 
 int /*<<< orphan*/  B43_PHY_ANALOGOVERVAL ; 
 int /*<<< orphan*/  B43_PHY_CCK (int) ; 
 int /*<<< orphan*/  B43_PHY_CLASSCTL ; 
 int /*<<< orphan*/  B43_PHY_CRS0 ; 
 int /*<<< orphan*/  B43_PHY_LO_CTL ; 
 int /*<<< orphan*/  B43_PHY_LO_LEAKAGE ; 
 int /*<<< orphan*/  B43_PHY_LO_MASK ; 
 int /*<<< orphan*/  B43_PHY_PGACTL ; 
 int /*<<< orphan*/  B43_PHY_RFOVER ; 
 int /*<<< orphan*/  B43_PHY_RFOVERVAL ; 
 int /*<<< orphan*/  B43_PHY_SYNCCTL ; 
 int /*<<< orphan*/  LPD (int,int,int) ; 
 int /*<<< orphan*/  b43_phy_mask (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43_phy_maskset (struct b43_wldev*,int /*<<< orphan*/ ,int,int) ; 
 void* b43_phy_read (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_phy_set (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43_phy_write (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int b43_radio_core_calibration_value (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_radio_maskset (struct b43_wldev*,int,int,int) ; 
 void* b43_radio_read16 (struct b43_wldev*,int) ; 
 int /*<<< orphan*/  b43_radio_set (struct b43_wldev*,int,int) ; 
 int /*<<< orphan*/  b43_radio_write16 (struct b43_wldev*,int,int) ; 
 int b43_read16 (struct b43_wldev*,int) ; 
 int /*<<< orphan*/  b43_synth_pu_workaround (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_write16 (struct b43_wldev*,int,int) ; 
 int bitrev4 (int) ; 
 scalar_t__ has_loopback_gain (struct b43_phy*) ; 
 int /*<<< orphan*/  memset (struct init2050_saved_values*,int /*<<< orphan*/ ,int) ; 
 int radio2050_rfover_val (struct b43_wldev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static u16 b43_radio_init2050(struct b43_wldev *dev)
{
	struct b43_phy *phy = &dev->phy;
	struct init2050_saved_values sav;
	u16 rcc;
	u16 radio78;
	u16 ret;
	u16 i, j;
	u32 tmp1 = 0, tmp2 = 0;

	memset(&sav, 0, sizeof(sav));	/* get rid of "may be used uninitialized..." */

	sav.radio_43 = b43_radio_read16(dev, 0x43);
	sav.radio_51 = b43_radio_read16(dev, 0x51);
	sav.radio_52 = b43_radio_read16(dev, 0x52);
	sav.phy_pgactl = b43_phy_read(dev, B43_PHY_PGACTL);
	sav.phy_cck_5A = b43_phy_read(dev, B43_PHY_CCK(0x5A));
	sav.phy_cck_59 = b43_phy_read(dev, B43_PHY_CCK(0x59));
	sav.phy_cck_58 = b43_phy_read(dev, B43_PHY_CCK(0x58));

	if (phy->type == B43_PHYTYPE_B) {
		sav.phy_cck_30 = b43_phy_read(dev, B43_PHY_CCK(0x30));
		sav.reg_3EC = b43_read16(dev, 0x3EC);

		b43_phy_write(dev, B43_PHY_CCK(0x30), 0xFF);
		b43_write16(dev, 0x3EC, 0x3F3F);
	} else if (phy->gmode || phy->rev >= 2) {
		sav.phy_rfover = b43_phy_read(dev, B43_PHY_RFOVER);
		sav.phy_rfoverval = b43_phy_read(dev, B43_PHY_RFOVERVAL);
		sav.phy_analogover = b43_phy_read(dev, B43_PHY_ANALOGOVER);
		sav.phy_analogoverval =
		    b43_phy_read(dev, B43_PHY_ANALOGOVERVAL);
		sav.phy_crs0 = b43_phy_read(dev, B43_PHY_CRS0);
		sav.phy_classctl = b43_phy_read(dev, B43_PHY_CLASSCTL);

		b43_phy_set(dev, B43_PHY_ANALOGOVER, 0x0003);
		b43_phy_mask(dev, B43_PHY_ANALOGOVERVAL, 0xFFFC);
		b43_phy_mask(dev, B43_PHY_CRS0, 0x7FFF);
		b43_phy_mask(dev, B43_PHY_CLASSCTL, 0xFFFC);
		if (has_loopback_gain(phy)) {
			sav.phy_lo_mask = b43_phy_read(dev, B43_PHY_LO_MASK);
			sav.phy_lo_ctl = b43_phy_read(dev, B43_PHY_LO_CTL);

			if (phy->rev >= 3)
				b43_phy_write(dev, B43_PHY_LO_MASK, 0xC020);
			else
				b43_phy_write(dev, B43_PHY_LO_MASK, 0x8020);
			b43_phy_write(dev, B43_PHY_LO_CTL, 0);
		}

		b43_phy_write(dev, B43_PHY_RFOVERVAL,
			      radio2050_rfover_val(dev, B43_PHY_RFOVERVAL,
						   LPD(0, 1, 1)));
		b43_phy_write(dev, B43_PHY_RFOVER,
			      radio2050_rfover_val(dev, B43_PHY_RFOVER, 0));
	}
	b43_write16(dev, 0x3E2, b43_read16(dev, 0x3E2) | 0x8000);

	sav.phy_syncctl = b43_phy_read(dev, B43_PHY_SYNCCTL);
	b43_phy_mask(dev, B43_PHY_SYNCCTL, 0xFF7F);
	sav.reg_3E6 = b43_read16(dev, 0x3E6);
	sav.reg_3F4 = b43_read16(dev, 0x3F4);

	if (phy->analog == 0) {
		b43_write16(dev, 0x03E6, 0x0122);
	} else {
		if (phy->analog >= 2) {
			b43_phy_maskset(dev, B43_PHY_CCK(0x03), 0xFFBF, 0x40);
		}
		b43_write16(dev, B43_MMIO_CHANNEL_EXT,
			    (b43_read16(dev, B43_MMIO_CHANNEL_EXT) | 0x2000));
	}

	rcc = b43_radio_core_calibration_value(dev);

	if (phy->type == B43_PHYTYPE_B)
		b43_radio_write16(dev, 0x78, 0x26);
	if (phy->gmode || phy->rev >= 2) {
		b43_phy_write(dev, B43_PHY_RFOVERVAL,
			      radio2050_rfover_val(dev, B43_PHY_RFOVERVAL,
						   LPD(0, 1, 1)));
	}
	b43_phy_write(dev, B43_PHY_PGACTL, 0xBFAF);
	b43_phy_write(dev, B43_PHY_CCK(0x2B), 0x1403);
	if (phy->gmode || phy->rev >= 2) {
		b43_phy_write(dev, B43_PHY_RFOVERVAL,
			      radio2050_rfover_val(dev, B43_PHY_RFOVERVAL,
						   LPD(0, 0, 1)));
	}
	b43_phy_write(dev, B43_PHY_PGACTL, 0xBFA0);
	b43_radio_set(dev, 0x51, 0x0004);
	if (phy->radio_rev == 8) {
		b43_radio_write16(dev, 0x43, 0x1F);
	} else {
		b43_radio_write16(dev, 0x52, 0);
		b43_radio_maskset(dev, 0x43, 0xFFF0, 0x0009);
	}
	b43_phy_write(dev, B43_PHY_CCK(0x58), 0);

	for (i = 0; i < 16; i++) {
		b43_phy_write(dev, B43_PHY_CCK(0x5A), 0x0480);
		b43_phy_write(dev, B43_PHY_CCK(0x59), 0xC810);
		b43_phy_write(dev, B43_PHY_CCK(0x58), 0x000D);
		if (phy->gmode || phy->rev >= 2) {
			b43_phy_write(dev, B43_PHY_RFOVERVAL,
				      radio2050_rfover_val(dev,
							   B43_PHY_RFOVERVAL,
							   LPD(1, 0, 1)));
		}
		b43_phy_write(dev, B43_PHY_PGACTL, 0xAFB0);
		udelay(10);
		if (phy->gmode || phy->rev >= 2) {
			b43_phy_write(dev, B43_PHY_RFOVERVAL,
				      radio2050_rfover_val(dev,
							   B43_PHY_RFOVERVAL,
							   LPD(1, 0, 1)));
		}
		b43_phy_write(dev, B43_PHY_PGACTL, 0xEFB0);
		udelay(10);
		if (phy->gmode || phy->rev >= 2) {
			b43_phy_write(dev, B43_PHY_RFOVERVAL,
				      radio2050_rfover_val(dev,
							   B43_PHY_RFOVERVAL,
							   LPD(1, 0, 0)));
		}
		b43_phy_write(dev, B43_PHY_PGACTL, 0xFFF0);
		udelay(20);
		tmp1 += b43_phy_read(dev, B43_PHY_LO_LEAKAGE);
		b43_phy_write(dev, B43_PHY_CCK(0x58), 0);
		if (phy->gmode || phy->rev >= 2) {
			b43_phy_write(dev, B43_PHY_RFOVERVAL,
				      radio2050_rfover_val(dev,
							   B43_PHY_RFOVERVAL,
							   LPD(1, 0, 1)));
		}
		b43_phy_write(dev, B43_PHY_PGACTL, 0xAFB0);
	}
	udelay(10);

	b43_phy_write(dev, B43_PHY_CCK(0x58), 0);
	tmp1++;
	tmp1 >>= 9;

	for (i = 0; i < 16; i++) {
		radio78 = (bitrev4(i) << 1) | 0x0020;
		b43_radio_write16(dev, 0x78, radio78);
		udelay(10);
		for (j = 0; j < 16; j++) {
			b43_phy_write(dev, B43_PHY_CCK(0x5A), 0x0D80);
			b43_phy_write(dev, B43_PHY_CCK(0x59), 0xC810);
			b43_phy_write(dev, B43_PHY_CCK(0x58), 0x000D);
			if (phy->gmode || phy->rev >= 2) {
				b43_phy_write(dev, B43_PHY_RFOVERVAL,
					      radio2050_rfover_val(dev,
								   B43_PHY_RFOVERVAL,
								   LPD(1, 0,
								       1)));
			}
			b43_phy_write(dev, B43_PHY_PGACTL, 0xAFB0);
			udelay(10);
			if (phy->gmode || phy->rev >= 2) {
				b43_phy_write(dev, B43_PHY_RFOVERVAL,
					      radio2050_rfover_val(dev,
								   B43_PHY_RFOVERVAL,
								   LPD(1, 0,
								       1)));
			}
			b43_phy_write(dev, B43_PHY_PGACTL, 0xEFB0);
			udelay(10);
			if (phy->gmode || phy->rev >= 2) {
				b43_phy_write(dev, B43_PHY_RFOVERVAL,
					      radio2050_rfover_val(dev,
								   B43_PHY_RFOVERVAL,
								   LPD(1, 0,
								       0)));
			}
			b43_phy_write(dev, B43_PHY_PGACTL, 0xFFF0);
			udelay(10);
			tmp2 += b43_phy_read(dev, B43_PHY_LO_LEAKAGE);
			b43_phy_write(dev, B43_PHY_CCK(0x58), 0);
			if (phy->gmode || phy->rev >= 2) {
				b43_phy_write(dev, B43_PHY_RFOVERVAL,
					      radio2050_rfover_val(dev,
								   B43_PHY_RFOVERVAL,
								   LPD(1, 0,
								       1)));
			}
			b43_phy_write(dev, B43_PHY_PGACTL, 0xAFB0);
		}
		tmp2++;
		tmp2 >>= 8;
		if (tmp1 < tmp2)
			break;
	}

	/* Restore the registers */
	b43_phy_write(dev, B43_PHY_PGACTL, sav.phy_pgactl);
	b43_radio_write16(dev, 0x51, sav.radio_51);
	b43_radio_write16(dev, 0x52, sav.radio_52);
	b43_radio_write16(dev, 0x43, sav.radio_43);
	b43_phy_write(dev, B43_PHY_CCK(0x5A), sav.phy_cck_5A);
	b43_phy_write(dev, B43_PHY_CCK(0x59), sav.phy_cck_59);
	b43_phy_write(dev, B43_PHY_CCK(0x58), sav.phy_cck_58);
	b43_write16(dev, 0x3E6, sav.reg_3E6);
	if (phy->analog != 0)
		b43_write16(dev, 0x3F4, sav.reg_3F4);
	b43_phy_write(dev, B43_PHY_SYNCCTL, sav.phy_syncctl);
	b43_synth_pu_workaround(dev, phy->channel);
	if (phy->type == B43_PHYTYPE_B) {
		b43_phy_write(dev, B43_PHY_CCK(0x30), sav.phy_cck_30);
		b43_write16(dev, 0x3EC, sav.reg_3EC);
	} else if (phy->gmode) {
		b43_write16(dev, B43_MMIO_PHY_RADIO,
			    b43_read16(dev, B43_MMIO_PHY_RADIO)
			    & 0x7FFF);
		b43_phy_write(dev, B43_PHY_RFOVER, sav.phy_rfover);
		b43_phy_write(dev, B43_PHY_RFOVERVAL, sav.phy_rfoverval);
		b43_phy_write(dev, B43_PHY_ANALOGOVER, sav.phy_analogover);
		b43_phy_write(dev, B43_PHY_ANALOGOVERVAL,
			      sav.phy_analogoverval);
		b43_phy_write(dev, B43_PHY_CRS0, sav.phy_crs0);
		b43_phy_write(dev, B43_PHY_CLASSCTL, sav.phy_classctl);
		if (has_loopback_gain(phy)) {
			b43_phy_write(dev, B43_PHY_LO_MASK, sav.phy_lo_mask);
			b43_phy_write(dev, B43_PHY_LO_CTL, sav.phy_lo_ctl);
		}
	}
	if (i > 15)
		ret = radio78;
	else
		ret = rcc;

	return ret;
}