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
struct inode {int dummy; } ;
struct btrfs_io_bio {int dummy; } ;
struct btrfs_dio_private {int flags; struct bio* dio_bio; scalar_t__ bytes; scalar_t__ logical_offset; struct inode* inode; } ;
struct bio {int /*<<< orphan*/  bi_status; struct btrfs_dio_private* bi_private; } ;
typedef  int /*<<< orphan*/  blk_status_t ;
struct TYPE_2__ {int /*<<< orphan*/  io_tree; } ;

/* Variables and functions */
 int BTRFS_DIO_ORIG_BIO_SUBMITTED ; 
 TYPE_1__* BTRFS_I (struct inode*) ; 
 int /*<<< orphan*/  bio_put (struct bio*) ; 
 struct btrfs_io_bio* btrfs_io_bio (struct bio*) ; 
 int /*<<< orphan*/  btrfs_io_bio_free_csum (struct btrfs_io_bio*) ; 
 int /*<<< orphan*/  btrfs_subio_endio_read (struct inode*,struct btrfs_io_bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dio_end_io (struct bio*) ; 
 int /*<<< orphan*/  kfree (struct btrfs_dio_private*) ; 
 int /*<<< orphan*/  unlock_extent (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void btrfs_endio_direct_read(struct bio *bio)
{
	struct btrfs_dio_private *dip = bio->bi_private;
	struct inode *inode = dip->inode;
	struct bio *dio_bio;
	struct btrfs_io_bio *io_bio = btrfs_io_bio(bio);
	blk_status_t err = bio->bi_status;

	if (dip->flags & BTRFS_DIO_ORIG_BIO_SUBMITTED)
		err = btrfs_subio_endio_read(inode, io_bio, err);

	unlock_extent(&BTRFS_I(inode)->io_tree, dip->logical_offset,
		      dip->logical_offset + dip->bytes - 1);
	dio_bio = dip->dio_bio;

	kfree(dip);

	dio_bio->bi_status = err;
	dio_end_io(dio_bio);
	btrfs_io_bio_free_csum(io_bio);
	bio_put(bio);
}