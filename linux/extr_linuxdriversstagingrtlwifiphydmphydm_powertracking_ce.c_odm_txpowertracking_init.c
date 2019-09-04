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
struct phy_dm_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  odm_txpowertracking_thermal_meter_init (struct phy_dm_struct*) ; 

void odm_txpowertracking_init(void *dm_void)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;

	odm_txpowertracking_thermal_meter_init(dm);
}