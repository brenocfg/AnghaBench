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
struct fjes_hw {int max_epid; size_t my_epid; TYPE_1__* ep_shm_info; } ;
struct TYPE_2__ {scalar_t__ es_status; scalar_t__ zone; } ;

/* Variables and functions */
 scalar_t__ FJES_ZONING_STATUS_ENABLE ; 
 scalar_t__ FJES_ZONING_ZONE_TYPE_NONE ; 

bool fjes_hw_epid_is_same_zone(struct fjes_hw *hw, int epid)
{
	if (epid >= hw->max_epid)
		return false;

	if ((hw->ep_shm_info[epid].es_status !=
			FJES_ZONING_STATUS_ENABLE) ||
		(hw->ep_shm_info[hw->my_epid].zone ==
			FJES_ZONING_ZONE_TYPE_NONE))
		return false;
	else
		return (hw->ep_shm_info[epid].zone ==
				hw->ep_shm_info[hw->my_epid].zone);
}