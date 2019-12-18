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
typedef  int u64 ;
struct super_block {int s_blocksize; int /*<<< orphan*/  s_bdev; } ;
struct gfs2_sbd {struct super_block* sd_vfs; } ;
struct TYPE_2__ {int bi_sector; } ;
struct bio {struct gfs2_sbd* bi_private; int /*<<< orphan*/ * bi_end_io; TYPE_1__ bi_iter; } ;
typedef  int /*<<< orphan*/  bio_end_io_t ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_MAX_PAGES ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 struct bio* bio_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_set_dev (struct bio*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct bio *gfs2_log_alloc_bio(struct gfs2_sbd *sdp, u64 blkno,
				      bio_end_io_t *end_io)
{
	struct super_block *sb = sdp->sd_vfs;
	struct bio *bio = bio_alloc(GFP_NOIO, BIO_MAX_PAGES);

	bio->bi_iter.bi_sector = blkno * (sb->s_blocksize >> 9);
	bio_set_dev(bio, sb->s_bdev);
	bio->bi_end_io = end_io;
	bio->bi_private = sdp;

	return bio;
}