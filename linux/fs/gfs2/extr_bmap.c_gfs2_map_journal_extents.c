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
typedef  unsigned int u64 ;
struct TYPE_3__ {unsigned int sb_bsize_shift; } ;
struct gfs2_sbd {TYPE_1__ sd_sb; } ;
struct gfs2_jdesc {scalar_t__ nr_extents; int /*<<< orphan*/  jd_inode; int /*<<< orphan*/  jd_jid; int /*<<< orphan*/  extent_list; } ;
struct TYPE_4__ {unsigned int i_blkbits; } ;
struct gfs2_inode {TYPE_2__ i_inode; } ;
struct buffer_head {unsigned int b_size; scalar_t__ b_state; scalar_t__ b_blocknr; } ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 struct gfs2_inode* GFS2_I (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  buffer_mapped (struct buffer_head*) ; 
 int /*<<< orphan*/  fs_info (struct gfs2_sbd*,char*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fs_warn (struct gfs2_sbd*,char*,int,unsigned long long,unsigned long long,scalar_t__,...) ; 
 int gfs2_add_jextent (struct gfs2_jdesc*,unsigned int,scalar_t__,unsigned int) ; 
 int gfs2_block_map (int /*<<< orphan*/ ,unsigned int,struct buffer_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_free_journal_extents (struct gfs2_jdesc*) ; 
 unsigned int i_size_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  ktime_ms_delta (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 

int gfs2_map_journal_extents(struct gfs2_sbd *sdp, struct gfs2_jdesc *jd)
{
	u64 lblock = 0;
	u64 lblock_stop;
	struct gfs2_inode *ip = GFS2_I(jd->jd_inode);
	struct buffer_head bh;
	unsigned int shift = sdp->sd_sb.sb_bsize_shift;
	u64 size;
	int rc;
	ktime_t start, end;

	start = ktime_get();
	lblock_stop = i_size_read(jd->jd_inode) >> shift;
	size = (lblock_stop - lblock) << shift;
	jd->nr_extents = 0;
	WARN_ON(!list_empty(&jd->extent_list));

	do {
		bh.b_state = 0;
		bh.b_blocknr = 0;
		bh.b_size = size;
		rc = gfs2_block_map(jd->jd_inode, lblock, &bh, 0);
		if (rc || !buffer_mapped(&bh))
			goto fail;
		rc = gfs2_add_jextent(jd, lblock, bh.b_blocknr, bh.b_size >> shift);
		if (rc)
			goto fail;
		size -= bh.b_size;
		lblock += (bh.b_size >> ip->i_inode.i_blkbits);
	} while(size > 0);

	end = ktime_get();
	fs_info(sdp, "journal %d mapped with %u extents in %lldms\n", jd->jd_jid,
		jd->nr_extents, ktime_ms_delta(end, start));
	return 0;

fail:
	fs_warn(sdp, "error %d mapping journal %u at offset %llu (extent %u)\n",
		rc, jd->jd_jid,
		(unsigned long long)(i_size_read(jd->jd_inode) - size),
		jd->nr_extents);
	fs_warn(sdp, "bmap=%d lblock=%llu block=%llu, state=0x%08lx, size=%llu\n",
		rc, (unsigned long long)lblock, (unsigned long long)bh.b_blocknr,
		bh.b_state, (unsigned long long)bh.b_size);
	gfs2_free_journal_extents(jd);
	return rc;
}