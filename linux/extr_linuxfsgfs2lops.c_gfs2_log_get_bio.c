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
typedef  int u64 ;
struct gfs2_sbd {int sd_fsb2bb_shift; struct bio* sd_log_bio; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REQ_OP_WRITE ; 
 int bio_end_sector (struct bio*) ; 
 struct bio* gfs2_log_alloc_bio (struct gfs2_sbd*,int) ; 
 int /*<<< orphan*/  gfs2_log_flush_bio (struct gfs2_sbd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct bio *gfs2_log_get_bio(struct gfs2_sbd *sdp, u64 blkno)
{
	struct bio *bio = sdp->sd_log_bio;
	u64 nblk;

	if (bio) {
		nblk = bio_end_sector(bio);
		nblk >>= sdp->sd_fsb2bb_shift;
		if (blkno == nblk)
			return bio;
		gfs2_log_flush_bio(sdp, REQ_OP_WRITE, 0);
	}

	return gfs2_log_alloc_bio(sdp, blkno);
}