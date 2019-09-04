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
struct b43legacy_phy {int txpwr_offset; } ;
struct b43legacy_wldev {struct b43legacy_phy phy; } ;

/* Variables and functions */
 int b43legacy_get_txgain_base_band (int) ; 
 int b43legacy_get_txgain_dac (int) ; 
 int b43legacy_get_txgain_freq_power_amp (int) ; 
 int b43legacy_ilt_read (struct b43legacy_wldev*,int) ; 
 int /*<<< orphan*/  b43legacy_ilt_write (struct b43legacy_wldev*,int,int) ; 
 int /*<<< orphan*/  b43legacy_phy_write (struct b43legacy_wldev*,int,int) ; 
 int clamp_val (int,int /*<<< orphan*/ ,int) ; 

void b43legacy_radio_set_txpower_a(struct b43legacy_wldev *dev, u16 txpower)
{
	struct b43legacy_phy *phy = &dev->phy;
	u16 pamp;
	u16 base;
	u16 dac;
	u16 ilt;

	txpower = clamp_val(txpower, 0, 63);

	pamp = b43legacy_get_txgain_freq_power_amp(txpower);
	pamp <<= 5;
	pamp &= 0x00E0;
	b43legacy_phy_write(dev, 0x0019, pamp);

	base = b43legacy_get_txgain_base_band(txpower);
	base &= 0x000F;
	b43legacy_phy_write(dev, 0x0017, base | 0x0020);

	ilt = b43legacy_ilt_read(dev, 0x3001);
	ilt &= 0x0007;

	dac = b43legacy_get_txgain_dac(txpower);
	dac <<= 3;
	dac |= ilt;

	b43legacy_ilt_write(dev, 0x3001, dac);

	phy->txpwr_offset = txpower;

	/* TODO: FuncPlaceholder (Adjust BB loft cancel) */
}