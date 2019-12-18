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
struct super_block {int s_blocksize; int /*<<< orphan*/  s_bdev; } ;
struct page {int dummy; } ;
struct gfs2_sbd {struct super_block* sd_vfs; } ;
struct gfs2_sb {int dummy; } ;
struct TYPE_2__ {int bi_sector; } ;
struct bio {struct page* bi_private; int /*<<< orphan*/  bi_end_io; TYPE_1__ bi_iter; } ;
typedef  int sector_t ;

/* Variables and functions */
 int /*<<< orphan*/  ClearPageDirty (struct page*) ; 
 int /*<<< orphan*/  ClearPageUptodate (struct page*) ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  PageUptodate (struct page*) ; 
 int /*<<< orphan*/  REQ_META ; 
 int /*<<< orphan*/  REQ_OP_READ ; 
 int /*<<< orphan*/  __free_page (struct page*) ; 
 struct page* alloc_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_add_page (struct bio*,struct page*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct bio* bio_alloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bio_put (struct bio*) ; 
 int /*<<< orphan*/  bio_set_dev (struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_set_op_attrs (struct bio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  end_bio_io_page ; 
 int gfs2_check_sb (struct gfs2_sbd*,int) ; 
 int /*<<< orphan*/  gfs2_sb_in (struct gfs2_sbd*,struct gfs2_sb*) ; 
 struct gfs2_sb* kmap (struct page*) ; 
 int /*<<< orphan*/  kunmap (struct page*) ; 
 int /*<<< orphan*/  lock_page (struct page*) ; 
 int /*<<< orphan*/  submit_bio (struct bio*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wait_on_page_locked (struct page*) ; 

__attribute__((used)) static int gfs2_read_super(struct gfs2_sbd *sdp, sector_t sector, int silent)
{
	struct super_block *sb = sdp->sd_vfs;
	struct gfs2_sb *p;
	struct page *page;
	struct bio *bio;

	page = alloc_page(GFP_NOFS);
	if (unlikely(!page))
		return -ENOMEM;

	ClearPageUptodate(page);
	ClearPageDirty(page);
	lock_page(page);

	bio = bio_alloc(GFP_NOFS, 1);
	bio->bi_iter.bi_sector = sector * (sb->s_blocksize >> 9);
	bio_set_dev(bio, sb->s_bdev);
	bio_add_page(bio, page, PAGE_SIZE, 0);

	bio->bi_end_io = end_bio_io_page;
	bio->bi_private = page;
	bio_set_op_attrs(bio, REQ_OP_READ, REQ_META);
	submit_bio(bio);
	wait_on_page_locked(page);
	bio_put(bio);
	if (!PageUptodate(page)) {
		__free_page(page);
		return -EIO;
	}
	p = kmap(page);
	gfs2_sb_in(sdp, p);
	kunmap(page);
	__free_page(page);
	return gfs2_check_sb(sdp, silent);
}