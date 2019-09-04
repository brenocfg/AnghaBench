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
typedef  int u8 ;
struct phy_dm_struct {int adaptivity_igi_upper; int dc_backoff; } ;

/* Variables and functions */

__attribute__((used)) static bool phydm_re_search_condition(void *dm_void)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;
	u8 adaptivity_igi_upper;
	u8 count = 0;

	adaptivity_igi_upper = dm->adaptivity_igi_upper + dm->dc_backoff;

	if (adaptivity_igi_upper <= 0x26 && count < 3) {
		count = count + 1;
		return true;
	}

	return false;
}