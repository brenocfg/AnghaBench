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
typedef  int u32 ;
struct TYPE_2__ {int sb_bsize; } ;
struct gfs2_sbd {TYPE_1__ sd_sb; } ;
struct gfs2_rgrpd {int rd_length; int rd_bitbytes; int rd_data; struct gfs2_bitmap* rd_bits; struct gfs2_sbd* rd_sbd; } ;
struct gfs2_rgrp {int dummy; } ;
struct gfs2_meta_header {int dummy; } ;
struct gfs2_bitmap {int bi_offset; int bi_start; int bi_bytes; int bi_blocks; scalar_t__ bi_flags; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int GFS2_NBBY ; 
 int /*<<< orphan*/  fs_err (struct gfs2_sbd*,char*,int,int,int) ; 
 scalar_t__ gfs2_consist_rgrpd (struct gfs2_rgrpd*) ; 
 int /*<<< orphan*/  gfs2_rindex_print (struct gfs2_rgrpd*) ; 
 struct gfs2_bitmap* kcalloc (int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int compute_bitstructs(struct gfs2_rgrpd *rgd)
{
	struct gfs2_sbd *sdp = rgd->rd_sbd;
	struct gfs2_bitmap *bi;
	u32 length = rgd->rd_length; /* # blocks in hdr & bitmap */
	u32 bytes_left, bytes;
	int x;

	if (!length)
		return -EINVAL;

	rgd->rd_bits = kcalloc(length, sizeof(struct gfs2_bitmap), GFP_NOFS);
	if (!rgd->rd_bits)
		return -ENOMEM;

	bytes_left = rgd->rd_bitbytes;

	for (x = 0; x < length; x++) {
		bi = rgd->rd_bits + x;

		bi->bi_flags = 0;
		/* small rgrp; bitmap stored completely in header block */
		if (length == 1) {
			bytes = bytes_left;
			bi->bi_offset = sizeof(struct gfs2_rgrp);
			bi->bi_start = 0;
			bi->bi_bytes = bytes;
			bi->bi_blocks = bytes * GFS2_NBBY;
		/* header block */
		} else if (x == 0) {
			bytes = sdp->sd_sb.sb_bsize - sizeof(struct gfs2_rgrp);
			bi->bi_offset = sizeof(struct gfs2_rgrp);
			bi->bi_start = 0;
			bi->bi_bytes = bytes;
			bi->bi_blocks = bytes * GFS2_NBBY;
		/* last block */
		} else if (x + 1 == length) {
			bytes = bytes_left;
			bi->bi_offset = sizeof(struct gfs2_meta_header);
			bi->bi_start = rgd->rd_bitbytes - bytes_left;
			bi->bi_bytes = bytes;
			bi->bi_blocks = bytes * GFS2_NBBY;
		/* other blocks */
		} else {
			bytes = sdp->sd_sb.sb_bsize -
				sizeof(struct gfs2_meta_header);
			bi->bi_offset = sizeof(struct gfs2_meta_header);
			bi->bi_start = rgd->rd_bitbytes - bytes_left;
			bi->bi_bytes = bytes;
			bi->bi_blocks = bytes * GFS2_NBBY;
		}

		bytes_left -= bytes;
	}

	if (bytes_left) {
		gfs2_consist_rgrpd(rgd);
		return -EIO;
	}
	bi = rgd->rd_bits + (length - 1);
	if ((bi->bi_start + bi->bi_bytes) * GFS2_NBBY != rgd->rd_data) {
		if (gfs2_consist_rgrpd(rgd)) {
			gfs2_rindex_print(rgd);
			fs_err(sdp, "start=%u len=%u offset=%u\n",
			       bi->bi_start, bi->bi_bytes, bi->bi_offset);
		}
		return -EIO;
	}

	return 0;
}