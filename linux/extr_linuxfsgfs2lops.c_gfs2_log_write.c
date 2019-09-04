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
typedef  int /*<<< orphan*/  u64 ;
struct page {int dummy; } ;
struct gfs2_sbd {int dummy; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REQ_OP_WRITE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int bio_add_page (struct bio*,struct page*,unsigned int,unsigned int) ; 
 struct bio* gfs2_log_alloc_bio (struct gfs2_sbd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_log_flush_bio (struct gfs2_sbd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct bio* gfs2_log_get_bio (struct gfs2_sbd*,int /*<<< orphan*/ ) ; 

void gfs2_log_write(struct gfs2_sbd *sdp, struct page *page,
		    unsigned size, unsigned offset, u64 blkno)
{
	struct bio *bio;
	int ret;

	bio = gfs2_log_get_bio(sdp, blkno);
	ret = bio_add_page(bio, page, size, offset);
	if (ret == 0) {
		gfs2_log_flush_bio(sdp, REQ_OP_WRITE, 0);
		bio = gfs2_log_alloc_bio(sdp, blkno);
		ret = bio_add_page(bio, page, size, offset);
		WARN_ON(ret == 0);
	}
}