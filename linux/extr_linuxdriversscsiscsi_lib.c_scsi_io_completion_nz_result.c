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
struct scsi_sense_hdr {scalar_t__ sense_key; int asc; int ascq; } ;
struct scsi_cmnd {scalar_t__* sense_buffer; struct request* request; } ;
struct request {int rq_flags; } ;
typedef  int /*<<< orphan*/  blk_status_t ;
struct TYPE_2__ {int /*<<< orphan*/  sense_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_STS_OK ; 
 scalar_t__ RECOVERED_ERROR ; 
 int RQF_QUIET ; 
 int /*<<< orphan*/  SCSI_SENSE_BUFFERSIZE ; 
 scalar_t__ blk_rq_bytes (struct request*) ; 
 scalar_t__ blk_rq_is_passthrough (struct request*) ; 
 int /*<<< orphan*/  min (scalar_t__,int /*<<< orphan*/ ) ; 
 int scsi_command_normalize_sense (struct scsi_cmnd*,struct scsi_sense_hdr*) ; 
 int /*<<< orphan*/  scsi_print_sense (struct scsi_cmnd*) ; 
 TYPE_1__* scsi_req (struct request*) ; 
 int /*<<< orphan*/  scsi_result_to_blk_status (struct scsi_cmnd*,int) ; 
 int /*<<< orphan*/  scsi_sense_is_deferred (struct scsi_sense_hdr*) ; 
 scalar_t__ scsi_status_is_good (int) ; 
 scalar_t__ status_byte (int) ; 

__attribute__((used)) static int scsi_io_completion_nz_result(struct scsi_cmnd *cmd, int result,
					blk_status_t *blk_statp)
{
	bool sense_valid;
	bool sense_current = true;	/* false implies "deferred sense" */
	struct request *req = cmd->request;
	struct scsi_sense_hdr sshdr;

	sense_valid = scsi_command_normalize_sense(cmd, &sshdr);
	if (sense_valid)
		sense_current = !scsi_sense_is_deferred(&sshdr);

	if (blk_rq_is_passthrough(req)) {
		if (sense_valid) {
			/*
			 * SG_IO wants current and deferred errors
			 */
			scsi_req(req)->sense_len =
				min(8 + cmd->sense_buffer[7],
				    SCSI_SENSE_BUFFERSIZE);
		}
		if (sense_current)
			*blk_statp = scsi_result_to_blk_status(cmd, result);
	} else if (blk_rq_bytes(req) == 0 && sense_current) {
		/*
		 * Flush commands do not transfers any data, and thus cannot use
		 * good_bytes != blk_rq_bytes(req) as the signal for an error.
		 * This sets *blk_statp explicitly for the problem case.
		 */
		*blk_statp = scsi_result_to_blk_status(cmd, result);
	}
	/*
	 * Recovered errors need reporting, but they're always treated as
	 * success, so fiddle the result code here.  For passthrough requests
	 * we already took a copy of the original into sreq->result which
	 * is what gets returned to the user
	 */
	if (sense_valid && (sshdr.sense_key == RECOVERED_ERROR)) {
		bool do_print = true;
		/*
		 * if ATA PASS-THROUGH INFORMATION AVAILABLE [0x0, 0x1d]
		 * skip print since caller wants ATA registers. Only occurs
		 * on SCSI ATA PASS_THROUGH commands when CK_COND=1
		 */
		if ((sshdr.asc == 0x0) && (sshdr.ascq == 0x1d))
			do_print = false;
		else if (req->rq_flags & RQF_QUIET)
			do_print = false;
		if (do_print)
			scsi_print_sense(cmd);
		result = 0;
		/* for passthrough, *blk_statp may be set */
		*blk_statp = BLK_STS_OK;
	}
	/*
	 * Another corner case: the SCSI status byte is non-zero but 'good'.
	 * Example: PRE-FETCH command returns SAM_STAT_CONDITION_MET when
	 * it is able to fit nominated LBs in its cache (and SAM_STAT_GOOD
	 * if it can't fit). Treat SAM_STAT_CONDITION_MET and the related
	 * intermediate statuses (both obsolete in SAM-4) as good.
	 */
	if (status_byte(result) && scsi_status_is_good(result)) {
		result = 0;
		*blk_statp = BLK_STS_OK;
	}
	return result;
}