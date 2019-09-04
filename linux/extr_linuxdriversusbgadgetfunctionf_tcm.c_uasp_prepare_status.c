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
struct sense_iu {int /*<<< orphan*/  status; void* len; void* tag; int /*<<< orphan*/  iu_id; } ;
struct se_cmd {scalar_t__ scsi_sense_length; int /*<<< orphan*/  scsi_status; } ;
struct usbg_cmd {scalar_t__ tag; int /*<<< orphan*/  state; struct uas_stream* stream; struct sense_iu sense_iu; struct se_cmd se_cmd; } ;
struct uas_stream {TYPE_1__* req_status; } ;
struct TYPE_2__ {int /*<<< orphan*/  complete; struct sense_iu* buf; scalar_t__ length; struct usbg_cmd* context; } ;

/* Variables and functions */
 int /*<<< orphan*/  IU_ID_STATUS ; 
 int /*<<< orphan*/  UASP_QUEUE_COMMAND ; 
 void* cpu_to_be16 (scalar_t__) ; 
 int /*<<< orphan*/  uasp_status_data_cmpl ; 

__attribute__((used)) static void uasp_prepare_status(struct usbg_cmd *cmd)
{
	struct se_cmd *se_cmd = &cmd->se_cmd;
	struct sense_iu *iu = &cmd->sense_iu;
	struct uas_stream *stream = cmd->stream;

	cmd->state = UASP_QUEUE_COMMAND;
	iu->iu_id = IU_ID_STATUS;
	iu->tag = cpu_to_be16(cmd->tag);

	/*
	 * iu->status_qual = cpu_to_be16(STATUS QUALIFIER SAM-4. Where R U?);
	 */
	iu->len = cpu_to_be16(se_cmd->scsi_sense_length);
	iu->status = se_cmd->scsi_status;
	stream->req_status->context = cmd;
	stream->req_status->length = se_cmd->scsi_sense_length + 16;
	stream->req_status->buf = iu;
	stream->req_status->complete = uasp_status_data_cmpl;
}