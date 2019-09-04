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
struct scsi_cmnd {int result; int /*<<< orphan*/  sense_buffer; } ;
struct aac_hba_resp {int status; int /*<<< orphan*/  sense_response_buf; int /*<<< orphan*/  sense_response_data_len; int /*<<< orphan*/  residual_count; } ;
struct aac_dev {int dummy; } ;

/* Variables and functions */
 int ABORT ; 
 int COMMAND_COMPLETE ; 
 int DID_ABORT ; 
 int DID_BUS_BUSY ; 
 int DID_ERROR ; 
 int DID_OK ; 
#define  SAM_STAT_BUSY 133 
#define  SAM_STAT_CHECK_CONDITION 132 
#define  SAM_STAT_GOOD 131 
#define  SAM_STAT_RESERVATION_CONFLICT 130 
#define  SAM_STAT_TASK_ABORTED 129 
#define  SAM_STAT_TASK_SET_FULL 128 
 int /*<<< orphan*/  SCSI_SENSE_BUFFERSIZE ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int min_t (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_set_resid (struct scsi_cmnd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u8 ; 

__attribute__((used)) static void hba_resp_task_complete(struct aac_dev *dev,
					struct scsi_cmnd *scsicmd,
					struct aac_hba_resp *err) {

	scsicmd->result = err->status;
	/* set residual count */
	scsi_set_resid(scsicmd, le32_to_cpu(err->residual_count));

	switch (err->status) {
	case SAM_STAT_GOOD:
		scsicmd->result |= DID_OK << 16 | COMMAND_COMPLETE << 8;
		break;
	case SAM_STAT_CHECK_CONDITION:
	{
		int len;

		len = min_t(u8, err->sense_response_data_len,
			SCSI_SENSE_BUFFERSIZE);
		if (len)
			memcpy(scsicmd->sense_buffer,
				err->sense_response_buf, len);
		scsicmd->result |= DID_OK << 16 | COMMAND_COMPLETE << 8;
		break;
	}
	case SAM_STAT_BUSY:
		scsicmd->result |= DID_BUS_BUSY << 16 | COMMAND_COMPLETE << 8;
		break;
	case SAM_STAT_TASK_ABORTED:
		scsicmd->result |= DID_ABORT << 16 | ABORT << 8;
		break;
	case SAM_STAT_RESERVATION_CONFLICT:
	case SAM_STAT_TASK_SET_FULL:
	default:
		scsicmd->result |= DID_ERROR << 16 | COMMAND_COMPLETE << 8;
		break;
	}
}