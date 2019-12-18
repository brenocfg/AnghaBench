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
struct gfs2_sbd {int /*<<< orphan*/  sd_log_bio; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REQ_OP_WRITE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int bio_add_page (struct bio*,struct page*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  gfs2_end_log_write ; 
 struct bio* gfs2_log_get_bio (struct gfs2_sbd*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void gfs2_log_write(struct gfs2_sbd *sdp, struct page *page,
		    unsigned size, unsigned offset, u64 blkno)
{
	struct bio *bio;
	int ret;

	bio = gfs2_log_get_bio(sdp, blkno, &sdp->sd_log_bio, REQ_OP_WRITE,
			       gfs2_end_log_write, false);
	ret = bio_add_page(bio, page, size, offset);
	if (ret == 0) {
		bio = gfs2_log_get_bio(sdp, blkno, &sdp->sd_log_bio,
				       REQ_OP_WRITE, gfs2_end_log_write, true);
		ret = bio_add_page(bio, page, size, offset);
		WARN_ON(ret == 0);
	}
}