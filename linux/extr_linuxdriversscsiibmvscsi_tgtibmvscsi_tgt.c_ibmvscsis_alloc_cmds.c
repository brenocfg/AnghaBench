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
struct scsi_info {int /*<<< orphan*/  free_cmd; scalar_t__ cmd_pool; } ;
struct ibmvscsis_cmd {int /*<<< orphan*/  list; int /*<<< orphan*/  work; struct scsi_info* adapter; int /*<<< orphan*/ * abort_cmd; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibmvscsis_scheduler ; 
 scalar_t__ kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ibmvscsis_alloc_cmds(struct scsi_info *vscsi, int num)
{
	struct ibmvscsis_cmd *cmd;
	int i;

	INIT_LIST_HEAD(&vscsi->free_cmd);
	vscsi->cmd_pool = kcalloc(num, sizeof(struct ibmvscsis_cmd),
				  GFP_KERNEL);
	if (!vscsi->cmd_pool)
		return -ENOMEM;

	for (i = 0, cmd = (struct ibmvscsis_cmd *)vscsi->cmd_pool; i < num;
	     i++, cmd++) {
		cmd->abort_cmd = NULL;
		cmd->adapter = vscsi;
		INIT_WORK(&cmd->work, ibmvscsis_scheduler);
		list_add_tail(&cmd->list, &vscsi->free_cmd);
	}

	return 0;
}