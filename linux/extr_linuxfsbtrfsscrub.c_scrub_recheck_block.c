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
struct scrub_page {int io_error; int physical; int /*<<< orphan*/  page; TYPE_1__* dev; } ;
struct scrub_block {int no_io_error_seen; int page_count; struct scrub_page** pagev; } ;
struct btrfs_fs_info {int dummy; } ;
struct TYPE_4__ {int bi_sector; } ;
struct bio {int /*<<< orphan*/  bi_opf; TYPE_2__ bi_iter; } ;
struct TYPE_3__ {int /*<<< orphan*/ * bdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  REQ_OP_READ ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  bio_add_page (struct bio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_put (struct bio*) ; 
 int /*<<< orphan*/  bio_set_dev (struct bio*,int /*<<< orphan*/ *) ; 
 struct bio* btrfs_io_bio_alloc (int) ; 
 scalar_t__ btrfsic_submit_bio_wait (struct bio*) ; 
 scalar_t__ scrub_is_page_on_raid56 (struct scrub_page*) ; 
 int /*<<< orphan*/  scrub_recheck_block_checksum (struct scrub_block*) ; 
 void scrub_recheck_block_on_raid56 (struct btrfs_fs_info*,struct scrub_block*) ; 

__attribute__((used)) static void scrub_recheck_block(struct btrfs_fs_info *fs_info,
				struct scrub_block *sblock,
				int retry_failed_mirror)
{
	int page_num;

	sblock->no_io_error_seen = 1;

	/* short cut for raid56 */
	if (!retry_failed_mirror && scrub_is_page_on_raid56(sblock->pagev[0]))
		return scrub_recheck_block_on_raid56(fs_info, sblock);

	for (page_num = 0; page_num < sblock->page_count; page_num++) {
		struct bio *bio;
		struct scrub_page *page = sblock->pagev[page_num];

		if (page->dev->bdev == NULL) {
			page->io_error = 1;
			sblock->no_io_error_seen = 0;
			continue;
		}

		WARN_ON(!page->page);
		bio = btrfs_io_bio_alloc(1);
		bio_set_dev(bio, page->dev->bdev);

		bio_add_page(bio, page->page, PAGE_SIZE, 0);
		bio->bi_iter.bi_sector = page->physical >> 9;
		bio->bi_opf = REQ_OP_READ;

		if (btrfsic_submit_bio_wait(bio)) {
			page->io_error = 1;
			sblock->no_io_error_seen = 0;
		}

		bio_put(bio);
	}

	if (sblock->no_io_error_seen)
		scrub_recheck_block_checksum(sblock);
}