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
struct scsi_sense_hdr {int response_code; int additional_length; int sense_key; int asc; int ascq; } ;
struct scsi_device {int sdev_bflags; int /*<<< orphan*/  retry_hwerror; int /*<<< orphan*/  allow_restart; TYPE_2__* sdev_target; int /*<<< orphan*/  expecting_cc_ua; TYPE_1__* handler; } ;
struct scsi_cmnd {scalar_t__* cmnd; scalar_t__ scsi_done; int* sense_buffer; struct scsi_device* device; } ;
struct TYPE_4__ {int /*<<< orphan*/  expecting_lun_change; } ;
struct TYPE_3__ {int (* check_sense ) (struct scsi_device*,struct scsi_sense_hdr*) ;} ;

/* Variables and functions */
#define  ABORTED_COMMAND 140 
 int ADD_TO_MLQUEUE ; 
#define  BLANK_CHECK 139 
 int BLIST_RETRY_ASC_C1 ; 
 int BLIST_RETRY_ITF ; 
#define  COPY_ABORTED 138 
#define  DATA_PROTECT 137 
 int /*<<< orphan*/  DID_ALLOC_FAILURE ; 
 int /*<<< orphan*/  DID_MEDIUM_ERROR ; 
 int /*<<< orphan*/  DID_TARGET_FAILURE ; 
 int FAILED ; 
#define  HARDWARE_ERROR 136 
#define  ILLEGAL_REQUEST 135 
#define  MEDIUM_ERROR 134 
#define  MISCOMPARE 133 
 int NEEDS_RETRY ; 
#define  NOT_READY 132 
#define  NO_SENSE 131 
#define  RECOVERED_ERROR 130 
 int SCSI_RETURN_NOT_HANDLED ; 
 int SUCCESS ; 
 scalar_t__ TEST_UNIT_READY ; 
#define  UNIT_ATTENTION 129 
#define  VOLUME_OVERFLOW 128 
 int /*<<< orphan*/  scsi_command_normalize_sense (struct scsi_cmnd*,struct scsi_sense_hdr*) ; 
 scalar_t__ scsi_eh_done ; 
 int /*<<< orphan*/  scsi_report_sense (struct scsi_device*,struct scsi_sense_hdr*) ; 
 scalar_t__ scsi_sense_is_deferred (struct scsi_sense_hdr*) ; 
 int /*<<< orphan*/  set_host_byte (struct scsi_cmnd*,int /*<<< orphan*/ ) ; 
 int stub1 (struct scsi_device*,struct scsi_sense_hdr*) ; 

