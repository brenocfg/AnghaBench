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
struct TYPE_2__ {int rev; struct b43_phy_lp* lp; } ;
struct b43_wldev {TYPE_1__ phy; } ;
struct b43_phy_lp {scalar_t__ full_calib_chan; scalar_t__ channel; int txpctl_mode; } ;
typedef  enum b43_lpphy_txpctl_mode { ____Placeholder_b43_lpphy_txpctl_mode } b43_lpphy_txpctl_mode ;

/* Variables and functions */
 int B43_LPPHY_TXPCTL_OFF ; 
 int /*<<< orphan*/  b43_mac_enable (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_mac_suspend (struct b43_wldev*) ; 
 int /*<<< orphan*/  lpphy_btcoex_override (struct b43_wldev*) ; 
 int /*<<< orphan*/  lpphy_papd_cal_txpwr (struct b43_wldev*) ; 
 int /*<<< orphan*/  lpphy_pr41573_workaround (struct b43_wldev*) ; 
 int /*<<< orphan*/  lpphy_read_tx_pctl_mode_from_hardware (struct b43_wldev*) ; 
 int /*<<< orphan*/  lpphy_restore_dig_flt_state (struct b43_wldev*) ; 
 int /*<<< orphan*/  lpphy_rx_iq_cal (struct b43_wldev*,int,int,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lpphy_save_dig_flt_state (struct b43_wldev*) ; 
 int /*<<< orphan*/  lpphy_set_tx_power_control (struct b43_wldev*,int) ; 

__attribute__((used)) static void lpphy_calibration(struct b43_wldev *dev)
{
	struct b43_phy_lp *lpphy = dev->phy.lp;
	enum b43_lpphy_txpctl_mode saved_pctl_mode;
	bool full_cal = false;

	if (lpphy->full_calib_chan != lpphy->channel) {
		full_cal = true;
		lpphy->full_calib_chan = lpphy->channel;
	}

	b43_mac_suspend(dev);

	lpphy_btcoex_override(dev);
	if (dev->phy.rev >= 2)
		lpphy_save_dig_flt_state(dev);
	lpphy_read_tx_pctl_mode_from_hardware(dev);
	saved_pctl_mode = lpphy->txpctl_mode;
	lpphy_set_tx_power_control(dev, B43_LPPHY_TXPCTL_OFF);
	//TODO Perform transmit power table I/Q LO calibration
	if ((dev->phy.rev == 0) && (saved_pctl_mode != B43_LPPHY_TXPCTL_OFF))
		lpphy_pr41573_workaround(dev);
	if ((dev->phy.rev >= 2) && full_cal) {
		lpphy_papd_cal_txpwr(dev);
	}
	lpphy_set_tx_power_control(dev, saved_pctl_mode);
	if (dev->phy.rev >= 2)
		lpphy_restore_dig_flt_state(dev);
	lpphy_rx_iq_cal(dev, true, true, false, false, NULL);

	b43_mac_enable(dev);
}