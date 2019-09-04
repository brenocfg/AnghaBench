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
typedef  scalar_t__ u32 ;
struct TYPE_3__ {int bLCKInProgress; } ;
struct odm_dm_struct {int SupportAbility; TYPE_1__ RFCalibrateInfo; scalar_t__* pbScanInProcess; } ;
struct adapter {TYPE_2__* HalData; } ;
struct TYPE_4__ {struct odm_dm_struct odmpriv; } ;

/* Variables and functions */
 int ODM_RF_CALIBRATION ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  phy_lc_calibrate (struct adapter*,int) ; 

void rtl88eu_phy_lc_calibrate(struct adapter *adapt)
{
	bool singletone = false, carrier_sup = false;
	u32 timeout = 2000, timecount = 0;
	struct odm_dm_struct *dm_odm = &adapt->HalData->odmpriv;

	if (!(dm_odm->SupportAbility & ODM_RF_CALIBRATION))
		return;
	if (singletone || carrier_sup)
		return;

	while (*(dm_odm->pbScanInProcess) && timecount < timeout) {
		mdelay(50);
		timecount += 50;
	}

	dm_odm->RFCalibrateInfo.bLCKInProgress = true;

	phy_lc_calibrate(adapt, false);

	dm_odm->RFCalibrateInfo.bLCKInProgress = false;
}