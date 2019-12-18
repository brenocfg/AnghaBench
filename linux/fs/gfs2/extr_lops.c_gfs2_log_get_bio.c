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
struct gfs2_sbd {int sd_fsb2bb_shift; } ;
struct bio {int dummy; } ;
typedef  int /*<<< orphan*/  bio_end_io_t ;

/* Variables and functions */
 int bio_end_sector (struct bio*) ; 
 struct bio* gfs2_log_alloc_bio (struct gfs2_sbd*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gfs2_log_submit_bio (struct bio**,int) ; 

__attribute__((used)) static struct bio *gfs2_log_get_bio(struct gfs2_sbd *sdp, u64 blkno,
				    struct bio **biop, int op,
				    bio_end_io_t *end_io, bool flush)
{
	struct bio *bio = *biop;

	if (bio) {
		u64 nblk;

		nblk = bio_end_sector(bio);
		nblk >>= sdp->sd_fsb2bb_shift;
		if (blkno == nblk && !flush)
			return bio;
		gfs2_log_submit_bio(biop, op);
	}

	*biop = gfs2_log_alloc_bio(sdp, blkno, end_io);
	return *biop;
}