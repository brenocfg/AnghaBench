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
typedef  int u32 ;
struct vmscsi_request {int data_transfer_length; scalar_t__ srb_status; scalar_t__ scsi_status; } ;
struct vmbus_channel_packet_multipage_buffer {int dummy; } ;
struct storvsc_device {struct Scsi_Host* host; } ;
struct TYPE_4__ {struct vmscsi_request vm_srb; } ;
struct storvsc_cmd_request {int payload_sz; TYPE_3__* payload; TYPE_1__ vstor_packet; struct scsi_cmnd* cmd; } ;
struct scsi_sense_hdr {scalar_t__ sense_key; int asc; int /*<<< orphan*/  ascq; } ;
struct scsi_cmnd {int /*<<< orphan*/  (* scsi_done ) (struct scsi_cmnd*) ;int /*<<< orphan*/  device; int /*<<< orphan*/  sense_buffer; scalar_t__ result; } ;
struct Scsi_Host {int dummy; } ;
struct TYPE_5__ {int len; } ;
struct TYPE_6__ {TYPE_2__ range; } ;

/* Variables and functions */
 scalar_t__ NOT_READY ; 
 int /*<<< orphan*/  SCSI_SENSE_BUFFERSIZE ; 
 scalar_t__ SRB_STATUS_DATA_OVERRUN ; 
 scalar_t__ SRB_STATUS_SUCCESS ; 
 int /*<<< orphan*/  STORVSC_LOGGING_ERROR ; 
 scalar_t__ do_logging (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 scalar_t__ scsi_normalize_sense (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct scsi_sense_hdr*) ; 
 int /*<<< orphan*/  scsi_print_sense_hdr (int /*<<< orphan*/ ,char*,struct scsi_sense_hdr*) ; 
 int /*<<< orphan*/  scsi_set_resid (struct scsi_cmnd*,int) ; 
 int /*<<< orphan*/  storvsc_handle_error (struct vmscsi_request*,struct scsi_cmnd*,struct Scsi_Host*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct scsi_cmnd*) ; 

__attribute__((used)) static void storvsc_command_completion(struct storvsc_cmd_request *cmd_request,
				       struct storvsc_device *stor_dev)
{
	struct scsi_cmnd *scmnd = cmd_request->cmd;
	struct scsi_sense_hdr sense_hdr;
	struct vmscsi_request *vm_srb;
	u32 data_transfer_length;
	struct Scsi_Host *host;
	u32 payload_sz = cmd_request->payload_sz;
	void *payload = cmd_request->payload;

	host = stor_dev->host;

	vm_srb = &cmd_request->vstor_packet.vm_srb;
	data_transfer_length = vm_srb->data_transfer_length;

	scmnd->result = vm_srb->scsi_status;

	if (scmnd->result) {
		if (scsi_normalize_sense(scmnd->sense_buffer,
				SCSI_SENSE_BUFFERSIZE, &sense_hdr) &&
		    !(sense_hdr.sense_key == NOT_READY &&
				 sense_hdr.asc == 0x03A) &&
		    do_logging(STORVSC_LOGGING_ERROR))
			scsi_print_sense_hdr(scmnd->device, "storvsc",
					     &sense_hdr);
	}

	if (vm_srb->srb_status != SRB_STATUS_SUCCESS) {
		storvsc_handle_error(vm_srb, scmnd, host, sense_hdr.asc,
					 sense_hdr.ascq);
		/*
		 * The Windows driver set data_transfer_length on
		 * SRB_STATUS_DATA_OVERRUN. On other errors, this value
		 * is untouched.  In these cases we set it to 0.
		 */
		if (vm_srb->srb_status != SRB_STATUS_DATA_OVERRUN)
			data_transfer_length = 0;
	}

	scsi_set_resid(scmnd,
		cmd_request->payload->range.len - data_transfer_length);

	scmnd->scsi_done(scmnd);

	if (payload_sz >
		sizeof(struct vmbus_channel_packet_multipage_buffer))
		kfree(payload);
}