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
typedef  scalar_t__ u8 ;
struct odm_rate_adaptive {scalar_t__ high_rssi_thresh; scalar_t__ low_rssi_thresh; } ;
struct phy_dm_struct {struct odm_rate_adaptive rate_adaptive; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
#define  DM_RATR_STA_HIGH 131 
#define  DM_RATR_STA_INIT 130 
#define  DM_RATR_STA_LOW 129 
#define  DM_RATR_STA_MIDDLE 128 
 int /*<<< orphan*/  ODM_COMP_RA_MASK ; 
 int /*<<< orphan*/  ODM_RT_TRACE (struct phy_dm_struct*,int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*,scalar_t__) ; 

bool odm_ra_state_check(void *dm_void, s32 rssi, bool is_force_update,
			u8 *ra_tr_state)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;
	struct odm_rate_adaptive *ra = &dm->rate_adaptive;
	const u8 go_up_gap = 5;
	u8 high_rssi_thresh_for_ra = ra->high_rssi_thresh;
	u8 low_rssi_thresh_for_ra = ra->low_rssi_thresh;
	u8 ratr_state;

	ODM_RT_TRACE(dm, ODM_COMP_RA_MASK,
		     "RSSI= (( %d )), Current_RSSI_level = (( %d ))\n", rssi,
		     *ra_tr_state);
	ODM_RT_TRACE(dm, ODM_COMP_RA_MASK,
		     "[Ori RA RSSI Thresh]  High= (( %d )), Low = (( %d ))\n",
		     high_rssi_thresh_for_ra, low_rssi_thresh_for_ra);
	/* threshold Adjustment:
	 * when RSSI state trends to go up one or two levels, make sure RSSI is
	 * high enough. Here go_up_gap is added to solve the boundary's level
	 * alternation issue.
	 */

	switch (*ra_tr_state) {
	case DM_RATR_STA_INIT:
	case DM_RATR_STA_HIGH:
		break;

	case DM_RATR_STA_MIDDLE:
		high_rssi_thresh_for_ra += go_up_gap;
		break;

	case DM_RATR_STA_LOW:
		high_rssi_thresh_for_ra += go_up_gap;
		low_rssi_thresh_for_ra += go_up_gap;
		break;

	default:
		WARN_ONCE(true, "wrong rssi level setting %d !", *ra_tr_state);
		break;
	}

	/* Decide ratr_state by RSSI.*/
	if (rssi > high_rssi_thresh_for_ra)
		ratr_state = DM_RATR_STA_HIGH;
	else if (rssi > low_rssi_thresh_for_ra)
		ratr_state = DM_RATR_STA_MIDDLE;

	else
		ratr_state = DM_RATR_STA_LOW;
	ODM_RT_TRACE(dm, ODM_COMP_RA_MASK,
		     "[Mod RA RSSI Thresh]  High= (( %d )), Low = (( %d ))\n",
		     high_rssi_thresh_for_ra, low_rssi_thresh_for_ra);

	if (*ra_tr_state != ratr_state || is_force_update) {
		ODM_RT_TRACE(dm, ODM_COMP_RA_MASK,
			     "[RSSI Level Update] %d->%d\n", *ra_tr_state,
			     ratr_state);
		*ra_tr_state = ratr_state;
		return true;
	}

	return false;
}