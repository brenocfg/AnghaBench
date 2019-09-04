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
typedef  scalar_t__ u32 ;
struct fsg_lun {scalar_t__ num_sectors; unsigned int blkbits; unsigned int file_length; unsigned int sense_data_info; int info_valid; void* sense_data; int /*<<< orphan*/  blksize; TYPE_2__* filp; int /*<<< orphan*/  nofua; scalar_t__ ro; } ;
struct fsg_common {int* cmnd; scalar_t__ data_size_from_cmnd; unsigned int usb_amount_left; unsigned int residue; int short_packet_received; struct fsg_buffhd* next_buffhd_to_drain; struct fsg_buffhd* next_buffhd_to_fill; struct fsg_lun* curlun; } ;
struct fsg_buffhd {scalar_t__ state; unsigned int bulk_out_intended_length; TYPE_1__* outreq; int /*<<< orphan*/  buf; struct fsg_buffhd* next; } ;
typedef  unsigned int ssize_t ;
typedef  unsigned int loff_t ;
struct TYPE_4__ {int /*<<< orphan*/  f_lock; int /*<<< orphan*/  f_flags; } ;
struct TYPE_3__ {scalar_t__ status; unsigned int actual; } ;

/* Variables and functions */
 scalar_t__ BUF_STATE_EMPTY ; 
 int EINTR ; 
 int EINVAL ; 
 int EIO ; 
 unsigned int FSG_BUFLEN ; 
 int /*<<< orphan*/  LDBG (struct fsg_lun*,char*,int,...) ; 
 int /*<<< orphan*/  LERROR (struct fsg_lun*,char*,unsigned int,unsigned long long,unsigned long long) ; 
 int /*<<< orphan*/  O_SYNC ; 
 void* SS_COMMUNICATION_FAILURE ; 
 void* SS_INVALID_FIELD_IN_CDB ; 
 void* SS_LOGICAL_BLOCK_ADDRESS_OUT_OF_RANGE ; 
 void* SS_WRITE_ERROR ; 
 void* SS_WRITE_PROTECTED ; 
 int /*<<< orphan*/  VLDBG (struct fsg_lun*,char*,unsigned int,unsigned long long,int) ; 
 int WRITE_6 ; 
 int /*<<< orphan*/  current ; 
 scalar_t__ get_unaligned_be24 (int*) ; 
 scalar_t__ get_unaligned_be32 (int*) ; 
 unsigned int kernel_write (TYPE_2__*,int /*<<< orphan*/ ,unsigned int,unsigned int*) ; 
 unsigned int min (unsigned int,unsigned int) ; 
 unsigned int round_down (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bulk_out_req_length (struct fsg_common*,struct fsg_buffhd*,unsigned int) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int sleep_thread (struct fsg_common*,int,struct fsg_buffhd*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  start_out_transfer (struct fsg_common*,struct fsg_buffhd*) ; 

__attribute__((used)) static int do_write(struct fsg_common *common)
{
	struct fsg_lun		*curlun = common->curlun;
	u32			lba;
	struct fsg_buffhd	*bh;
	int			get_some_more;
	u32			amount_left_to_req, amount_left_to_write;
	loff_t			usb_offset, file_offset, file_offset_tmp;
	unsigned int		amount;
	ssize_t			nwritten;
	int			rc;

	if (curlun->ro) {
		curlun->sense_data = SS_WRITE_PROTECTED;
		return -EINVAL;
	}
	spin_lock(&curlun->filp->f_lock);
	curlun->filp->f_flags &= ~O_SYNC;	/* Default is not to wait */
	spin_unlock(&curlun->filp->f_lock);

	/*
	 * Get the starting Logical Block Address and check that it's
	 * not too big
	 */
	if (common->cmnd[0] == WRITE_6)
		lba = get_unaligned_be24(&common->cmnd[1]);
	else {
		lba = get_unaligned_be32(&common->cmnd[2]);

		/*
		 * We allow DPO (Disable Page Out = don't save data in the
		 * cache) and FUA (Force Unit Access = write directly to the
		 * medium).  We don't implement DPO; we implement FUA by
		 * performing synchronous output.
		 */
		if (common->cmnd[1] & ~0x18) {
			curlun->sense_data = SS_INVALID_FIELD_IN_CDB;
			return -EINVAL;
		}
		if (!curlun->nofua && (common->cmnd[1] & 0x08)) { /* FUA */
			spin_lock(&curlun->filp->f_lock);
			curlun->filp->f_flags |= O_SYNC;
			spin_unlock(&curlun->filp->f_lock);
		}
	}
	if (lba >= curlun->num_sectors) {
		curlun->sense_data = SS_LOGICAL_BLOCK_ADDRESS_OUT_OF_RANGE;
		return -EINVAL;
	}

	/* Carry out the file writes */
	get_some_more = 1;
	file_offset = usb_offset = ((loff_t) lba) << curlun->blkbits;
	amount_left_to_req = common->data_size_from_cmnd;
	amount_left_to_write = common->data_size_from_cmnd;

	while (amount_left_to_write > 0) {

		/* Queue a request for more data from the host */
		bh = common->next_buffhd_to_fill;
		if (bh->state == BUF_STATE_EMPTY && get_some_more) {

			/*
			 * Figure out how much we want to get:
			 * Try to get the remaining amount,
			 * but not more than the buffer size.
			 */
			amount = min(amount_left_to_req, FSG_BUFLEN);

			/* Beyond the end of the backing file? */
			if (usb_offset >= curlun->file_length) {
				get_some_more = 0;
				curlun->sense_data =
					SS_LOGICAL_BLOCK_ADDRESS_OUT_OF_RANGE;
				curlun->sense_data_info =
					usb_offset >> curlun->blkbits;
				curlun->info_valid = 1;
				continue;
			}

			/* Get the next buffer */
			usb_offset += amount;
			common->usb_amount_left -= amount;
			amount_left_to_req -= amount;
			if (amount_left_to_req == 0)
				get_some_more = 0;

			/*
			 * Except at the end of the transfer, amount will be
			 * equal to the buffer size, which is divisible by
			 * the bulk-out maxpacket size.
			 */
			set_bulk_out_req_length(common, bh, amount);
			if (!start_out_transfer(common, bh))
				/* Dunno what to do if common->fsg is NULL */
				return -EIO;
			common->next_buffhd_to_fill = bh->next;
			continue;
		}

		/* Write the received data to the backing file */
		bh = common->next_buffhd_to_drain;
		if (bh->state == BUF_STATE_EMPTY && !get_some_more)
			break;			/* We stopped early */

		/* Wait for the data to be received */
		rc = sleep_thread(common, false, bh);
		if (rc)
			return rc;

		common->next_buffhd_to_drain = bh->next;
		bh->state = BUF_STATE_EMPTY;

		/* Did something go wrong with the transfer? */
		if (bh->outreq->status != 0) {
			curlun->sense_data = SS_COMMUNICATION_FAILURE;
			curlun->sense_data_info =
					file_offset >> curlun->blkbits;
			curlun->info_valid = 1;
			break;
		}

		amount = bh->outreq->actual;
		if (curlun->file_length - file_offset < amount) {
			LERROR(curlun, "write %u @ %llu beyond end %llu\n",
				       amount, (unsigned long long)file_offset,
				       (unsigned long long)curlun->file_length);
			amount = curlun->file_length - file_offset;
		}

		/*
		 * Don't accept excess data.  The spec doesn't say
		 * what to do in this case.  We'll ignore the error.
		 */
		amount = min(amount, bh->bulk_out_intended_length);

		/* Don't write a partial block */
		amount = round_down(amount, curlun->blksize);
		if (amount == 0)
			goto empty_write;

		/* Perform the write */
		file_offset_tmp = file_offset;
		nwritten = kernel_write(curlun->filp, bh->buf, amount,
				&file_offset_tmp);
		VLDBG(curlun, "file write %u @ %llu -> %d\n", amount,
				(unsigned long long)file_offset, (int)nwritten);
		if (signal_pending(current))
			return -EINTR;		/* Interrupted! */

		if (nwritten < 0) {
			LDBG(curlun, "error in file write: %d\n",
					(int) nwritten);
			nwritten = 0;
		} else if (nwritten < amount) {
			LDBG(curlun, "partial file write: %d/%u\n",
					(int) nwritten, amount);
			nwritten = round_down(nwritten, curlun->blksize);
		}
		file_offset += nwritten;
		amount_left_to_write -= nwritten;
		common->residue -= nwritten;

		/* If an error occurred, report it and its position */
		if (nwritten < amount) {
			curlun->sense_data = SS_WRITE_ERROR;
			curlun->sense_data_info =
					file_offset >> curlun->blkbits;
			curlun->info_valid = 1;
			break;
		}

 empty_write:
		/* Did the host decide to stop early? */
		if (bh->outreq->actual < bh->bulk_out_intended_length) {
			common->short_packet_received = 1;
			break;
		}
	}

	return -EIO;		/* No default reply */
}