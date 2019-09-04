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
struct lpphy_tx_gains {int dummy; } ;
struct TYPE_3__ {struct b43_phy_lp* lp; } ;
struct b43_wldev {TYPE_2__* dev; TYPE_1__ phy; } ;
struct b43_phy_lp {int txpctl_mode; } ;
struct TYPE_4__ {int chip_id; scalar_t__ chip_rev; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43_LPPHY_AFE_CTL_OVR ; 
 int /*<<< orphan*/  B43_LPPHY_RF_PWR_OVERRIDE ; 
 int B43_LPPHY_TXPCTL_OFF ; 
 int /*<<< orphan*/  b43_phy_maskset (struct b43_wldev*,int /*<<< orphan*/ ,int,int) ; 
 int b43_phy_read (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 int lpphy_get_bb_mult (struct b43_wldev*) ; 
 struct lpphy_tx_gains lpphy_get_tx_gains (struct b43_wldev*) ; 
 int /*<<< orphan*/  lpphy_papd_cal (struct b43_wldev*,struct lpphy_tx_gains,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  lpphy_read_tx_pctl_mode_from_hardware (struct b43_wldev*) ; 
 int /*<<< orphan*/  lpphy_set_bb_mult (struct b43_wldev*,int) ; 
 int /*<<< orphan*/  lpphy_set_tx_gains (struct b43_wldev*,struct lpphy_tx_gains) ; 
 int /*<<< orphan*/  lpphy_set_tx_power_control (struct b43_wldev*,int) ; 

__attribute__((used)) static void lpphy_papd_cal_txpwr(struct b43_wldev *dev)
{
	struct b43_phy_lp *lpphy = dev->phy.lp;
	struct lpphy_tx_gains gains, oldgains;
	int old_txpctl, old_afe_ovr, old_rf, old_bbmult;

	lpphy_read_tx_pctl_mode_from_hardware(dev);
	old_txpctl = lpphy->txpctl_mode;
	old_afe_ovr = b43_phy_read(dev, B43_LPPHY_AFE_CTL_OVR) & 0x40;
	if (old_afe_ovr)
		oldgains = lpphy_get_tx_gains(dev);
	old_rf = b43_phy_read(dev, B43_LPPHY_RF_PWR_OVERRIDE) & 0xFF;
	old_bbmult = lpphy_get_bb_mult(dev);

	lpphy_set_tx_power_control(dev, B43_LPPHY_TXPCTL_OFF);

	if (dev->dev->chip_id == 0x4325 && dev->dev->chip_rev == 0)
		lpphy_papd_cal(dev, gains, 0, 1, 30);
	else
		lpphy_papd_cal(dev, gains, 0, 1, 65);

	if (old_afe_ovr)
		lpphy_set_tx_gains(dev, oldgains);
	lpphy_set_bb_mult(dev, old_bbmult);
	lpphy_set_tx_power_control(dev, old_txpctl);
	b43_phy_maskset(dev, B43_LPPHY_RF_PWR_OVERRIDE, 0xFF00, old_rf);
}