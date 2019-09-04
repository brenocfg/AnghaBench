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
struct pqi_ctrl_info {int block_requests; int /*<<< orphan*/  scsi_host; int /*<<< orphan*/  block_requests_wait; } ;

/* Variables and functions */
 int /*<<< orphan*/  pqi_retry_raid_bypass_requests (struct pqi_ctrl_info*) ; 
 int /*<<< orphan*/  scsi_unblock_requests (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void pqi_ctrl_unblock_requests(struct pqi_ctrl_info *ctrl_info)
{
	ctrl_info->block_requests = false;
	wake_up_all(&ctrl_info->block_requests_wait);
	pqi_retry_raid_bypass_requests(ctrl_info);
	scsi_unblock_requests(ctrl_info->scsi_host);
}