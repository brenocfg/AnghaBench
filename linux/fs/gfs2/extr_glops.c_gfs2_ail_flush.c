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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_3__ {int sb_bsize; } ;
struct gfs2_sbd {TYPE_1__ sd_sb; } ;
struct gfs2_meta_header {int dummy; } ;
struct gfs2_log_descriptor {int dummy; } ;
struct TYPE_4__ {struct gfs2_sbd* ln_sbd; } ;
struct gfs2_glock {int /*<<< orphan*/  gl_ail_count; TYPE_2__ gl_name; } ;

/* Variables and functions */
 int GFS2_LFC_AIL_FLUSH ; 
 int GFS2_LOG_HEAD_FLUSH_NORMAL ; 
 int /*<<< orphan*/  __gfs2_ail_flush (struct gfs2_glock*,int,unsigned int) ; 
 unsigned int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gfs2_log_flush (struct gfs2_sbd*,int /*<<< orphan*/ *,int) ; 
 int gfs2_trans_begin (struct gfs2_sbd*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  gfs2_trans_end (struct gfs2_sbd*) ; 

void gfs2_ail_flush(struct gfs2_glock *gl, bool fsync)
{
	struct gfs2_sbd *sdp = gl->gl_name.ln_sbd;
	unsigned int revokes = atomic_read(&gl->gl_ail_count);
	unsigned int max_revokes = (sdp->sd_sb.sb_bsize - sizeof(struct gfs2_log_descriptor)) / sizeof(u64);
	int ret;

	if (!revokes)
		return;

	while (revokes > max_revokes)
		max_revokes += (sdp->sd_sb.sb_bsize - sizeof(struct gfs2_meta_header)) / sizeof(u64);

	ret = gfs2_trans_begin(sdp, 0, max_revokes);
	if (ret)
		return;
	__gfs2_ail_flush(gl, fsync, max_revokes);
	gfs2_trans_end(sdp);
	gfs2_log_flush(sdp, NULL, GFS2_LOG_HEAD_FLUSH_NORMAL |
		       GFS2_LFC_AIL_FLUSH);
}