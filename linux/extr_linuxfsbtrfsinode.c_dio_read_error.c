#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct page {int dummy; } ;
struct io_failure_record {int /*<<< orphan*/  this_mirror; int /*<<< orphan*/  in_validation; } ;
struct inode {TYPE_1__* i_sb; } ;
struct extent_io_tree {int dummy; } ;
struct bio_vec {scalar_t__ bv_len; } ;
struct bio {unsigned int bi_opf; } ;
typedef  scalar_t__ blk_status_t ;
typedef  int /*<<< orphan*/  bio_end_io_t ;
struct TYPE_8__ {TYPE_2__* root; struct extent_io_tree io_failure_tree; struct extent_io_tree io_tree; } ;
struct TYPE_7__ {int logical; } ;
struct TYPE_6__ {int /*<<< orphan*/  fs_info; } ;
struct TYPE_5__ {int s_blocksize_bits; } ;

/* Variables and functions */
 scalar_t__ BLK_STS_IOERR ; 
 TYPE_4__* BTRFS_I (struct inode*) ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned int REQ_FAILFAST_DEV ; 
 unsigned int REQ_OP_READ ; 
 scalar_t__ REQ_OP_WRITE ; 
 int /*<<< orphan*/  bio_get_first_bvec (struct bio*,struct bio_vec*) ; 
 scalar_t__ bio_op (struct bio*) ; 
 int /*<<< orphan*/  bio_put (struct bio*) ; 
 int bio_segments (struct bio*) ; 
 int btrfs_check_dio_repairable (struct inode*,struct bio*,struct io_failure_record*,int) ; 
 struct bio* btrfs_create_repair_bio (struct inode*,struct bio*,struct io_failure_record*,struct page*,unsigned int,int,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  btrfs_debug (int /*<<< orphan*/ ,char*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int btrfs_get_io_failure_record (struct inode*,int,int,struct io_failure_record**) ; 
 scalar_t__ btrfs_inode_sectorsize (struct inode*) ; 
 TYPE_3__* btrfs_io_bio (struct bio*) ; 
 scalar_t__ errno_to_blk_status (int) ; 
 int /*<<< orphan*/  free_io_failure (struct extent_io_tree*,struct extent_io_tree*,struct io_failure_record*) ; 
 scalar_t__ submit_dio_repair_bio (struct inode*,struct bio*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static blk_status_t dio_read_error(struct inode *inode, struct bio *failed_bio,
				   struct page *page, unsigned int pgoff,
				   u64 start, u64 end, int failed_mirror,
				   bio_end_io_t *repair_endio, void *repair_arg)
{
	struct io_failure_record *failrec;
	struct extent_io_tree *io_tree = &BTRFS_I(inode)->io_tree;
	struct extent_io_tree *failure_tree = &BTRFS_I(inode)->io_failure_tree;
	struct bio *bio;
	int isector;
	unsigned int read_mode = 0;
	int segs;
	int ret;
	blk_status_t status;
	struct bio_vec bvec;

	BUG_ON(bio_op(failed_bio) == REQ_OP_WRITE);

	ret = btrfs_get_io_failure_record(inode, start, end, &failrec);
	if (ret)
		return errno_to_blk_status(ret);

	ret = btrfs_check_dio_repairable(inode, failed_bio, failrec,
					 failed_mirror);
	if (!ret) {
		free_io_failure(failure_tree, io_tree, failrec);
		return BLK_STS_IOERR;
	}

	segs = bio_segments(failed_bio);
	bio_get_first_bvec(failed_bio, &bvec);
	if (segs > 1 ||
	    (bvec.bv_len > btrfs_inode_sectorsize(inode)))
		read_mode |= REQ_FAILFAST_DEV;

	isector = start - btrfs_io_bio(failed_bio)->logical;
	isector >>= inode->i_sb->s_blocksize_bits;
	bio = btrfs_create_repair_bio(inode, failed_bio, failrec, page,
				pgoff, isector, repair_endio, repair_arg);
	bio->bi_opf = REQ_OP_READ | read_mode;

	btrfs_debug(BTRFS_I(inode)->root->fs_info,
		    "repair DIO read error: submitting new dio read[%#x] to this_mirror=%d, in_validation=%d",
		    read_mode, failrec->this_mirror, failrec->in_validation);

	status = submit_dio_repair_bio(inode, bio, failrec->this_mirror);
	if (status) {
		free_io_failure(failure_tree, io_tree, failrec);
		bio_put(bio);
	}

	return status;
}