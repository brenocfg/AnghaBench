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
struct lbuf {int l_blkno; int /*<<< orphan*/  l_offset; int /*<<< orphan*/  l_page; struct jfs_log* l_log; } ;
struct jfs_log {int l2bsize; scalar_t__ no_integrity; int /*<<< orphan*/  bdev; } ;
struct TYPE_3__ {int bi_sector; scalar_t__ bi_size; } ;
struct bio {int bi_opf; TYPE_1__ bi_iter; struct lbuf* bi_private; int /*<<< orphan*/  (* bi_end_io ) (struct bio*) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  submitted; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  INCREMENT (int /*<<< orphan*/ ) ; 
 scalar_t__ LOGPSIZE ; 
 int REQ_OP_WRITE ; 
 int REQ_SYNC ; 
 int /*<<< orphan*/  bio_add_page (struct bio*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 struct bio* bio_alloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bio_set_dev (struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jfs_info (char*) ; 
 int /*<<< orphan*/  lbmIODone (struct bio*) ; 
 TYPE_2__ lmStat ; 
 int /*<<< orphan*/  submit_bio (struct bio*) ; 

__attribute__((used)) static void lbmStartIO(struct lbuf * bp)
{
	struct bio *bio;
	struct jfs_log *log = bp->l_log;

	jfs_info("lbmStartIO");

	bio = bio_alloc(GFP_NOFS, 1);
	bio->bi_iter.bi_sector = bp->l_blkno << (log->l2bsize - 9);
	bio_set_dev(bio, log->bdev);

	bio_add_page(bio, bp->l_page, LOGPSIZE, bp->l_offset);
	BUG_ON(bio->bi_iter.bi_size != LOGPSIZE);

	bio->bi_end_io = lbmIODone;
	bio->bi_private = bp;
	bio->bi_opf = REQ_OP_WRITE | REQ_SYNC;

	/* check if journaling to disk has been disabled */
	if (log->no_integrity) {
		bio->bi_iter.bi_size = 0;
		lbmIODone(bio);
	} else {
		submit_bio(bio);
		INCREMENT(lmStat.submitted);
	}
}