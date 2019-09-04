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
typedef  scalar_t__ uint ;
typedef  scalar_t__ u8 ;
struct viosrp_crq {scalar_t__ valid; } ;
struct TYPE_2__ {int index; int mask; struct viosrp_crq* base_addr; } ;
struct scsi_info {long flags; int /*<<< orphan*/  dev; int /*<<< orphan*/  dma_dev; TYPE_1__ cmd_q; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 scalar_t__ INVALIDATE_CMD_RESP_EL ; 
 long SCHEDULE_DISCONNECT ; 
 int TRANS_EVENT ; 
 scalar_t__ VALID_TRANS_EVENT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dma_rmb () ; 
 long ibmvscsis_parse_command (struct scsi_info*,struct viosrp_crq*) ; 
 long ibmvscsis_trans_event (struct scsi_info*,struct viosrp_crq*) ; 
 int /*<<< orphan*/  vio_enable_interrupts (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ibmvscsis_poll_cmd_q(struct scsi_info *vscsi)
{
	struct viosrp_crq *crq;
	long rc;
	bool ack = true;
	volatile u8 valid;

	dev_dbg(&vscsi->dev, "poll_cmd_q: flags 0x%x, state 0x%hx, q index %ud\n",
		vscsi->flags, vscsi->state, vscsi->cmd_q.index);

	rc = vscsi->flags & SCHEDULE_DISCONNECT;
	crq = vscsi->cmd_q.base_addr + vscsi->cmd_q.index;
	valid = crq->valid;
	dma_rmb();

	while (valid) {
poll_work:
		vscsi->cmd_q.index =
			(vscsi->cmd_q.index + 1) & vscsi->cmd_q.mask;

		if (!rc) {
			rc = ibmvscsis_parse_command(vscsi, crq);
		} else {
			if ((uint)crq->valid == VALID_TRANS_EVENT) {
				/*
				 * must service the transport layer events even
				 * in an error state, dont break out until all
				 * the consecutive transport events have been
				 * processed
				 */
				rc = ibmvscsis_trans_event(vscsi, crq);
			} else if (vscsi->flags & TRANS_EVENT) {
				/*
				 * if a tranport event has occurred leave
				 * everything but transport events on the queue
				 */
				dev_dbg(&vscsi->dev, "poll_cmd_q, ignoring\n");

				/*
				 * need to decrement the queue index so we can
				 * look at the elment again
				 */
				if (vscsi->cmd_q.index)
					vscsi->cmd_q.index -= 1;
				else
					/*
					 * index is at 0 it just wrapped.
					 * have it index last element in q
					 */
					vscsi->cmd_q.index = vscsi->cmd_q.mask;
				break;
			}
		}

		crq->valid = INVALIDATE_CMD_RESP_EL;

		crq = vscsi->cmd_q.base_addr + vscsi->cmd_q.index;
		valid = crq->valid;
		dma_rmb();
	}

	if (!rc) {
		if (ack) {
			vio_enable_interrupts(vscsi->dma_dev);
			ack = false;
			dev_dbg(&vscsi->dev, "poll_cmd_q, reenabling interrupts\n");
		}
		valid = crq->valid;
		dma_rmb();
		if (valid)
			goto poll_work;
	}

	dev_dbg(&vscsi->dev, "Leaving poll_cmd_q: rc %ld\n", rc);
}