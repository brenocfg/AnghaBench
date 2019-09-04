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
struct xfs_ioend {struct bio* io_bio; TYPE_1__* io_inode; } ;
struct writeback_control {int dummy; } ;
struct block_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  bi_sector; } ;
struct bio {int bi_opf; int /*<<< orphan*/  bi_write_hint; TYPE_2__ bi_iter; } ;
typedef  int /*<<< orphan*/  sector_t ;
struct TYPE_3__ {int /*<<< orphan*/  i_write_hint; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_MAX_PAGES ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int REQ_OP_WRITE ; 
 struct bio* bio_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_chain (struct bio*,struct bio*) ; 
 int /*<<< orphan*/  bio_get (struct bio*) ; 
 int /*<<< orphan*/  bio_set_dev (struct bio*,struct block_device*) ; 
 int /*<<< orphan*/  submit_bio (struct bio*) ; 
 int wbc_to_write_flags (struct writeback_control*) ; 

__attribute__((used)) static void
xfs_chain_bio(
	struct xfs_ioend	*ioend,
	struct writeback_control *wbc,
	struct block_device	*bdev,
	sector_t		sector)
{
	struct bio *new;

	new = bio_alloc(GFP_NOFS, BIO_MAX_PAGES);
	bio_set_dev(new, bdev);
	new->bi_iter.bi_sector = sector;
	bio_chain(ioend->io_bio, new);
	bio_get(ioend->io_bio);		/* for xfs_destroy_ioend */
	ioend->io_bio->bi_opf = REQ_OP_WRITE | wbc_to_write_flags(wbc);
	ioend->io_bio->bi_write_hint = ioend->io_inode->i_write_hint;
	submit_bio(ioend->io_bio);
	ioend->io_bio = new;
}