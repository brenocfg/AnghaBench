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
struct ssb_sprom {int revision; int boardflags2_lo; } ;
struct TYPE_4__ {int /*<<< orphan*/  channel; struct b43_phy_n* n; } ;
struct b43_wldev {TYPE_2__ phy; int /*<<< orphan*/  wl; TYPE_1__* dev; } ;
struct b43_phy_n {int /*<<< orphan*/  gain_boost; } ;
struct TYPE_3__ {scalar_t__ board_vendor; scalar_t__ board_type; int board_rev; struct ssb_sprom* bus_sprom; } ;

/* Variables and functions */
 int /*<<< orphan*/  B2055_C1_LNA_GAINBST ; 
 int /*<<< orphan*/  B2055_C1_RX_BB_LPF ; 
 int /*<<< orphan*/  B2055_C1_RX_BB_MIDACHP ; 
 int /*<<< orphan*/  B2055_C1_RX_BB_REG ; 
 int /*<<< orphan*/  B2055_C1_RX_RFSPC1 ; 
 int /*<<< orphan*/  B2055_C2_LNA_GAINBST ; 
 int /*<<< orphan*/  B2055_C2_RX_BB_LPF ; 
 int /*<<< orphan*/  B2055_C2_RX_BB_MIDACHP ; 
 int /*<<< orphan*/  B2055_C2_RX_BB_REG ; 
 int /*<<< orphan*/  B2055_C2_RX_RFSPC1 ; 
 int /*<<< orphan*/  B2055_CAL_COUT2 ; 
 int /*<<< orphan*/  B2055_CAL_LPOCTL ; 
 int /*<<< orphan*/  B2055_CAL_MISC ; 
 int /*<<< orphan*/  B2055_MASTER1 ; 
 int /*<<< orphan*/  B2055_RRCCAL_NOPTSEL ; 
 int B43_BFL2_RXBB_INT_REG_DIS ; 
 scalar_t__ PCI_VENDOR_ID_BROADCOM ; 
 scalar_t__ SSB_BOARD_CB2_4321 ; 
 int /*<<< orphan*/  b43_radio_mask (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43_radio_maskset (struct b43_wldev*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  b43_radio_set (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43_radio_wait_value (struct b43_wldev*,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  b43_radio_write (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43_switch_channel (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void b43_radio_init2055_post(struct b43_wldev *dev)
{
	struct b43_phy_n *nphy = dev->phy.n;
	struct ssb_sprom *sprom = dev->dev->bus_sprom;
	bool workaround = false;

	if (sprom->revision < 4)
		workaround = (dev->dev->board_vendor != PCI_VENDOR_ID_BROADCOM
			      && dev->dev->board_type == SSB_BOARD_CB2_4321
			      && dev->dev->board_rev >= 0x41);
	else
		workaround =
			!(sprom->boardflags2_lo & B43_BFL2_RXBB_INT_REG_DIS);

	b43_radio_mask(dev, B2055_MASTER1, 0xFFF3);
	if (workaround) {
		b43_radio_mask(dev, B2055_C1_RX_BB_REG, 0x7F);
		b43_radio_mask(dev, B2055_C2_RX_BB_REG, 0x7F);
	}
	b43_radio_maskset(dev, B2055_RRCCAL_NOPTSEL, 0xFFC0, 0x2C);
	b43_radio_write(dev, B2055_CAL_MISC, 0x3C);
	b43_radio_mask(dev, B2055_CAL_MISC, 0xFFBE);
	b43_radio_set(dev, B2055_CAL_LPOCTL, 0x80);
	b43_radio_set(dev, B2055_CAL_MISC, 0x1);
	msleep(1);
	b43_radio_set(dev, B2055_CAL_MISC, 0x40);
	if (!b43_radio_wait_value(dev, B2055_CAL_COUT2, 0x80, 0x80, 10, 2000))
		b43err(dev->wl, "radio post init timeout\n");
	b43_radio_mask(dev, B2055_CAL_LPOCTL, 0xFF7F);
	b43_switch_channel(dev, dev->phy.channel);
	b43_radio_write(dev, B2055_C1_RX_BB_LPF, 0x9);
	b43_radio_write(dev, B2055_C2_RX_BB_LPF, 0x9);
	b43_radio_write(dev, B2055_C1_RX_BB_MIDACHP, 0x83);
	b43_radio_write(dev, B2055_C2_RX_BB_MIDACHP, 0x83);
	b43_radio_maskset(dev, B2055_C1_LNA_GAINBST, 0xFFF8, 0x6);
	b43_radio_maskset(dev, B2055_C2_LNA_GAINBST, 0xFFF8, 0x6);
	if (!nphy->gain_boost) {
		b43_radio_set(dev, B2055_C1_RX_RFSPC1, 0x2);
		b43_radio_set(dev, B2055_C2_RX_RFSPC1, 0x2);
	} else {
		b43_radio_mask(dev, B2055_C1_RX_RFSPC1, 0xFFFD);
		b43_radio_mask(dev, B2055_C2_RX_RFSPC1, 0xFFFD);
	}
	udelay(2);
}