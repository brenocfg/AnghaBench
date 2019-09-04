#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_int ;
struct scsi_cmnd {int result; unsigned char* host_scribble; TYPE_3__* device; int /*<<< orphan*/  sc_data_direction; int /*<<< orphan*/  sense_buffer; } ;
struct qlogicpti {int send_marker; size_t res_out_ptr; scalar_t__ qregs; int /*<<< orphan*/ * cmd_count; TYPE_2__* op; int /*<<< orphan*/  qpti_id; struct scsi_cmnd** cmd_slots; int /*<<< orphan*/ * res_cpu; } ;
struct TYPE_4__ {scalar_t__ entry_type; } ;
struct Status_Entry {size_t handle; scalar_t__ completion_status; int status_flags; int state_flags; TYPE_1__ hdr; int /*<<< orphan*/  req_sense_data; } ;
struct TYPE_6__ {size_t id; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  ASYNC_SCSI_BUS_RESET 133 
#define  COMMAND_ERROR 132 
#define  COMMAND_PARAM_ERROR 131 
 scalar_t__ CS_ABORTED ; 
 scalar_t__ CS_RESET_OCCURRED ; 
 int DID_ERROR ; 
 scalar_t__ ENTRY_STATUS ; 
#define  EXECUTION_TIMEOUT_RESET 130 
 scalar_t__ HCCTRL ; 
 size_t HCCTRL_CRIRQ ; 
#define  HOST_INTERFACE_ERROR 129 
#define  INVALID_COMMAND 128 
 scalar_t__ MBOX0 ; 
 scalar_t__ MBOX5 ; 
 size_t NEXT_RES_PTR (size_t) ; 
 scalar_t__ SBUS_SEMAPHORE ; 
 int SBUS_SEMAPHORE_LCK ; 
 scalar_t__ SBUS_STAT ; 
 int SBUS_STAT_RINT ; 
 int /*<<< orphan*/  SCSI_SENSE_BUFFERSIZE ; 
 int SF_GOT_SENSE ; 
 int STF_BUS_RESET ; 
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int qlogicpti_return_status (struct Status_Entry*,int /*<<< orphan*/ ) ; 
 int sbus_readw (scalar_t__) ; 
 int /*<<< orphan*/  sbus_writew (size_t,scalar_t__) ; 
 scalar_t__ scsi_bufflen (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_sg_count (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_sglist (struct scsi_cmnd*) ; 

__attribute__((used)) static struct scsi_cmnd *qlogicpti_intr_handler(struct qlogicpti *qpti)
{
	struct scsi_cmnd *Cmnd, *done_queue = NULL;
	struct Status_Entry *sts;
	u_int in_ptr, out_ptr;

	if (!(sbus_readw(qpti->qregs + SBUS_STAT) & SBUS_STAT_RINT))
		return NULL;
		
	in_ptr = sbus_readw(qpti->qregs + MBOX5);
	sbus_writew(HCCTRL_CRIRQ, qpti->qregs + HCCTRL);
	if (sbus_readw(qpti->qregs + SBUS_SEMAPHORE) & SBUS_SEMAPHORE_LCK) {
		switch (sbus_readw(qpti->qregs + MBOX0)) {
		case ASYNC_SCSI_BUS_RESET:
		case EXECUTION_TIMEOUT_RESET:
			qpti->send_marker = 1;
			break;
		case INVALID_COMMAND:
		case HOST_INTERFACE_ERROR:
		case COMMAND_ERROR:
		case COMMAND_PARAM_ERROR:
			break;
		};
		sbus_writew(0, qpti->qregs + SBUS_SEMAPHORE);
	}

	/* This looks like a network driver! */
	out_ptr = qpti->res_out_ptr;
	while (out_ptr != in_ptr) {
		u_int cmd_slot;

		sts = (struct Status_Entry *) &qpti->res_cpu[out_ptr];
		out_ptr = NEXT_RES_PTR(out_ptr);

		/* We store an index in the handle, not the pointer in
		 * some form.  This avoids problems due to the fact
		 * that the handle provided is only 32-bits. -DaveM
		 */
		cmd_slot = sts->handle;
		Cmnd = qpti->cmd_slots[cmd_slot];
		qpti->cmd_slots[cmd_slot] = NULL;

		if (sts->completion_status == CS_RESET_OCCURRED ||
		    sts->completion_status == CS_ABORTED ||
		    (sts->status_flags & STF_BUS_RESET))
			qpti->send_marker = 1;

		if (sts->state_flags & SF_GOT_SENSE)
			memcpy(Cmnd->sense_buffer, sts->req_sense_data,
			       SCSI_SENSE_BUFFERSIZE);

		if (sts->hdr.entry_type == ENTRY_STATUS)
			Cmnd->result =
			    qlogicpti_return_status(sts, qpti->qpti_id);
		else
			Cmnd->result = DID_ERROR << 16;

		if (scsi_bufflen(Cmnd))
			dma_unmap_sg(&qpti->op->dev,
				     scsi_sglist(Cmnd), scsi_sg_count(Cmnd),
				     Cmnd->sc_data_direction);

		qpti->cmd_count[Cmnd->device->id]--;
		sbus_writew(out_ptr, qpti->qregs + MBOX5);
		Cmnd->host_scribble = (unsigned char *) done_queue;
		done_queue = Cmnd;
	}
	qpti->res_out_ptr = out_ptr;

	return done_queue;
}