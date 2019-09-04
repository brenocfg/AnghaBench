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
struct scsi_info {int debit; int flags; int /*<<< orphan*/  wait_idle; int /*<<< orphan*/  waiting_rsp; int /*<<< orphan*/  schedule_q; int /*<<< orphan*/  active_q; int /*<<< orphan*/  free_cmd; int /*<<< orphan*/  dev; } ;
struct iu_entry {int dummy; } ;
struct ibmvscsis_cmd {int type; int /*<<< orphan*/  list; struct iu_entry* iue; } ;

/* Variables and functions */
#define  ADAPTER_MAD 131 
 int PROCESSING_MAD ; 
#define  SCSI_CDB 130 
#define  TASK_MANAGEMENT 129 
#define  UNSET_TYPE 128 
 int WAIT_FOR_IDLE ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  srp_iu_put (struct iu_entry*) ; 

__attribute__((used)) static void ibmvscsis_free_cmd_resources(struct scsi_info *vscsi,
					 struct ibmvscsis_cmd *cmd)
{
	struct iu_entry *iue = cmd->iue;

	switch (cmd->type) {
	case TASK_MANAGEMENT:
	case SCSI_CDB:
		/*
		 * When the queue goes down this value is cleared, so it
		 * cannot be cleared in this general purpose function.
		 */
		if (vscsi->debit)
			vscsi->debit -= 1;
		break;
	case ADAPTER_MAD:
		vscsi->flags &= ~PROCESSING_MAD;
		break;
	case UNSET_TYPE:
		break;
	default:
		dev_err(&vscsi->dev, "free_cmd_resources unknown type %d\n",
			cmd->type);
		break;
	}

	cmd->iue = NULL;
	list_add_tail(&cmd->list, &vscsi->free_cmd);
	srp_iu_put(iue);

	if (list_empty(&vscsi->active_q) && list_empty(&vscsi->schedule_q) &&
	    list_empty(&vscsi->waiting_rsp) && (vscsi->flags & WAIT_FOR_IDLE)) {
		vscsi->flags &= ~WAIT_FOR_IDLE;
		complete(&vscsi->wait_idle);
	}
}