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
struct brcms_phy {int /*<<< orphan*/  phycal_timer; TYPE_1__* sh; } ;
struct TYPE_2__ {int /*<<< orphan*/  up; } ;

/* Variables and functions */
 int /*<<< orphan*/  PHY_PERICAL_AUTO ; 
 scalar_t__ PHY_PERICAL_MPHASE_PENDING (struct brcms_phy*) ; 
 scalar_t__ PLT_INPROG_PHY (struct brcms_phy*) ; 
 scalar_t__ SCAN_RM_IN_PROGRESS (struct brcms_phy*) ; 
 int /*<<< orphan*/  wlapi_add_timer (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlc_phy_cal_perical_mphase_reset (struct brcms_phy*) ; 
 int /*<<< orphan*/  wlc_phy_cal_perical_mphase_restart (struct brcms_phy*) ; 
 int /*<<< orphan*/  wlc_phy_cal_perical_nphy_run (struct brcms_phy*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wlc_phy_timercb_phycal(struct brcms_phy *pi)
{
	uint delay = 5;

	if (PHY_PERICAL_MPHASE_PENDING(pi)) {
		if (!pi->sh->up) {
			wlc_phy_cal_perical_mphase_reset(pi);
			return;
		}

		if (SCAN_RM_IN_PROGRESS(pi) || PLT_INPROG_PHY(pi)) {

			delay = 1000;
			wlc_phy_cal_perical_mphase_restart(pi);
		} else
			wlc_phy_cal_perical_nphy_run(pi, PHY_PERICAL_AUTO);
		wlapi_add_timer(pi->phycal_timer, delay, 0);
		return;
	}

}