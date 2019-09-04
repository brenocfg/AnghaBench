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
struct brcms_phy {scalar_t__ mphase_txcal_cmdidx; int /*<<< orphan*/  mphase_cal_phase_id; int /*<<< orphan*/  cal_type_override; int /*<<< orphan*/  phycal_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPHASE_CAL_STATE_IDLE ; 
 int /*<<< orphan*/  PHY_PERICAL_AUTO ; 
 int /*<<< orphan*/  wlapi_del_timer (int /*<<< orphan*/ ) ; 

void wlc_phy_cal_perical_mphase_reset(struct brcms_phy *pi)
{
	wlapi_del_timer(pi->phycal_timer);

	pi->cal_type_override = PHY_PERICAL_AUTO;
	pi->mphase_cal_phase_id = MPHASE_CAL_STATE_IDLE;
	pi->mphase_txcal_cmdidx = 0;
}