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
typedef  int u16 ;
struct TYPE_3__ {struct b43_phy_lp* lp; } ;
struct b43_wldev {TYPE_2__* dev; int /*<<< orphan*/  wl; TYPE_1__ phy; } ;
struct b43_phy_lp {int rx_pwr_offset; int rssi_vf; scalar_t__ rssi_vc; scalar_t__ rssi_gs; } ;
struct TYPE_4__ {int board_rev; int chip_id; scalar_t__ chip_rev; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43_LPPHY_ADC_COMPENSATION_CTL ; 
 int /*<<< orphan*/  B43_LPPHY_AFE_ADC_CTL_0 ; 
 int /*<<< orphan*/  B43_LPPHY_AFE_ADC_CTL_1 ; 
 int /*<<< orphan*/  B43_LPPHY_AFE_CTL ; 
 int /*<<< orphan*/  B43_LPPHY_AFE_CTL_OVR ; 
 int /*<<< orphan*/  B43_LPPHY_AFE_CTL_OVRVAL ; 
 int /*<<< orphan*/  B43_LPPHY_AFE_DAC_CTL ; 
 int /*<<< orphan*/  B43_LPPHY_AFE_RSSI_CTL_0 ; 
 int /*<<< orphan*/  B43_LPPHY_AFE_RSSI_CTL_1 ; 
 int /*<<< orphan*/  B43_LPPHY_CLIPCTRTHRESH ; 
 int /*<<< orphan*/  B43_LPPHY_CLIPTHRESH ; 
 int /*<<< orphan*/  B43_LPPHY_CRSGAIN_CTL ; 
 int /*<<< orphan*/  B43_LPPHY_CRS_ED_THRESH ; 
 int /*<<< orphan*/  B43_LPPHY_DCOFFSETTRANSIENT ; 
 int /*<<< orphan*/  B43_LPPHY_GAINDIRECTMISMATCH ; 
 int /*<<< orphan*/  B43_LPPHY_GAINMISMATCH ; 
 int /*<<< orphan*/  B43_LPPHY_HIGAINDB ; 
 int /*<<< orphan*/  B43_LPPHY_IDLEAFTERPKTRXTO ; 
 int /*<<< orphan*/  B43_LPPHY_INPUT_PWRDB ; 
 int /*<<< orphan*/  B43_LPPHY_LOWGAINDB ; 
 int /*<<< orphan*/  B43_LPPHY_MINPWR_LEVEL ; 
 int /*<<< orphan*/  B43_LPPHY_OFDMSYNCTHRESH0 ; 
 int /*<<< orphan*/  B43_LPPHY_PREAMBLECONFIRMTO ; 
 int /*<<< orphan*/  B43_LPPHY_PWR_THRESH1 ; 
 int /*<<< orphan*/  B43_LPPHY_RESET_CTL ; 
 int /*<<< orphan*/  B43_LPPHY_RF_OVERRIDE_0 ; 
 int /*<<< orphan*/  B43_LPPHY_RF_OVERRIDE_2 ; 
 int /*<<< orphan*/  B43_LPPHY_SYNCPEAKCNT ; 
 int /*<<< orphan*/  B43_LPPHY_TR_LOOKUP_1 ; 
 int /*<<< orphan*/  B43_LPPHY_VERYLOWGAINDB ; 
 int /*<<< orphan*/  B43_LPTAB16 (int,int) ; 
 int /*<<< orphan*/  B43_LPTAB32 (int,int) ; 
 int /*<<< orphan*/  B43_PHY_OFDM (int) ; 
 scalar_t__ NL80211_BAND_2GHZ ; 
 scalar_t__ b43_current_band (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_lptab_write (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43_phy_mask (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43_phy_maskset (struct b43_wldev*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  b43_phy_set (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43_phy_write (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lpphy_save_dig_flt_state (struct b43_wldev*) ; 

__attribute__((used)) static void lpphy_baseband_rev2plus_init(struct b43_wldev *dev)
{
	struct b43_phy_lp *lpphy = dev->phy.lp;

	b43_phy_write(dev, B43_LPPHY_AFE_DAC_CTL, 0x50);
	b43_phy_write(dev, B43_LPPHY_AFE_CTL, 0x8800);
	b43_phy_write(dev, B43_LPPHY_AFE_CTL_OVR, 0);
	b43_phy_write(dev, B43_LPPHY_AFE_CTL_OVRVAL, 0);
	b43_phy_write(dev, B43_LPPHY_RF_OVERRIDE_0, 0);
	b43_phy_write(dev, B43_LPPHY_RF_OVERRIDE_2, 0);
	b43_phy_write(dev, B43_PHY_OFDM(0xF9), 0);
	b43_phy_write(dev, B43_LPPHY_TR_LOOKUP_1, 0);
	b43_phy_set(dev, B43_LPPHY_ADC_COMPENSATION_CTL, 0x10);
	b43_phy_maskset(dev, B43_LPPHY_OFDMSYNCTHRESH0, 0xFF00, 0xB4);
	b43_phy_maskset(dev, B43_LPPHY_DCOFFSETTRANSIENT, 0xF8FF, 0x200);
	b43_phy_maskset(dev, B43_LPPHY_DCOFFSETTRANSIENT, 0xFF00, 0x7F);
	b43_phy_maskset(dev, B43_LPPHY_GAINDIRECTMISMATCH, 0xFF0F, 0x40);
	b43_phy_maskset(dev, B43_LPPHY_PREAMBLECONFIRMTO, 0xFF00, 0x2);
	b43_phy_mask(dev, B43_LPPHY_CRSGAIN_CTL, ~0x4000);
	b43_phy_mask(dev, B43_LPPHY_CRSGAIN_CTL, ~0x2000);
	b43_phy_set(dev, B43_PHY_OFDM(0x10A), 0x1);
	if (dev->dev->board_rev >= 0x18) {
		b43_lptab_write(dev, B43_LPTAB32(17, 65), 0xEC);
		b43_phy_maskset(dev, B43_PHY_OFDM(0x10A), 0xFF01, 0x14);
	} else {
		b43_phy_maskset(dev, B43_PHY_OFDM(0x10A), 0xFF01, 0x10);
	}
	b43_phy_maskset(dev, B43_PHY_OFDM(0xDF), 0xFF00, 0xF4);
	b43_phy_maskset(dev, B43_PHY_OFDM(0xDF), 0x00FF, 0xF100);
	b43_phy_write(dev, B43_LPPHY_CLIPTHRESH, 0x48);
	b43_phy_maskset(dev, B43_LPPHY_HIGAINDB, 0xFF00, 0x46);
	b43_phy_maskset(dev, B43_PHY_OFDM(0xE4), 0xFF00, 0x10);
	b43_phy_maskset(dev, B43_LPPHY_PWR_THRESH1, 0xFFF0, 0x9);
	b43_phy_mask(dev, B43_LPPHY_GAINDIRECTMISMATCH, ~0xF);
	b43_phy_maskset(dev, B43_LPPHY_VERYLOWGAINDB, 0x00FF, 0x5500);
	b43_phy_maskset(dev, B43_LPPHY_CLIPCTRTHRESH, 0xFC1F, 0xA0);
	b43_phy_maskset(dev, B43_LPPHY_GAINDIRECTMISMATCH, 0xE0FF, 0x300);
	b43_phy_maskset(dev, B43_LPPHY_HIGAINDB, 0x00FF, 0x2A00);
	if ((dev->dev->chip_id == 0x4325) && (dev->dev->chip_rev == 0)) {
		b43_phy_maskset(dev, B43_LPPHY_LOWGAINDB, 0x00FF, 0x2100);
		b43_phy_maskset(dev, B43_LPPHY_VERYLOWGAINDB, 0xFF00, 0xA);
	} else {
		b43_phy_maskset(dev, B43_LPPHY_LOWGAINDB, 0x00FF, 0x1E00);
		b43_phy_maskset(dev, B43_LPPHY_VERYLOWGAINDB, 0xFF00, 0xD);
	}
	b43_phy_maskset(dev, B43_PHY_OFDM(0xFE), 0xFFE0, 0x1F);
	b43_phy_maskset(dev, B43_PHY_OFDM(0xFF), 0xFFE0, 0xC);
	b43_phy_maskset(dev, B43_PHY_OFDM(0x100), 0xFF00, 0x19);
	b43_phy_maskset(dev, B43_PHY_OFDM(0xFF), 0x03FF, 0x3C00);
	b43_phy_maskset(dev, B43_PHY_OFDM(0xFE), 0xFC1F, 0x3E0);
	b43_phy_maskset(dev, B43_PHY_OFDM(0xFF), 0xFFE0, 0xC);
	b43_phy_maskset(dev, B43_PHY_OFDM(0x100), 0x00FF, 0x1900);
	b43_phy_maskset(dev, B43_LPPHY_CLIPCTRTHRESH, 0x83FF, 0x5800);
	b43_phy_maskset(dev, B43_LPPHY_CLIPCTRTHRESH, 0xFFE0, 0x12);
	b43_phy_maskset(dev, B43_LPPHY_GAINMISMATCH, 0x0FFF, 0x9000);

	if ((dev->dev->chip_id == 0x4325) && (dev->dev->chip_rev == 0)) {
		b43_lptab_write(dev, B43_LPTAB16(0x08, 0x14), 0);
		b43_lptab_write(dev, B43_LPTAB16(0x08, 0x12), 0x40);
	}

	if (b43_current_band(dev->wl) == NL80211_BAND_2GHZ) {
		b43_phy_set(dev, B43_LPPHY_CRSGAIN_CTL, 0x40);
		b43_phy_maskset(dev, B43_LPPHY_CRSGAIN_CTL, 0xF0FF, 0xB00);
		b43_phy_maskset(dev, B43_LPPHY_SYNCPEAKCNT, 0xFFF8, 0x6);
		b43_phy_maskset(dev, B43_LPPHY_MINPWR_LEVEL, 0x00FF, 0x9D00);
		b43_phy_maskset(dev, B43_LPPHY_MINPWR_LEVEL, 0xFF00, 0xA1);
		b43_phy_mask(dev, B43_LPPHY_IDLEAFTERPKTRXTO, 0x00FF);
	} else /* 5GHz */
		b43_phy_mask(dev, B43_LPPHY_CRSGAIN_CTL, ~0x40);

	b43_phy_maskset(dev, B43_LPPHY_CRS_ED_THRESH, 0xFF00, 0xB3);
	b43_phy_maskset(dev, B43_LPPHY_CRS_ED_THRESH, 0x00FF, 0xAD00);
	b43_phy_maskset(dev, B43_LPPHY_INPUT_PWRDB, 0xFF00, lpphy->rx_pwr_offset);
	b43_phy_set(dev, B43_LPPHY_RESET_CTL, 0x44);
	b43_phy_write(dev, B43_LPPHY_RESET_CTL, 0x80);
	b43_phy_write(dev, B43_LPPHY_AFE_RSSI_CTL_0, 0xA954);
	b43_phy_write(dev, B43_LPPHY_AFE_RSSI_CTL_1,
		      0x2000 | ((u16)lpphy->rssi_gs << 10) |
		      ((u16)lpphy->rssi_vc << 4) | lpphy->rssi_vf);

	if ((dev->dev->chip_id == 0x4325) && (dev->dev->chip_rev == 0)) {
		b43_phy_set(dev, B43_LPPHY_AFE_ADC_CTL_0, 0x1C);
		b43_phy_maskset(dev, B43_LPPHY_AFE_CTL, 0x00FF, 0x8800);
		b43_phy_maskset(dev, B43_LPPHY_AFE_ADC_CTL_1, 0xFC3C, 0x0400);
	}

	lpphy_save_dig_flt_state(dev);
}