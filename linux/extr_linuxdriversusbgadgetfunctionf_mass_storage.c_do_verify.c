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
typedef  scalar_t__ u32 ;
struct fsg_lun {scalar_t__ num_sectors; scalar_t__ blkbits; unsigned int sense_data_info; int info_valid; void* sense_data; int /*<<< orphan*/  blksize; int /*<<< orphan*/  filp; scalar_t__ file_length; } ;
struct fsg_common {int* cmnd; struct fsg_buffhd* next_buffhd_to_fill; struct fsg_lun* curlun; } ;
struct fsg_buffhd {int /*<<< orphan*/  buf; } ;
typedef  unsigned int ssize_t ;
typedef  unsigned int loff_t ;

/* Variables and functions */
 int EINTR ; 
 int EINVAL ; 
 int EIO ; 
 scalar_t__ FSG_BUFLEN ; 
 int /*<<< orphan*/  LDBG (struct fsg_lun*,char*,int,...) ; 
 void* SS_INVALID_FIELD_IN_CDB ; 
 void* SS_LOGICAL_BLOCK_ADDRESS_OUT_OF_RANGE ; 
 void* SS_UNRECOVERED_READ_ERROR ; 
 int /*<<< orphan*/  VLDBG (struct fsg_lun*,char*,unsigned int,unsigned long long,int) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  fsg_lun_fsync_sub (struct fsg_lun*) ; 
 scalar_t__ get_unaligned_be16 (int*) ; 
 scalar_t__ get_unaligned_be32 (int*) ; 
 int /*<<< orphan*/  invalidate_sub (struct fsg_lun*) ; 
 unsigned int kernel_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int*) ; 
 unsigned int min (unsigned int,scalar_t__) ; 
 unsigned int round_down (unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int do_verify(struct fsg_common *common)
{
	struct fsg_lun		*curlun = common->curlun;
	u32			lba;
	u32			verification_length;
	struct fsg_buffhd	*bh = common->next_buffhd_to_fill;
	loff_t			file_offset, file_offset_tmp;
	u32			amount_left;
	unsigned int		amount;
	ssize_t			nread;

	/*
	 * Get the starting Logical Block Address and check that it's
	 * not too big.
	 */
	lba = get_unaligned_be32(&common->cmnd[2]);
	if (lba >= curlun->num_sectors) {
		curlun->sense_data = SS_LOGICAL_BLOCK_ADDRESS_OUT_OF_RANGE;
		return -EINVAL;
	}

	/*
	 * We allow DPO (Disable Page Out = don't save data in the
	 * cache) but we don't implement it.
	 */
	if (common->cmnd[1] & ~0x10) {
		curlun->sense_data = SS_INVALID_FIELD_IN_CDB;
		return -EINVAL;
	}

	verification_length = get_unaligned_be16(&common->cmnd[7]);
	if (unlikely(verification_length == 0))
		return -EIO;		/* No default reply */

	/* Prepare to carry out the file verify */
	amount_left = verification_length << curlun->blkbits;
	file_offset = ((loff_t) lba) << curlun->blkbits;

	/* Write out all the dirty buffers before invalidating them */
	fsg_lun_fsync_sub(curlun);
	if (signal_pending(current))
		return -EINTR;

	invalidate_sub(curlun);
	if (signal_pending(current))
		return -EINTR;

	/* Just try to read the requested blocks */
	while (amount_left > 0) {
		/*
		 * Figure out how much we need to read:
		 * Try to read the remaining amount, but not more than
		 * the buffer size.
		 * And don't try to read past the end of the file.
		 */
		amount = min(amount_left, FSG_BUFLEN);
		amount = min((loff_t)amount,
			     curlun->file_length - file_offset);
		if (amount == 0) {
			curlun->sense_data =
					SS_LOGICAL_BLOCK_ADDRESS_OUT_OF_RANGE;
			curlun->sense_data_info =
				file_offset >> curlun->blkbits;
			curlun->info_valid = 1;
			break;
		}

		/* Perform the read */
		file_offset_tmp = file_offset;
		nread = kernel_read(curlun->filp, bh->buf, amount,
				&file_offset_tmp);
		VLDBG(curlun, "file read %u @ %llu -> %d\n", amount,
				(unsigned long long) file_offset,
				(int) nread);
		if (signal_pending(current))
			return -EINTR;

		if (nread < 0) {
			LDBG(curlun, "error in file verify: %d\n", (int)nread);
			nread = 0;
		} else if (nread < amount) {
			LDBG(curlun, "partial file verify: %d/%u\n",
			     (int)nread, amount);
			nread = round_down(nread, curlun->blksize);
		}
		if (nread == 0) {
			curlun->sense_data = SS_UNRECOVERED_READ_ERROR;
			curlun->sense_data_info =
				file_offset >> curlun->blkbits;
			curlun->info_valid = 1;
			break;
		}
		file_offset += nread;
		amount_left -= nread;
	}
	return 0;
}