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
typedef  int uint ;
typedef  int /*<<< orphan*/  u16 ;
struct brcms_phy_pub {int dummy; } ;
struct brcms_phy_lcnphy {int lcnphy_cal_counter; int /*<<< orphan*/  lcnphy_cal_temper; } ;
struct TYPE_2__ {struct brcms_phy_lcnphy* pi_lcnphy; } ;
struct brcms_phy {TYPE_1__ u; } ;

/* Variables and functions */
#define  LCNPHY_PERICAL_TEMPBASED_TXPWRCTRL 132 
 int LCNPHY_TEMPSENSE (int /*<<< orphan*/ ) ; 
#define  PHY_FULLCAL 131 
#define  PHY_PERICAL_CHAN 130 
#define  PHY_PERICAL_PHYINIT 129 
#define  PHY_PERICAL_WATCHDOG 128 
 int /*<<< orphan*/  wlc_2064_vco_cal (struct brcms_phy*) ; 
 int /*<<< orphan*/  wlc_lcnphy_glacial_timer_based_cal (struct brcms_phy*) ; 
 int /*<<< orphan*/  wlc_lcnphy_periodic_cal (struct brcms_phy*) ; 
 int /*<<< orphan*/  wlc_lcnphy_tempsense (struct brcms_phy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlc_lcnphy_tempsense_based_pwr_ctrl_enabled (struct brcms_phy*) ; 
 int /*<<< orphan*/  wlc_lcnphy_tx_power_adjustment (struct brcms_phy_pub*) ; 

void wlc_lcnphy_calib_modes(struct brcms_phy *pi, uint mode)
{
	u16 temp_new;
	int temp1, temp2, temp_diff;
	struct brcms_phy_lcnphy *pi_lcn = pi->u.pi_lcnphy;

	switch (mode) {
	case PHY_PERICAL_CHAN:
		break;
	case PHY_FULLCAL:
		wlc_lcnphy_periodic_cal(pi);
		break;
	case PHY_PERICAL_PHYINIT:
		wlc_lcnphy_periodic_cal(pi);
		break;
	case PHY_PERICAL_WATCHDOG:
		if (wlc_lcnphy_tempsense_based_pwr_ctrl_enabled(pi)) {
			temp_new = wlc_lcnphy_tempsense(pi, 0);
			temp1 = LCNPHY_TEMPSENSE(temp_new);
			temp2 = LCNPHY_TEMPSENSE(pi_lcn->lcnphy_cal_temper);
			temp_diff = temp1 - temp2;
			if ((pi_lcn->lcnphy_cal_counter > 90) ||
			    (temp_diff > 60) || (temp_diff < -60)) {
				wlc_lcnphy_glacial_timer_based_cal(pi);
				wlc_2064_vco_cal(pi);
				pi_lcn->lcnphy_cal_temper = temp_new;
				pi_lcn->lcnphy_cal_counter = 0;
			} else
				pi_lcn->lcnphy_cal_counter++;
		}
		break;
	case LCNPHY_PERICAL_TEMPBASED_TXPWRCTRL:
		if (wlc_lcnphy_tempsense_based_pwr_ctrl_enabled(pi))
			wlc_lcnphy_tx_power_adjustment(
				(struct brcms_phy_pub *) pi);
		break;
	}
}