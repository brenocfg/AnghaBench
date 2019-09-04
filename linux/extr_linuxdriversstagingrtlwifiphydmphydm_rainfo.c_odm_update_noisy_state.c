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
struct phy_dm_struct {scalar_t__ support_ic_type; int is_noisy_state; } ;

/* Variables and functions */
 scalar_t__ ODM_RTL8188E ; 
 scalar_t__ ODM_RTL8192E ; 
 scalar_t__ ODM_RTL8710B ; 
 scalar_t__ ODM_RTL8723B ; 
 scalar_t__ ODM_RTL8723D ; 
 scalar_t__ ODM_RTL8812 ; 
 scalar_t__ ODM_RTL8821 ; 
 int /*<<< orphan*/  odm_set_ra_dm_arfb_by_noisy (struct phy_dm_struct*) ; 

void odm_update_noisy_state(void *dm_void, bool is_noisy_state_from_c2h)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;

	/* JJ ADD 20161014 */
	if (dm->support_ic_type == ODM_RTL8821 ||
	    dm->support_ic_type == ODM_RTL8812 ||
	    dm->support_ic_type == ODM_RTL8723B ||
	    dm->support_ic_type == ODM_RTL8192E ||
	    dm->support_ic_type == ODM_RTL8188E ||
	    dm->support_ic_type == ODM_RTL8723D ||
	    dm->support_ic_type == ODM_RTL8710B)
		dm->is_noisy_state = is_noisy_state_from_c2h;
	odm_set_ra_dm_arfb_by_noisy(dm);
}