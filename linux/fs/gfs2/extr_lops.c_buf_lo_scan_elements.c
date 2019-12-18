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
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct gfs2_sbd {int dummy; } ;
struct gfs2_rgrpd {scalar_t__ rd_addr; int /*<<< orphan*/  rd_gl; TYPE_1__* rd_bits; } ;
struct gfs2_meta_header {scalar_t__ mh_type; } ;
struct gfs2_log_descriptor {int /*<<< orphan*/  ld_type; int /*<<< orphan*/  ld_data1; } ;
struct gfs2_jdesc {int /*<<< orphan*/  jd_replayed_blocks; int /*<<< orphan*/  jd_found_blocks; int /*<<< orphan*/  jd_inode; } ;
struct gfs2_inode {struct gfs2_glock* i_gl; } ;
struct gfs2_glock {int dummy; } ;
struct buffer_head {scalar_t__ b_data; int /*<<< orphan*/  b_size; } ;
typedef  int /*<<< orphan*/  __be64 ;
struct TYPE_2__ {scalar_t__ bi_bh; } ;

/* Variables and functions */
 int EIO ; 
 struct gfs2_inode* GFS2_I (int /*<<< orphan*/ ) ; 
 unsigned int GFS2_LOG_DESC_METADATA ; 
 int /*<<< orphan*/  GFS2_METATYPE_RG ; 
 struct gfs2_sbd* GFS2_SB (int /*<<< orphan*/ ) ; 
 unsigned int be32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 scalar_t__ buffer_busy (scalar_t__) ; 
 int /*<<< orphan*/  buffer_pinned (scalar_t__) ; 
 scalar_t__ cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fs_info (struct gfs2_sbd*,char*,int,...) ; 
 struct gfs2_rgrpd* gfs2_blk2rgrpd (struct gfs2_sbd*,scalar_t__,int) ; 
 int /*<<< orphan*/  gfs2_dump_glock (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ gfs2_meta_check (struct gfs2_sbd*,struct buffer_head*) ; 
 struct buffer_head* gfs2_meta_new (struct gfs2_glock*,scalar_t__) ; 
 int /*<<< orphan*/  gfs2_replay_incr_blk (struct gfs2_jdesc*,int /*<<< orphan*/ *) ; 
 int gfs2_replay_read_block (struct gfs2_jdesc*,int /*<<< orphan*/ ,struct buffer_head**) ; 
 scalar_t__ gfs2_revoke_check (struct gfs2_jdesc*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mark_buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int buf_lo_scan_elements(struct gfs2_jdesc *jd, u32 start,
				struct gfs2_log_descriptor *ld, __be64 *ptr,
				int pass)
{
	struct gfs2_inode *ip = GFS2_I(jd->jd_inode);
	struct gfs2_sbd *sdp = GFS2_SB(jd->jd_inode);
	struct gfs2_glock *gl = ip->i_gl;
	unsigned int blks = be32_to_cpu(ld->ld_data1);
	struct buffer_head *bh_log, *bh_ip;
	u64 blkno;
	int error = 0;

	if (pass != 1 || be32_to_cpu(ld->ld_type) != GFS2_LOG_DESC_METADATA)
		return 0;

	gfs2_replay_incr_blk(jd, &start);

	for (; blks; gfs2_replay_incr_blk(jd, &start), blks--) {
		blkno = be64_to_cpu(*ptr++);

		jd->jd_found_blocks++;

		if (gfs2_revoke_check(jd, blkno, start))
			continue;

		error = gfs2_replay_read_block(jd, start, &bh_log);
		if (error)
			return error;

		bh_ip = gfs2_meta_new(gl, blkno);
		memcpy(bh_ip->b_data, bh_log->b_data, bh_log->b_size);

		if (gfs2_meta_check(sdp, bh_ip))
			error = -EIO;
		else {
			struct gfs2_meta_header *mh =
				(struct gfs2_meta_header *)bh_ip->b_data;

			if (mh->mh_type == cpu_to_be32(GFS2_METATYPE_RG)) {
				struct gfs2_rgrpd *rgd;

				rgd = gfs2_blk2rgrpd(sdp, blkno, false);
				if (rgd && rgd->rd_addr == blkno &&
				    rgd->rd_bits && rgd->rd_bits->bi_bh) {
					fs_info(sdp, "Replaying 0x%llx but we "
						"already have a bh!\n",
						(unsigned long long)blkno);
					fs_info(sdp, "busy:%d, pinned:%d\n",
						buffer_busy(rgd->rd_bits->bi_bh) ? 1 : 0,
						buffer_pinned(rgd->rd_bits->bi_bh));
					gfs2_dump_glock(NULL, rgd->rd_gl, true);
				}
			}
			mark_buffer_dirty(bh_ip);
		}
		brelse(bh_log);
		brelse(bh_ip);

		if (error)
			break;

		jd->jd_replayed_blocks++;
	}

	return error;
}