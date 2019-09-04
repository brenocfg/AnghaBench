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
typedef  scalar_t__ u32 ;
struct fsg_lun {scalar_t__ num_sectors; unsigned int blkbits; unsigned int sense_data_info; int info_valid; void* sense_data; int /*<<< orphan*/  blksize; int /*<<< orphan*/  filp; scalar_t__ file_length; } ;
struct fsg_common {int* cmnd; scalar_t__ data_size_from_cmnd; unsigned int residue; struct fsg_buffhd* next_buffhd_to_fill; struct fsg_lun* curlun; } ;
struct fsg_buffhd {struct fsg_buffhd* next; TYPE_1__* inreq; void* state; int /*<<< orphan*/  buf; } ;
typedef  unsigned int ssize_t ;
typedef  unsigned int loff_t ;
struct TYPE_2__ {unsigned int length; scalar_t__ zero; } ;

/* Variables and functions */
 void* BUF_STATE_FULL ; 
 int EINTR ; 
 int EINVAL ; 
 int EIO ; 
 scalar_t__ FSG_BUFLEN ; 
 int /*<<< orphan*/  LDBG (struct fsg_lun*,char*,int,...) ; 
 int READ_6 ; 
 void* SS_INVALID_FIELD_IN_CDB ; 
 void* SS_LOGICAL_BLOCK_ADDRESS_OUT_OF_RANGE ; 
 void* SS_UNRECOVERED_READ_ERROR ; 
 int /*<<< orphan*/  VLDBG (struct fsg_lun*,char*,unsigned int,unsigned long long,int) ; 
 int /*<<< orphan*/  current ; 
 scalar_t__ get_unaligned_be24 (int*) ; 
 scalar_t__ get_unaligned_be32 (int*) ; 
 unsigned int kernel_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int*) ; 
 unsigned int min (unsigned int,scalar_t__) ; 
 unsigned int round_down (unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int sleep_thread (struct fsg_common*,int,struct fsg_buffhd*) ; 
 int /*<<< orphan*/  start_in_transfer (struct fsg_common*,struct fsg_buffhd*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int do_read(struct fsg_common *common)
{
	struct fsg_lun		*curlun = common->curlun;
	u32			lba;
	struct fsg_buffhd	*bh;
	int			rc;
	u32			amount_left;
	loff_t			file_offset, file_offset_tmp;
	unsigned int		amount;
	ssize_t			nread;

	/*
	 * Get the starting Logical Block Address and check that it's
	 * not too big.
	 */
	if (common->cmnd[0] == READ_6)
		lba = get_unaligned_be24(&common->cmnd[1]);
	else {
		lba = get_unaligned_be32(&common->cmnd[2]);

		/*
		 * We allow DPO (Disable Page Out = don't save data in the
		 * cache) and FUA (Force Unit Access = don't read from the
		 * cache), but we don't implement them.
		 */
		if ((common->cmnd[1] & ~0x18) != 0) {
			curlun->sense_data = SS_INVALID_FIELD_IN_CDB;
			return -EINVAL;
		}
	}
	if (lba >= curlun->num_sectors) {
		curlun->sense_data = SS_LOGICAL_BLOCK_ADDRESS_OUT_OF_RANGE;
		return -EINVAL;
	}
	file_offset = ((loff_t) lba) << curlun->blkbits;

	/* Carry out the file reads */
	amount_left = common->data_size_from_cmnd;
	if (unlikely(amount_left == 0))
		return -EIO;		/* No default reply */

	for (;;) {
		/*
		 * Figure out how much we need to read:
		 * Try to read the remaining amount.
		 * But don't read more than the buffer size.
		 * And don't try to read past the end of the file.
		 */
		amount = min(amount_left, FSG_BUFLEN);
		amount = min((loff_t)amount,
			     curlun->file_length - file_offset);

		/* Wait for the next buffer to become available */
		bh = common->next_buffhd_to_fill;
		rc = sleep_thread(common, false, bh);
		if (rc)
			return rc;

		/*
		 * If we were asked to read past the end of file,
		 * end with an empty buffer.
		 */
		if (amount == 0) {
			curlun->sense_data =
					SS_LOGICAL_BLOCK_ADDRESS_OUT_OF_RANGE;
			curlun->sense_data_info =
					file_offset >> curlun->blkbits;
			curlun->info_valid = 1;
			bh->inreq->length = 0;
			bh->state = BUF_STATE_FULL;
			break;
		}

		/* Perform the read */
		file_offset_tmp = file_offset;
		nread = kernel_read(curlun->filp, bh->buf, amount,
				&file_offset_tmp);
		VLDBG(curlun, "file read %u @ %llu -> %d\n", amount,
		      (unsigned long long)file_offset, (int)nread);
		if (signal_pending(current))
			return -EINTR;

		if (nread < 0) {
			LDBG(curlun, "error in file read: %d\n", (int)nread);
			nread = 0;
		} else if (nread < amount) {
			LDBG(curlun, "partial file read: %d/%u\n",
			     (int)nread, amount);
			nread = round_down(nread, curlun->blksize);
		}
		file_offset  += nread;
		amount_left  -= nread;
		common->residue -= nread;

		/*
		 * Except at the end of the transfer, nread will be
		 * equal to the buffer size, which is divisible by the
		 * bulk-in maxpacket size.
		 */
		bh->inreq->length = nread;
		bh->state = BUF_STATE_FULL;

		/* If an error occurred, report it and its position */
		if (nread < amount) {
			curlun->sense_data = SS_UNRECOVERED_READ_ERROR;
			curlun->sense_data_info =
					file_offset >> curlun->blkbits;
			curlun->info_valid = 1;
			break;
		}

		if (amount_left == 0)
			break;		/* No more left to read */

		/* Send this buffer and go read some more */
		bh->inreq->zero = 0;
		if (!start_in_transfer(common, bh))
			/* Don't know what to do if common->fsg is NULL */
			return -EIO;
		common->next_buffhd_to_fill = bh->next;
	}

	return -EIO;		/* No default reply */
}