int scsi_check_sense(struct scsi_cmnd *scmd)
{
	struct scsi_device *sdev = scmd->device;
	struct scsi_sense_hdr sshdr;

	if (! scsi_command_normalize_sense(scmd, &sshdr))
		return FAILED;	/* no valid sense data */

	scsi_report_sense(sdev, &sshdr);

	if (scsi_sense_is_deferred(&sshdr))
		return NEEDS_RETRY;

	if (sdev->handler && sdev->handler->check_sense) {
		int rc;

		rc = sdev->handler->check_sense(sdev, &sshdr);
		if (rc != SCSI_RETURN_NOT_HANDLED)
			return rc;
		/* handler does not care. Drop down to default handling */
	}

	if (scmd->cmnd[0] == TEST_UNIT_READY && scmd->scsi_done != scsi_eh_done)
		/*
		 * nasty: for mid-layer issued TURs, we need to return the
		 * actual sense data without any recovery attempt.  For eh
		 * issued ones, we need to try to recover and interpret
		 */
		return SUCCESS;

	/*
	 * Previous logic looked for FILEMARK, EOM or ILI which are
	 * mainly associated with tapes and returned SUCCESS.
	 */
	if (sshdr.response_code == 0x70) {
		/* fixed format */
		if (scmd->sense_buffer[2] & 0xe0)
			return SUCCESS;
	} else {
		/*
		 * descriptor format: look for "stream commands sense data
		 * descriptor" (see SSC-3). Assume single sense data
		 * descriptor. Ignore ILI from SBC-2 READ LONG and WRITE LONG.
		 */
		if ((sshdr.additional_length > 3) &&
		    (scmd->sense_buffer[8] == 0x4) &&
		    (scmd->sense_buffer[11] & 0xe0))
			return SUCCESS;
	}

	switch (sshdr.sense_key) {
	case NO_SENSE:
		return SUCCESS;
	case RECOVERED_ERROR:
		return /* soft_error */ SUCCESS;

	case ABORTED_COMMAND:
		if (sshdr.asc == 0x10) /* DIF */
			return SUCCESS;

		if (sshdr.asc == 0x44 && sdev->sdev_bflags & BLIST_RETRY_ITF)
			return ADD_TO_MLQUEUE;
		if (sshdr.asc == 0xc1 && sshdr.ascq == 0x01 &&
		    sdev->sdev_bflags & BLIST_RETRY_ASC_C1)
			return ADD_TO_MLQUEUE;

		return NEEDS_RETRY;
	case NOT_READY:
	case UNIT_ATTENTION:
		/*
		 * if we are expecting a cc/ua because of a bus reset that we
		 * performed, treat this just as a retry.  otherwise this is
		 * information that we should pass up to the upper-level driver
		 * so that we can deal with it there.
		 */
		if (scmd->device->expecting_cc_ua) {
			/*
			 * Because some device does not queue unit
			 * attentions correctly, we carefully check
			 * additional sense code and qualifier so as
			 * not to squash media change unit attention.
			 */
			if (sshdr.asc != 0x28 || sshdr.ascq != 0x00) {
				scmd->device->expecting_cc_ua = 0;
				return NEEDS_RETRY;
			}
		}
		/*
		 * we might also expect a cc/ua if another LUN on the target
		 * reported a UA with an ASC/ASCQ of 3F 0E -
		 * REPORTED LUNS DATA HAS CHANGED.
		 */
		if (scmd->device->sdev_target->expecting_lun_change &&
		    sshdr.asc == 0x3f && sshdr.ascq == 0x0e)
			return NEEDS_RETRY;
		/*
		 * if the device is in the process of becoming ready, we
		 * should retry.
		 */
		if ((sshdr.asc == 0x04) && (sshdr.ascq == 0x01))
			return NEEDS_RETRY;
		/*
		 * if the device is not started, we need to wake
		 * the error handler to start the motor
		 */
		if (scmd->device->allow_restart &&
		    (sshdr.asc == 0x04) && (sshdr.ascq == 0x02))
			return FAILED;
		/*
		 * Pass the UA upwards for a determination in the completion
		 * functions.
		 */
		return SUCCESS;

		/* these are not supported */
	case DATA_PROTECT:
		if (sshdr.asc == 0x27 && sshdr.ascq == 0x07) {
			/* Thin provisioning hard threshold reached */
			set_host_byte(scmd, DID_ALLOC_FAILURE);
			return SUCCESS;
		}
		/* FALLTHROUGH */
	case COPY_ABORTED:
	case VOLUME_OVERFLOW:
	case MISCOMPARE:
	case BLANK_CHECK:
		set_host_byte(scmd, DID_TARGET_FAILURE);
		return SUCCESS;

	case MEDIUM_ERROR:
		if (sshdr.asc == 0x11 || /* UNRECOVERED READ ERR */
		    sshdr.asc == 0x13 || /* AMNF DATA FIELD */
		    sshdr.asc == 0x14) { /* RECORD NOT FOUND */
			set_host_byte(scmd, DID_MEDIUM_ERROR);
			return SUCCESS;
		}
		return NEEDS_RETRY;

	case HARDWARE_ERROR:
		if (scmd->device->retry_hwerror)
			return ADD_TO_MLQUEUE;
		else
			set_host_byte(scmd, DID_TARGET_FAILURE);
		/* FALLTHROUGH */

	case ILLEGAL_REQUEST:
		if (sshdr.asc == 0x20 || /* Invalid command operation code */
		    sshdr.asc == 0x21 || /* Logical block address out of range */
		    sshdr.asc == 0x22 || /* Invalid function */
		    sshdr.asc == 0x24 || /* Invalid field in cdb */
		    sshdr.asc == 0x26 || /* Parameter value invalid */
		    sshdr.asc == 0x27) { /* Write protected */
			set_host_byte(scmd, DID_TARGET_FAILURE);
		}
		return SUCCESS;

	default:
		return SUCCESS;
	}
}