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
struct st_request {int /*<<< orphan*/ * sense; } ;
struct st_partstat {scalar_t__ eof; int drv_block; scalar_t__ at_sm; } ;
struct st_modedef {scalar_t__ do_read_ahead; } ;
struct TYPE_4__ {scalar_t__ sense_key; } ;
struct st_cmdstatus {int flags; scalar_t__ residual; TYPE_1__ sense_hdr; scalar_t__ uremainder64; scalar_t__ remainder_valid; scalar_t__ have_sense; } ;
struct st_buffer {int buffer_blocks; int buffer_size; long syscall_result; int buffer_bytes; struct st_cmdstatus cmdstat; scalar_t__ read_pointer; int /*<<< orphan*/  do_dio; } ;
struct scsi_tape {size_t current_mode; size_t partition; int block_size; struct st_buffer* buffer; scalar_t__ sili; TYPE_3__* device; scalar_t__ try_dio_now; struct st_partstat* ps; struct st_modedef* modes; } ;
struct TYPE_6__ {TYPE_2__* request_queue; } ;
struct TYPE_5__ {int /*<<< orphan*/  rq_timeout; } ;

/* Variables and functions */
 scalar_t__ BLANK_CHECK ; 
 int /*<<< orphan*/  DEBC_printk (struct scsi_tape*,char*,...) ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 long EIO ; 
 long ENOMEM ; 
 int /*<<< orphan*/  KERN_NOTICE ; 
 int MAX_COMMAND_SIZE ; 
 int /*<<< orphan*/  MAX_RETRIES ; 
 scalar_t__ MEDIUM_ERROR ; 
 int /*<<< orphan*/  MTBSR ; 
 unsigned char READ_6 ; 
 int SENSE_EOM ; 
 int SENSE_FMK ; 
 int SENSE_ILI ; 
 scalar_t__ ST_EOD_1 ; 
 void* ST_EOD_2 ; 
 scalar_t__ ST_EOM_OK ; 
 scalar_t__ ST_FM ; 
 scalar_t__ ST_FM_HIT ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  release_buffering (struct scsi_tape*,int) ; 
 struct st_request* st_do_scsi (struct st_request*,struct scsi_tape*,unsigned char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ st_int_ioctl (struct scsi_tape*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  st_printk (int /*<<< orphan*/ ,struct scsi_tape*,char*,...) ; 
 int /*<<< orphan*/  st_release_request (struct st_request*) ; 
 scalar_t__ try_rdio ; 

__attribute__((used)) static long read_tape(struct scsi_tape *STp, long count,
		      struct st_request ** aSRpnt)
{
	int transfer, blks, bytes;
	unsigned char cmd[MAX_COMMAND_SIZE];
	struct st_request *SRpnt;
	struct st_modedef *STm;
	struct st_partstat *STps;
	struct st_buffer *STbp;
	int retval = 0;

	if (count == 0)
		return 0;

	STm = &(STp->modes[STp->current_mode]);
	STps = &(STp->ps[STp->partition]);
	if (STps->eof == ST_FM_HIT)
		return 1;
	STbp = STp->buffer;

	if (STp->block_size == 0)
		blks = bytes = count;
	else {
		if (!(STp->try_dio_now && try_rdio) && STm->do_read_ahead) {
			blks = (STp->buffer)->buffer_blocks;
			bytes = blks * STp->block_size;
		} else {
			bytes = count;
			if (!STbp->do_dio && bytes > (STp->buffer)->buffer_size)
				bytes = (STp->buffer)->buffer_size;
			blks = bytes / STp->block_size;
			bytes = blks * STp->block_size;
		}
	}

	memset(cmd, 0, MAX_COMMAND_SIZE);
	cmd[0] = READ_6;
	cmd[1] = (STp->block_size != 0);
	if (!cmd[1] && STp->sili)
		cmd[1] |= 2;
	cmd[2] = blks >> 16;
	cmd[3] = blks >> 8;
	cmd[4] = blks;

	SRpnt = *aSRpnt;
	SRpnt = st_do_scsi(SRpnt, STp, cmd, bytes, DMA_FROM_DEVICE,
			   STp->device->request_queue->rq_timeout,
			   MAX_RETRIES, 1);
	release_buffering(STp, 1);
	*aSRpnt = SRpnt;
	if (!SRpnt)
		return STbp->syscall_result;

	STbp->read_pointer = 0;
	STps->at_sm = 0;

	/* Something to check */
	if (STbp->syscall_result) {
		struct st_cmdstatus *cmdstatp = &STp->buffer->cmdstat;

		retval = 1;
		DEBC_printk(STp,
			    "Sense: %2x %2x %2x %2x %2x %2x %2x %2x\n",
			    SRpnt->sense[0], SRpnt->sense[1],
			    SRpnt->sense[2], SRpnt->sense[3],
			    SRpnt->sense[4], SRpnt->sense[5],
			    SRpnt->sense[6], SRpnt->sense[7]);
		if (cmdstatp->have_sense) {

			if (cmdstatp->sense_hdr.sense_key == BLANK_CHECK)
				cmdstatp->flags &= 0xcf;	/* No need for EOM in this case */

			if (cmdstatp->flags != 0) { /* EOF, EOM, or ILI */
				/* Compute the residual count */
				if (cmdstatp->remainder_valid)
					transfer = (int)cmdstatp->uremainder64;
				else
					transfer = 0;
				if (cmdstatp->sense_hdr.sense_key == MEDIUM_ERROR) {
					if (STp->block_size == 0)
						transfer = bytes;
					/* Some drives set ILI with MEDIUM ERROR */
					cmdstatp->flags &= ~SENSE_ILI;
				}

				if (cmdstatp->flags & SENSE_ILI) {	/* ILI */
					if (STp->block_size == 0 &&
					    transfer < 0) {
						st_printk(KERN_NOTICE, STp,
							  "Failed to read %d "
							  "byte block with %d "
							  "byte transfer.\n",
							  bytes - transfer,
							  bytes);
						if (STps->drv_block >= 0)
							STps->drv_block += 1;
						STbp->buffer_bytes = 0;
						return (-ENOMEM);
					} else if (STp->block_size == 0) {
						STbp->buffer_bytes = bytes - transfer;
					} else {
						st_release_request(SRpnt);
						SRpnt = *aSRpnt = NULL;
						if (transfer == blks) {	/* We did not get anything, error */
							st_printk(KERN_NOTICE, STp,
								  "Incorrect "
								  "block size.\n");
							if (STps->drv_block >= 0)
								STps->drv_block += blks - transfer + 1;
							st_int_ioctl(STp, MTBSR, 1);
							return (-EIO);
						}
						/* We have some data, deliver it */
						STbp->buffer_bytes = (blks - transfer) *
						    STp->block_size;
						DEBC_printk(STp, "ILI but "
							    "enough data "
							    "received %ld "
							    "%d.\n", count,
							    STbp->buffer_bytes);
						if (STps->drv_block >= 0)
							STps->drv_block += 1;
						if (st_int_ioctl(STp, MTBSR, 1))
							return (-EIO);
					}
				} else if (cmdstatp->flags & SENSE_FMK) {	/* FM overrides EOM */
					if (STps->eof != ST_FM_HIT)
						STps->eof = ST_FM_HIT;
					else
						STps->eof = ST_EOD_2;
					if (STp->block_size == 0)
						STbp->buffer_bytes = 0;
					else
						STbp->buffer_bytes =
						    bytes - transfer * STp->block_size;
					DEBC_printk(STp, "EOF detected (%d "
						    "bytes read).\n",
						    STbp->buffer_bytes);
				} else if (cmdstatp->flags & SENSE_EOM) {
					if (STps->eof == ST_FM)
						STps->eof = ST_EOD_1;
					else
						STps->eof = ST_EOM_OK;
					if (STp->block_size == 0)
						STbp->buffer_bytes = bytes - transfer;
					else
						STbp->buffer_bytes =
						    bytes - transfer * STp->block_size;

					DEBC_printk(STp, "EOM detected (%d "
						    "bytes read).\n",
						    STbp->buffer_bytes);
				}
			}
			/* end of EOF, EOM, ILI test */
			else {	/* nonzero sense key */
				DEBC_printk(STp, "Tape error while reading.\n");
				STps->drv_block = (-1);
				if (STps->eof == ST_FM &&
				    cmdstatp->sense_hdr.sense_key == BLANK_CHECK) {
					DEBC_printk(STp, "Zero returned for "
						    "first BLANK CHECK "
						    "after EOF.\n");
					STps->eof = ST_EOD_2;	/* First BLANK_CHECK after FM */
				} else	/* Some other extended sense code */
					retval = (-EIO);
			}

			if (STbp->buffer_bytes < 0)  /* Caused by bogus sense data */
				STbp->buffer_bytes = 0;
		}
		/* End of extended sense test */
		else {		/* Non-extended sense */
			retval = STbp->syscall_result;
		}

	}
	/* End of error handling */
	else {			/* Read successful */
		STbp->buffer_bytes = bytes;
		if (STp->sili) /* In fixed block mode residual is always zero here */
			STbp->buffer_bytes -= STp->buffer->cmdstat.residual;
	}

	if (STps->drv_block >= 0) {
		if (STp->block_size == 0)
			STps->drv_block++;
		else
			STps->drv_block += STbp->buffer_bytes / STp->block_size;
	}
	return retval;
}