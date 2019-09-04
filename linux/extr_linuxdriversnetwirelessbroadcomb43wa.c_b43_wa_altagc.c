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
struct b43_phy {int rev; } ;
struct b43_wldev {struct b43_phy phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43_OFDMTAB_AGC1 ; 
 int /*<<< orphan*/  B43_OFDMTAB_AGC1_R1 ; 
 int /*<<< orphan*/  B43_OFDMTAB_AGC2 ; 
 int /*<<< orphan*/  B43_OFDMTAB_AGC3 ; 
 int /*<<< orphan*/  B43_OFDMTAB_AGC3_R1 ; 
 int /*<<< orphan*/  B43_PHY_ANTWRSETT ; 
 int /*<<< orphan*/  B43_PHY_CCKSHIFTBITS_WA ; 
 int /*<<< orphan*/  B43_PHY_DIVP1P2GAIN ; 
 int /*<<< orphan*/  B43_PHY_DIVSRCHIDX ; 
 int /*<<< orphan*/  B43_PHY_LMS ; 
 int /*<<< orphan*/  B43_PHY_LPFGAINCTL ; 
 int /*<<< orphan*/  B43_PHY_N1N2GAIN ; 
 int /*<<< orphan*/  B43_PHY_N1P1GAIN ; 
 int /*<<< orphan*/  B43_PHY_OFDM (int) ; 
 int /*<<< orphan*/  B43_PHY_P1P2GAIN ; 
 int /*<<< orphan*/  B43_PHY_PEAK_COUNT ; 
 int /*<<< orphan*/  B43_PHY_VERSION_OFDM ; 
 int /*<<< orphan*/  b43_ofdmtab_write16 (struct b43_wldev*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  b43_phy_mask (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43_phy_maskset (struct b43_wldev*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  b43_phy_read (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_phy_write (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43_radio_set (struct b43_wldev*,int,int) ; 

__attribute__((used)) static void b43_wa_altagc(struct b43_wldev *dev)
{
	struct b43_phy *phy = &dev->phy;

	if (phy->rev == 1) {
		b43_ofdmtab_write16(dev, B43_OFDMTAB_AGC1_R1, 0, 254);
		b43_ofdmtab_write16(dev, B43_OFDMTAB_AGC1_R1, 1, 13);
		b43_ofdmtab_write16(dev, B43_OFDMTAB_AGC1_R1, 2, 19);
		b43_ofdmtab_write16(dev, B43_OFDMTAB_AGC1_R1, 3, 25);
		b43_ofdmtab_write16(dev, B43_OFDMTAB_AGC2, 0, 0x2710);
		b43_ofdmtab_write16(dev, B43_OFDMTAB_AGC2, 1, 0x9B83);
		b43_ofdmtab_write16(dev, B43_OFDMTAB_AGC2, 2, 0x9B83);
		b43_ofdmtab_write16(dev, B43_OFDMTAB_AGC2, 3, 0x0F8D);
		b43_phy_write(dev, B43_PHY_LMS, 4);
	} else {
		b43_ofdmtab_write16(dev, B43_OFDMTAB_AGC1, 0, 254);
		b43_ofdmtab_write16(dev, B43_OFDMTAB_AGC1, 1, 13);
		b43_ofdmtab_write16(dev, B43_OFDMTAB_AGC1, 2, 19);
		b43_ofdmtab_write16(dev, B43_OFDMTAB_AGC1, 3, 25);
	}

	b43_phy_maskset(dev, B43_PHY_CCKSHIFTBITS_WA, 0x00FF, 0x5700);
	b43_phy_maskset(dev, B43_PHY_OFDM(0x1A), ~0x007F, 0x000F);
	b43_phy_maskset(dev, B43_PHY_OFDM(0x1A), ~0x3F80, 0x2B80);
	b43_phy_maskset(dev, B43_PHY_ANTWRSETT, 0xF0FF, 0x0300);
	b43_radio_set(dev, 0x7A, 0x0008);
	b43_phy_maskset(dev, B43_PHY_N1P1GAIN, ~0x000F, 0x0008);
	b43_phy_maskset(dev, B43_PHY_P1P2GAIN, ~0x0F00, 0x0600);
	b43_phy_maskset(dev, B43_PHY_N1N2GAIN, ~0x0F00, 0x0700);
	b43_phy_maskset(dev, B43_PHY_N1P1GAIN, ~0x0F00, 0x0100);
	if (phy->rev == 1) {
		b43_phy_maskset(dev, B43_PHY_N1N2GAIN, ~0x000F, 0x0007);
	}
	b43_phy_maskset(dev, B43_PHY_OFDM(0x88), ~0x00FF, 0x001C);
	b43_phy_maskset(dev, B43_PHY_OFDM(0x88), ~0x3F00, 0x0200);
	b43_phy_maskset(dev, B43_PHY_OFDM(0x96), ~0x00FF, 0x001C);
	b43_phy_maskset(dev, B43_PHY_OFDM(0x89), ~0x00FF, 0x0020);
	b43_phy_maskset(dev, B43_PHY_OFDM(0x89), ~0x3F00, 0x0200);
	b43_phy_maskset(dev, B43_PHY_OFDM(0x82), ~0x00FF, 0x002E);
	b43_phy_maskset(dev, B43_PHY_OFDM(0x96), 0x00FF, 0x1A00);
	b43_phy_maskset(dev, B43_PHY_OFDM(0x81), ~0x00FF, 0x0028);
	b43_phy_maskset(dev, B43_PHY_OFDM(0x81), 0x00FF, 0x2C00);
	if (phy->rev == 1) {
		b43_phy_write(dev, B43_PHY_PEAK_COUNT, 0x092B);
		b43_phy_maskset(dev, B43_PHY_OFDM(0x1B), ~0x001E, 0x0002);
	} else {
		b43_phy_mask(dev, B43_PHY_OFDM(0x1B), ~0x001E);
		b43_phy_write(dev, B43_PHY_OFDM(0x1F), 0x287A);
		b43_phy_maskset(dev, B43_PHY_LPFGAINCTL, ~0x000F, 0x0004);
		if (phy->rev >= 6) {
			b43_phy_write(dev, B43_PHY_OFDM(0x22), 0x287A);
			b43_phy_maskset(dev, B43_PHY_LPFGAINCTL, 0x0FFF, 0x3000);
		}
	}
	b43_phy_maskset(dev, B43_PHY_DIVSRCHIDX, 0x8080, 0x7874);
	b43_phy_write(dev, B43_PHY_OFDM(0x8E), 0x1C00);
	if (phy->rev == 1) {
		b43_phy_maskset(dev, B43_PHY_DIVP1P2GAIN, ~0x0F00, 0x0600);
		b43_phy_write(dev, B43_PHY_OFDM(0x8B), 0x005E);
		b43_phy_maskset(dev, B43_PHY_ANTWRSETT, ~0x00FF, 0x001E);
		b43_phy_write(dev, B43_PHY_OFDM(0x8D), 0x0002);
		b43_ofdmtab_write16(dev, B43_OFDMTAB_AGC3_R1, 0, 0);
		b43_ofdmtab_write16(dev, B43_OFDMTAB_AGC3_R1, 1, 7);
		b43_ofdmtab_write16(dev, B43_OFDMTAB_AGC3_R1, 2, 16);
		b43_ofdmtab_write16(dev, B43_OFDMTAB_AGC3_R1, 3, 28);
	} else {
		b43_ofdmtab_write16(dev, B43_OFDMTAB_AGC3, 0, 0);
		b43_ofdmtab_write16(dev, B43_OFDMTAB_AGC3, 1, 7);
		b43_ofdmtab_write16(dev, B43_OFDMTAB_AGC3, 2, 16);
		b43_ofdmtab_write16(dev, B43_OFDMTAB_AGC3, 3, 28);
	}
	if (phy->rev >= 6) {
		b43_phy_mask(dev, B43_PHY_OFDM(0x26), ~0x0003);
		b43_phy_mask(dev, B43_PHY_OFDM(0x26), ~0x1000);
	}
	b43_phy_read(dev, B43_PHY_VERSION_OFDM); /* Dummy read */
}