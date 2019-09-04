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
struct phy_dm_struct {int /*<<< orphan*/  pre_dbg_priority; } ;

/* Variables and functions */
 int /*<<< orphan*/  BB_DBGPORT_RELEASE ; 
 int /*<<< orphan*/  ODM_COMP_API ; 
 int /*<<< orphan*/  ODM_RT_TRACE (struct phy_dm_struct*,int /*<<< orphan*/ ,char*) ; 

void phydm_release_bb_dbg_port(void *dm_void)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;

	dm->pre_dbg_priority = BB_DBGPORT_RELEASE;
	ODM_RT_TRACE(dm, ODM_COMP_API, "Release BB dbg_port\n");
}