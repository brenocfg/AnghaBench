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
typedef  int u32 ;
struct TYPE_2__ {int sb_bsize_shift; int sb_bsize; } ;
struct gfs2_sbd {int sd_fsb2bb_shift; int sd_fsb2bb; int sd_diptrs; int sd_inptrs; int sd_jbsize; int sd_hash_bsize; int sd_hash_bsize_shift; int sd_hash_ptrs; int sd_qc_per_block; int sd_blocks_per_bitmap; int sd_max_dirres; int* sd_heightsize; unsigned int sd_max_height; int sd_max_dents_per_leaf; TYPE_1__ sd_sb; } ;
struct gfs2_quota_change {int dummy; } ;
struct gfs2_meta_header {int dummy; } ;
struct gfs2_leaf {int dummy; } ;
struct gfs2_dinode {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 int DIV_ROUND_UP (int,int) ; 
 int GFS2_BASIC_BLOCK_SHIFT ; 
 int GFS2_DIR_MAX_DEPTH ; 
 unsigned int GFS2_MAX_META_HEIGHT ; 
 int GFS2_MIN_DIRENT_SIZE ; 
 int GFS2_NBBY ; 
 int GFS2_SB_ADDR ; 
 int do_div (int,int) ; 
 int /*<<< orphan*/  fs_err (struct gfs2_sbd*,char*) ; 
 int /*<<< orphan*/  gfs2_assert (struct gfs2_sbd*,int) ; 
 int gfs2_read_super (struct gfs2_sbd*,int,int) ; 

__attribute__((used)) static int gfs2_read_sb(struct gfs2_sbd *sdp, int silent)
{
	u32 hash_blocks, ind_blocks, leaf_blocks;
	u32 tmp_blocks;
	unsigned int x;
	int error;

	error = gfs2_read_super(sdp, GFS2_SB_ADDR >> sdp->sd_fsb2bb_shift, silent);
	if (error) {
		if (!silent)
			fs_err(sdp, "can't read superblock\n");
		return error;
	}

	sdp->sd_fsb2bb_shift = sdp->sd_sb.sb_bsize_shift -
			       GFS2_BASIC_BLOCK_SHIFT;
	sdp->sd_fsb2bb = BIT(sdp->sd_fsb2bb_shift);
	sdp->sd_diptrs = (sdp->sd_sb.sb_bsize -
			  sizeof(struct gfs2_dinode)) / sizeof(u64);
	sdp->sd_inptrs = (sdp->sd_sb.sb_bsize -
			  sizeof(struct gfs2_meta_header)) / sizeof(u64);
	sdp->sd_jbsize = sdp->sd_sb.sb_bsize - sizeof(struct gfs2_meta_header);
	sdp->sd_hash_bsize = sdp->sd_sb.sb_bsize / 2;
	sdp->sd_hash_bsize_shift = sdp->sd_sb.sb_bsize_shift - 1;
	sdp->sd_hash_ptrs = sdp->sd_hash_bsize / sizeof(u64);
	sdp->sd_qc_per_block = (sdp->sd_sb.sb_bsize -
				sizeof(struct gfs2_meta_header)) /
			        sizeof(struct gfs2_quota_change);
	sdp->sd_blocks_per_bitmap = (sdp->sd_sb.sb_bsize -
				     sizeof(struct gfs2_meta_header))
		* GFS2_NBBY; /* not the rgrp bitmap, subsequent bitmaps only */

	/* Compute maximum reservation required to add a entry to a directory */

	hash_blocks = DIV_ROUND_UP(sizeof(u64) * BIT(GFS2_DIR_MAX_DEPTH),
			     sdp->sd_jbsize);

	ind_blocks = 0;
	for (tmp_blocks = hash_blocks; tmp_blocks > sdp->sd_diptrs;) {
		tmp_blocks = DIV_ROUND_UP(tmp_blocks, sdp->sd_inptrs);
		ind_blocks += tmp_blocks;
	}

	leaf_blocks = 2 + GFS2_DIR_MAX_DEPTH;

	sdp->sd_max_dirres = hash_blocks + ind_blocks + leaf_blocks;

	sdp->sd_heightsize[0] = sdp->sd_sb.sb_bsize -
				sizeof(struct gfs2_dinode);
	sdp->sd_heightsize[1] = sdp->sd_sb.sb_bsize * sdp->sd_diptrs;
	for (x = 2;; x++) {
		u64 space, d;
		u32 m;

		space = sdp->sd_heightsize[x - 1] * sdp->sd_inptrs;
		d = space;
		m = do_div(d, sdp->sd_inptrs);

		if (d != sdp->sd_heightsize[x - 1] || m)
			break;
		sdp->sd_heightsize[x] = space;
	}
	sdp->sd_max_height = x;
	sdp->sd_heightsize[x] = ~0;
	gfs2_assert(sdp, sdp->sd_max_height <= GFS2_MAX_META_HEIGHT);

	sdp->sd_max_dents_per_leaf = (sdp->sd_sb.sb_bsize -
				      sizeof(struct gfs2_leaf)) /
				     GFS2_MIN_DIRENT_SIZE;
	return 0;
}