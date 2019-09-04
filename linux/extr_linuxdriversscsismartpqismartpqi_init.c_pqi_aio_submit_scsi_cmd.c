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
struct scsi_cmnd {int /*<<< orphan*/  cmd_len; int /*<<< orphan*/  cmnd; } ;
struct pqi_scsi_dev {int /*<<< orphan*/  aio_handle; } ;
struct pqi_queue_group {int dummy; } ;
struct pqi_ctrl_info {int dummy; } ;

/* Variables and functions */
 int pqi_aio_submit_io (struct pqi_ctrl_info*,struct scsi_cmnd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pqi_queue_group*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline int pqi_aio_submit_scsi_cmd(struct pqi_ctrl_info *ctrl_info,
	struct pqi_scsi_dev *device, struct scsi_cmnd *scmd,
	struct pqi_queue_group *queue_group)
{
	return pqi_aio_submit_io(ctrl_info, scmd, device->aio_handle,
		scmd->cmnd, scmd->cmd_len, queue_group, NULL, false);
}