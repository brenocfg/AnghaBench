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
struct sense_data_t {int dummy; } ;
struct scsi_cmnd {int result; int /*<<< orphan*/  sense_buffer; } ;
struct rtsx_chip {int /*<<< orphan*/ * sense_buffer; } ;

/* Variables and functions */
 int DID_ABORT ; 
 int DID_ERROR ; 
 int /*<<< orphan*/  RTSX_STAT_ABORT ; 
 int SAM_STAT_CHECK_CONDITION ; 
 int SAM_STAT_GOOD ; 
 size_t SCSI_LUN (struct scsi_cmnd*) ; 
 int TRANSPORT_ERROR ; 
 int TRANSPORT_FAILED ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned char*,int) ; 
 scalar_t__ rtsx_chk_stat (struct rtsx_chip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtsx_dev (struct rtsx_chip*) ; 
 int rtsx_scsi_handler (struct scsi_cmnd*,struct rtsx_chip*) ; 

void rtsx_invoke_transport(struct scsi_cmnd *srb, struct rtsx_chip *chip)
{
	int result;

	result = rtsx_scsi_handler(srb, chip);

	/*
	 * if the command gets aborted by the higher layers, we need to
	 * short-circuit all other processing.
	 */
	if (rtsx_chk_stat(chip, RTSX_STAT_ABORT)) {
		dev_dbg(rtsx_dev(chip), "-- command was aborted\n");
		srb->result = DID_ABORT << 16;
		goto handle_errors;
	}

	/* if there is a transport error, reset and don't auto-sense */
	if (result == TRANSPORT_ERROR) {
		dev_dbg(rtsx_dev(chip), "-- transport indicates error, resetting\n");
		srb->result = DID_ERROR << 16;
		goto handle_errors;
	}

	srb->result = SAM_STAT_GOOD;

	/*
	 * If we have a failure, we're going to do a REQUEST_SENSE
	 * automatically.  Note that we differentiate between a command
	 * "failure" and an "error" in the transport mechanism.
	 */
	if (result == TRANSPORT_FAILED) {
		/* set the result so the higher layers expect this data */
		srb->result = SAM_STAT_CHECK_CONDITION;
		memcpy(srb->sense_buffer,
		       (unsigned char *)&chip->sense_buffer[SCSI_LUN(srb)],
		       sizeof(struct sense_data_t));
	}

	return;

handle_errors:
	return;
}