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
struct lbuf {int l_blkno; int /*<<< orphan*/  l_flag; int /*<<< orphan*/  l_ioevent; int /*<<< orphan*/  l_offset; int /*<<< orphan*/  l_page; } ;
struct jfs_log {int l2bsize; scalar_t__ no_integrity; int /*<<< orphan*/  bdev; } ;
struct TYPE_2__ {int bi_sector; scalar_t__ bi_size; } ;
struct bio {TYPE_1__ bi_iter; int /*<<< orphan*/  bi_opf; struct lbuf* bi_private; int /*<<< orphan*/  (* bi_end_io ) (struct bio*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 scalar_t__ LOGPSIZE ; 
 int /*<<< orphan*/  REQ_OP_READ ; 
 int /*<<< orphan*/  bio_add_page (struct bio*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 struct bio* bio_alloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bio_set_dev (struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jfs_info (char*,struct lbuf*,int) ; 
 struct lbuf* lbmAllocate (struct jfs_log*,int) ; 
 int /*<<< orphan*/  lbmIODone (struct bio*) ; 
 int /*<<< orphan*/  lbmREAD ; 
 int /*<<< orphan*/  submit_bio (struct bio*) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int lbmRead(struct jfs_log * log, int pn, struct lbuf ** bpp)
{
	struct bio *bio;
	struct lbuf *bp;

	/*
	 * allocate a log buffer
	 */
	*bpp = bp = lbmAllocate(log, pn);
	jfs_info("lbmRead: bp:0x%p pn:0x%x", bp, pn);

	bp->l_flag |= lbmREAD;

	bio = bio_alloc(GFP_NOFS, 1);

	bio->bi_iter.bi_sector = bp->l_blkno << (log->l2bsize - 9);
	bio_set_dev(bio, log->bdev);

	bio_add_page(bio, bp->l_page, LOGPSIZE, bp->l_offset);
	BUG_ON(bio->bi_iter.bi_size != LOGPSIZE);

	bio->bi_end_io = lbmIODone;
	bio->bi_private = bp;
	bio->bi_opf = REQ_OP_READ;
	/*check if journaling to disk has been disabled*/
	if (log->no_integrity) {
		bio->bi_iter.bi_size = 0;
		lbmIODone(bio);
	} else {
		submit_bio(bio);
	}

	wait_event(bp->l_ioevent, (bp->l_flag != lbmREAD));

	return 0;
}