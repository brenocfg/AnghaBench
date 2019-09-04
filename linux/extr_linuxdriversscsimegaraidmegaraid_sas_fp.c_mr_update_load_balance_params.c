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
typedef  int u16 ;
struct MR_LD_RAID {int level; scalar_t__ ldState; } ;
struct MR_DRV_RAID_MAP_ALL {int dummy; } ;
struct LD_LOAD_BALANCE_INFO {int loadBalanceFlag; } ;

/* Variables and functions */
 int LB_PENDING_CMDS_DEFAULT ; 
 int MAX_LOGICAL_DRIVES_EXT ; 
 scalar_t__ MR_LD_STATE_OPTIMAL ; 
 struct MR_LD_RAID* MR_LdRaidGet (int,struct MR_DRV_RAID_MAP_ALL*) ; 
 int MR_TargetIdToLdGet (int,struct MR_DRV_RAID_MAP_ALL*) ; 
 int lb_pending_cmds ; 

void mr_update_load_balance_params(struct MR_DRV_RAID_MAP_ALL *drv_map,
	struct LD_LOAD_BALANCE_INFO *lbInfo)
{
	int ldCount;
	u16 ld;
	struct MR_LD_RAID *raid;

	if (lb_pending_cmds > 128 || lb_pending_cmds < 1)
		lb_pending_cmds = LB_PENDING_CMDS_DEFAULT;

	for (ldCount = 0; ldCount < MAX_LOGICAL_DRIVES_EXT; ldCount++) {
		ld = MR_TargetIdToLdGet(ldCount, drv_map);
		if (ld >= MAX_LOGICAL_DRIVES_EXT - 1) {
			lbInfo[ldCount].loadBalanceFlag = 0;
			continue;
		}

		raid = MR_LdRaidGet(ld, drv_map);
		if ((raid->level != 1) ||
			(raid->ldState != MR_LD_STATE_OPTIMAL)) {
			lbInfo[ldCount].loadBalanceFlag = 0;
			continue;
		}
		lbInfo[ldCount].loadBalanceFlag = 1;
	}
}