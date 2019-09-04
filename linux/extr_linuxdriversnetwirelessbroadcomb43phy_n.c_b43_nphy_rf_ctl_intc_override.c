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
struct TYPE_2__ {int rev; } ;
struct b43_wldev {int /*<<< orphan*/  wl; TYPE_1__ phy; } ;
typedef  enum n_intc_override { ____Placeholder_n_intc_override } n_intc_override ;

/* Variables and functions */
 int B43_NPHY_RFCTL_CMD ; 
 int B43_NPHY_RFCTL_CMD_RXTX ; 
 int B43_NPHY_RFCTL_CMD_START ; 
 int B43_NPHY_RFCTL_INTC1 ; 
 int B43_NPHY_RFCTL_INTC2 ; 
 int B43_NPHY_RFCTL_OVER ; 
 int B43_NPHY_TXF_40CO_B1S1 ; 
 int /*<<< orphan*/  B43_RFSEQ_RESET2RX ; 
 int /*<<< orphan*/  B43_WARN_ON (int) ; 
 int /*<<< orphan*/  NL80211_BAND_5GHZ ; 
#define  N_INTC_OVERRIDE_EXT_LNA_GAIN 132 
#define  N_INTC_OVERRIDE_EXT_LNA_PU 131 
#define  N_INTC_OVERRIDE_OFF 130 
#define  N_INTC_OVERRIDE_PA 129 
#define  N_INTC_OVERRIDE_TRSW 128 
 int /*<<< orphan*/  b43_current_band (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_nphy_force_rf_sequence (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_nphy_rf_ctl_intc_override_rev7 (struct b43_wldev*,int,int,int) ; 
 int /*<<< orphan*/  b43_phy_mask (struct b43_wldev*,int,int) ; 
 int /*<<< orphan*/  b43_phy_maskset (struct b43_wldev*,int,int,int) ; 
 int b43_phy_read (struct b43_wldev*,int) ; 
 int /*<<< orphan*/  b43_phy_set (struct b43_wldev*,int,int) ; 
 int /*<<< orphan*/  b43_phy_write (struct b43_wldev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void b43_nphy_rf_ctl_intc_override(struct b43_wldev *dev,
					  enum n_intc_override intc_override,
					  u16 value, u8 core)
{
	u8 i, j;
	u16 reg, tmp, val;

	if (dev->phy.rev >= 7) {
		b43_nphy_rf_ctl_intc_override_rev7(dev, intc_override, value,
						   core);
		return;
	}

	B43_WARN_ON(dev->phy.rev < 3);

	for (i = 0; i < 2; i++) {
		if ((core == 1 && i == 1) || (core == 2 && !i))
			continue;

		reg = (i == 0) ?
			B43_NPHY_RFCTL_INTC1 : B43_NPHY_RFCTL_INTC2;
		b43_phy_set(dev, reg, 0x400);

		switch (intc_override) {
		case N_INTC_OVERRIDE_OFF:
			b43_phy_write(dev, reg, 0);
			b43_nphy_force_rf_sequence(dev, B43_RFSEQ_RESET2RX);
			break;
		case N_INTC_OVERRIDE_TRSW:
			if (!i) {
				b43_phy_maskset(dev, B43_NPHY_RFCTL_INTC1,
						0xFC3F, (value << 6));
				b43_phy_maskset(dev, B43_NPHY_TXF_40CO_B1S1,
						0xFFFE, 1);
				b43_phy_set(dev, B43_NPHY_RFCTL_CMD,
						B43_NPHY_RFCTL_CMD_START);
				for (j = 0; j < 100; j++) {
					if (!(b43_phy_read(dev, B43_NPHY_RFCTL_CMD) & B43_NPHY_RFCTL_CMD_START)) {
						j = 0;
						break;
					}
					udelay(10);
				}
				if (j)
					b43err(dev->wl,
						"intc override timeout\n");
				b43_phy_mask(dev, B43_NPHY_TXF_40CO_B1S1,
						0xFFFE);
			} else {
				b43_phy_maskset(dev, B43_NPHY_RFCTL_INTC2,
						0xFC3F, (value << 6));
				b43_phy_maskset(dev, B43_NPHY_RFCTL_OVER,
						0xFFFE, 1);
				b43_phy_set(dev, B43_NPHY_RFCTL_CMD,
						B43_NPHY_RFCTL_CMD_RXTX);
				for (j = 0; j < 100; j++) {
					if (!(b43_phy_read(dev, B43_NPHY_RFCTL_CMD) & B43_NPHY_RFCTL_CMD_RXTX)) {
						j = 0;
						break;
					}
					udelay(10);
				}
				if (j)
					b43err(dev->wl,
						"intc override timeout\n");
				b43_phy_mask(dev, B43_NPHY_RFCTL_OVER,
						0xFFFE);
			}
			break;
		case N_INTC_OVERRIDE_PA:
			if (b43_current_band(dev->wl) == NL80211_BAND_5GHZ) {
				tmp = 0x0020;
				val = value << 5;
			} else {
				tmp = 0x0010;
				val = value << 4;
			}
			b43_phy_maskset(dev, reg, ~tmp, val);
			break;
		case N_INTC_OVERRIDE_EXT_LNA_PU:
			if (b43_current_band(dev->wl) == NL80211_BAND_5GHZ) {
				tmp = 0x0001;
				val = value;
			} else {
				tmp = 0x0004;
				val = value << 2;
			}
			b43_phy_maskset(dev, reg, ~tmp, val);
			break;
		case N_INTC_OVERRIDE_EXT_LNA_GAIN:
			if (b43_current_band(dev->wl) == NL80211_BAND_5GHZ) {
				tmp = 0x0002;
				val = value << 1;
			} else {
				tmp = 0x0008;
				val = value << 3;
			}
			b43_phy_maskset(dev, reg, ~tmp, val);
			break;
		}
	}
}