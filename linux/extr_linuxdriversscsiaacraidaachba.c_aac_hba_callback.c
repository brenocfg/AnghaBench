#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int sent_command; } ;
struct scsi_cmnd {int result; int /*<<< orphan*/  (* scsi_done ) (struct scsi_cmnd*) ;TYPE_2__ SCp; } ;
struct fib {int flags; struct aac_dev* dev; scalar_t__ hw_fib_va; } ;
struct aac_hba_resp {int service_response; } ;
struct TYPE_3__ {struct aac_hba_resp err; } ;
struct aac_native_hba {TYPE_1__ resp; } ;
struct aac_dev {int dummy; } ;

/* Variables and functions */
 int COMMAND_COMPLETE ; 
 int DID_ERROR ; 
 int DID_NO_CONNECT ; 
 int DID_OK ; 
 int FIB_CONTEXT_FLAG_FASTRESP ; 
 int FIB_CONTEXT_FLAG_NATIVE_HBA_TMF ; 
#define  HBA_RESP_SVCRES_FAILURE 133 
#define  HBA_RESP_SVCRES_TASK_COMPLETE 132 
#define  HBA_RESP_SVCRES_TMF_COMPLETE 131 
#define  HBA_RESP_SVCRES_TMF_LUN_INVALID 130 
#define  HBA_RESP_SVCRES_TMF_REJECTED 129 
#define  HBA_RESP_SVCRES_TMF_SUCCEEDED 128 
 int MESSAGE_REJECT ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aac_fib_complete (struct fib*) ; 
 int /*<<< orphan*/  aac_valid_context (struct scsi_cmnd*,struct fib*) ; 
 int /*<<< orphan*/  hba_resp_task_complete (struct aac_dev*,struct scsi_cmnd*,struct aac_hba_resp*) ; 
 int /*<<< orphan*/  hba_resp_task_failure (struct aac_dev*,struct scsi_cmnd*,struct aac_hba_resp*) ; 
 int /*<<< orphan*/  scsi_dma_unmap (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  stub1 (struct scsi_cmnd*) ; 

void aac_hba_callback(void *context, struct fib *fibptr)
{
	struct aac_dev *dev;
	struct scsi_cmnd *scsicmd;

	struct aac_hba_resp *err =
			&((struct aac_native_hba *)fibptr->hw_fib_va)->resp.err;

	scsicmd = (struct scsi_cmnd *) context;

	if (!aac_valid_context(scsicmd, fibptr))
		return;

	WARN_ON(fibptr == NULL);
	dev = fibptr->dev;

	if (!(fibptr->flags & FIB_CONTEXT_FLAG_NATIVE_HBA_TMF))
		scsi_dma_unmap(scsicmd);

	if (fibptr->flags & FIB_CONTEXT_FLAG_FASTRESP) {
		/* fast response */
		scsicmd->result = DID_OK << 16 | COMMAND_COMPLETE << 8;
		goto out;
	}

	switch (err->service_response) {
	case HBA_RESP_SVCRES_TASK_COMPLETE:
		hba_resp_task_complete(dev, scsicmd, err);
		break;
	case HBA_RESP_SVCRES_FAILURE:
		hba_resp_task_failure(dev, scsicmd, err);
		break;
	case HBA_RESP_SVCRES_TMF_REJECTED:
		scsicmd->result = DID_ERROR << 16 | MESSAGE_REJECT << 8;
		break;
	case HBA_RESP_SVCRES_TMF_LUN_INVALID:
		scsicmd->result = DID_NO_CONNECT << 16 | COMMAND_COMPLETE << 8;
		break;
	case HBA_RESP_SVCRES_TMF_COMPLETE:
	case HBA_RESP_SVCRES_TMF_SUCCEEDED:
		scsicmd->result = DID_OK << 16 | COMMAND_COMPLETE << 8;
		break;
	default:
		scsicmd->result = DID_ERROR << 16 | COMMAND_COMPLETE << 8;
		break;
	}

out:
	aac_fib_complete(fibptr);

	if (fibptr->flags & FIB_CONTEXT_FLAG_NATIVE_HBA_TMF)
		scsicmd->SCp.sent_command = 1;
	else
		scsicmd->scsi_done(scsicmd);
}