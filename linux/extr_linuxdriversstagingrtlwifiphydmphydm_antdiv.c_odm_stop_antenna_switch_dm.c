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
struct phy_dm_struct {int /*<<< orphan*/  support_ability; } ;

/* Variables and functions */
 int /*<<< orphan*/  ODM_BB_ANT_DIV ; 
 int /*<<< orphan*/  ODM_COMP_ANT_DIV ; 
 int /*<<< orphan*/  ODM_RT_TRACE (struct phy_dm_struct*,int /*<<< orphan*/ ,char*) ; 

void odm_stop_antenna_switch_dm(void *dm_void)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;

	/* disable ODM antenna diversity */
	dm->support_ability &= ~ODM_BB_ANT_DIV;
	ODM_RT_TRACE(dm, ODM_COMP_ANT_DIV, "STOP Antenna Diversity\n");
}