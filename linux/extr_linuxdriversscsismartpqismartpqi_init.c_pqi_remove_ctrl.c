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
struct pqi_ctrl_info {scalar_t__ pqi_mode_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  pqi_cancel_rescan_worker (struct pqi_ctrl_info*) ; 
 int /*<<< orphan*/  pqi_cancel_update_time_worker (struct pqi_ctrl_info*) ; 
 int /*<<< orphan*/  pqi_free_ctrl_resources (struct pqi_ctrl_info*) ; 
 int /*<<< orphan*/  pqi_remove_all_scsi_devices (struct pqi_ctrl_info*) ; 
 int /*<<< orphan*/  pqi_revert_to_sis_mode (struct pqi_ctrl_info*) ; 
 int /*<<< orphan*/  pqi_unregister_scsi (struct pqi_ctrl_info*) ; 

__attribute__((used)) static void pqi_remove_ctrl(struct pqi_ctrl_info *ctrl_info)
{
	pqi_cancel_rescan_worker(ctrl_info);
	pqi_cancel_update_time_worker(ctrl_info);
	pqi_remove_all_scsi_devices(ctrl_info);
	pqi_unregister_scsi(ctrl_info);
	if (ctrl_info->pqi_mode_enabled)
		pqi_revert_to_sis_mode(ctrl_info);
	pqi_free_ctrl_resources(ctrl_info);
}