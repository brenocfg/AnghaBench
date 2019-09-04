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
struct scrub_page {int physical_for_dev_replace; scalar_t__ logical; int /*<<< orphan*/  page; } ;
struct scrub_ctx {scalar_t__ pages_per_wr_bio; int /*<<< orphan*/  wr_lock; TYPE_1__* wr_tgtdev; struct scrub_bio* wr_curr_bio; } ;
struct scrub_bio {int page_count; int physical; scalar_t__ logical; struct scrub_page** pagev; struct bio* bio; scalar_t__ status; TYPE_1__* dev; struct scrub_ctx* sctx; } ;
struct TYPE_4__ {int bi_sector; } ;
struct bio {int /*<<< orphan*/  bi_opf; TYPE_2__ bi_iter; int /*<<< orphan*/  bi_end_io; struct scrub_bio* bi_private; } ;
struct TYPE_3__ {int /*<<< orphan*/  bdev; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  REQ_OP_WRITE ; 
 int bio_add_page (struct bio*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_put (struct bio*) ; 
 int /*<<< orphan*/  bio_set_dev (struct bio*,int /*<<< orphan*/ ) ; 
 struct bio* btrfs_io_bio_alloc (scalar_t__) ; 
 struct scrub_bio* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scrub_page_get (struct scrub_page*) ; 
 int /*<<< orphan*/  scrub_wr_bio_end_io ; 
 int /*<<< orphan*/  scrub_wr_submit (struct scrub_ctx*) ; 

__attribute__((used)) static int scrub_add_page_to_wr_bio(struct scrub_ctx *sctx,
				    struct scrub_page *spage)
{
	struct scrub_bio *sbio;
	int ret;

	mutex_lock(&sctx->wr_lock);
again:
	if (!sctx->wr_curr_bio) {
		sctx->wr_curr_bio = kzalloc(sizeof(*sctx->wr_curr_bio),
					      GFP_KERNEL);
		if (!sctx->wr_curr_bio) {
			mutex_unlock(&sctx->wr_lock);
			return -ENOMEM;
		}
		sctx->wr_curr_bio->sctx = sctx;
		sctx->wr_curr_bio->page_count = 0;
	}
	sbio = sctx->wr_curr_bio;
	if (sbio->page_count == 0) {
		struct bio *bio;

		sbio->physical = spage->physical_for_dev_replace;
		sbio->logical = spage->logical;
		sbio->dev = sctx->wr_tgtdev;
		bio = sbio->bio;
		if (!bio) {
			bio = btrfs_io_bio_alloc(sctx->pages_per_wr_bio);
			sbio->bio = bio;
		}

		bio->bi_private = sbio;
		bio->bi_end_io = scrub_wr_bio_end_io;
		bio_set_dev(bio, sbio->dev->bdev);
		bio->bi_iter.bi_sector = sbio->physical >> 9;
		bio->bi_opf = REQ_OP_WRITE;
		sbio->status = 0;
	} else if (sbio->physical + sbio->page_count * PAGE_SIZE !=
		   spage->physical_for_dev_replace ||
		   sbio->logical + sbio->page_count * PAGE_SIZE !=
		   spage->logical) {
		scrub_wr_submit(sctx);
		goto again;
	}

	ret = bio_add_page(sbio->bio, spage->page, PAGE_SIZE, 0);
	if (ret != PAGE_SIZE) {
		if (sbio->page_count < 1) {
			bio_put(sbio->bio);
			sbio->bio = NULL;
			mutex_unlock(&sctx->wr_lock);
			return -EIO;
		}
		scrub_wr_submit(sctx);
		goto again;
	}

	sbio->pagev[sbio->page_count] = spage;
	scrub_page_get(spage);
	sbio->page_count++;
	if (sbio->page_count == sctx->pages_per_wr_bio)
		scrub_wr_submit(sctx);
	mutex_unlock(&sctx->wr_lock);

	return 0;
}