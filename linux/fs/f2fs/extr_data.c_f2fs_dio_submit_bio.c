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
struct inode {int dummy; } ;
struct f2fs_private_dio {int write; struct f2fs_private_dio* orig_private; int /*<<< orphan*/  orig_end_io; struct inode* inode; } ;
struct bio {int /*<<< orphan*/  bi_status; struct f2fs_private_dio* bi_private; int /*<<< orphan*/  bi_end_io; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_STS_IOERR ; 
 int /*<<< orphan*/  F2FS_DIO_READ ; 
 int /*<<< orphan*/  F2FS_DIO_WRITE ; 
 int /*<<< orphan*/  F2FS_I_SB (struct inode*) ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 scalar_t__ REQ_OP_WRITE ; 
 int /*<<< orphan*/  bio_endio (struct bio*) ; 
 scalar_t__ bio_op (struct bio*) ; 
 int /*<<< orphan*/  f2fs_dio_end_io ; 
 struct f2fs_private_dio* f2fs_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inc_page_count (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  submit_bio (struct bio*) ; 

__attribute__((used)) static void f2fs_dio_submit_bio(struct bio *bio, struct inode *inode,
							loff_t file_offset)
{
	struct f2fs_private_dio *dio;
	bool write = (bio_op(bio) == REQ_OP_WRITE);

	dio = f2fs_kzalloc(F2FS_I_SB(inode),
			sizeof(struct f2fs_private_dio), GFP_NOFS);
	if (!dio)
		goto out;

	dio->inode = inode;
	dio->orig_end_io = bio->bi_end_io;
	dio->orig_private = bio->bi_private;
	dio->write = write;

	bio->bi_end_io = f2fs_dio_end_io;
	bio->bi_private = dio;

	inc_page_count(F2FS_I_SB(inode),
			write ? F2FS_DIO_WRITE : F2FS_DIO_READ);

	submit_bio(bio);
	return;
out:
	bio->bi_status = BLK_STS_IOERR;
	bio_endio(bio);
}