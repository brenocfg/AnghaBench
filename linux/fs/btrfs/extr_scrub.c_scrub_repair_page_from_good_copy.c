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
struct scrub_page {int physical; TYPE_4__* dev; int /*<<< orphan*/ * page; scalar_t__ io_error; } ;
struct scrub_block {scalar_t__ checksum_error; scalar_t__ header_error; TYPE_1__* sctx; struct scrub_page** pagev; } ;
struct TYPE_7__ {int /*<<< orphan*/  num_write_errors; } ;
struct btrfs_fs_info {TYPE_3__ dev_replace; } ;
struct TYPE_6__ {int bi_sector; } ;
struct bio {int /*<<< orphan*/  bi_opf; TYPE_2__ bi_iter; } ;
struct TYPE_8__ {int /*<<< orphan*/  bdev; } ;
struct TYPE_5__ {struct btrfs_fs_info* fs_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_DEV_STAT_WRITE_ERRS ; 
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int EIO ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  REQ_OP_WRITE ; 
 int /*<<< orphan*/  atomic64_inc (int /*<<< orphan*/ *) ; 
 int bio_add_page (struct bio*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_put (struct bio*) ; 
 int /*<<< orphan*/  bio_set_dev (struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_dev_stat_inc_and_print (TYPE_4__*,int /*<<< orphan*/ ) ; 
 struct bio* btrfs_io_bio_alloc (int) ; 
 int /*<<< orphan*/  btrfs_warn_rl (struct btrfs_fs_info*,char*) ; 
 scalar_t__ btrfsic_submit_bio_wait (struct bio*) ; 

__attribute__((used)) static int scrub_repair_page_from_good_copy(struct scrub_block *sblock_bad,
					    struct scrub_block *sblock_good,
					    int page_num, int force_write)
{
	struct scrub_page *page_bad = sblock_bad->pagev[page_num];
	struct scrub_page *page_good = sblock_good->pagev[page_num];
	struct btrfs_fs_info *fs_info = sblock_bad->sctx->fs_info;

	BUG_ON(page_bad->page == NULL);
	BUG_ON(page_good->page == NULL);
	if (force_write || sblock_bad->header_error ||
	    sblock_bad->checksum_error || page_bad->io_error) {
		struct bio *bio;
		int ret;

		if (!page_bad->dev->bdev) {
			btrfs_warn_rl(fs_info,
				"scrub_repair_page_from_good_copy(bdev == NULL) is unexpected");
			return -EIO;
		}

		bio = btrfs_io_bio_alloc(1);
		bio_set_dev(bio, page_bad->dev->bdev);
		bio->bi_iter.bi_sector = page_bad->physical >> 9;
		bio->bi_opf = REQ_OP_WRITE;

		ret = bio_add_page(bio, page_good->page, PAGE_SIZE, 0);
		if (PAGE_SIZE != ret) {
			bio_put(bio);
			return -EIO;
		}

		if (btrfsic_submit_bio_wait(bio)) {
			btrfs_dev_stat_inc_and_print(page_bad->dev,
				BTRFS_DEV_STAT_WRITE_ERRS);
			atomic64_inc(&fs_info->dev_replace.num_write_errors);
			bio_put(bio);
			return -EIO;
		}
		bio_put(bio);
	}

	return 0;
}