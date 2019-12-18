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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {scalar_t__ ls_jid; } ;
struct gfs2_sbd {int /*<<< orphan*/  sd_log_flush_head; TYPE_1__ sd_lockstruct; } ;
struct gfs2_log_header_host {scalar_t__ lh_sequence; int /*<<< orphan*/  lh_blkno; } ;
struct gfs2_jdesc {scalar_t__ jd_jid; int /*<<< orphan*/  jd_inode; } ;

/* Variables and functions */
 int GFS2_LOG_HEAD_RECOVERY ; 
 int GFS2_LOG_HEAD_UNMOUNT ; 
 struct gfs2_sbd* GFS2_SB (int /*<<< orphan*/ ) ; 
 int REQ_FUA ; 
 int REQ_META ; 
 int REQ_PREFLUSH ; 
 int REQ_SYNC ; 
 int /*<<< orphan*/  gfs2_replay_incr_blk (struct gfs2_jdesc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gfs2_write_log_header (struct gfs2_sbd*,struct gfs2_jdesc*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void clean_journal(struct gfs2_jdesc *jd,
			  struct gfs2_log_header_host *head)
{
	struct gfs2_sbd *sdp = GFS2_SB(jd->jd_inode);
	u32 lblock = head->lh_blkno;

	gfs2_replay_incr_blk(jd, &lblock);
	if (jd->jd_jid == sdp->sd_lockstruct.ls_jid)
		sdp->sd_log_flush_head = lblock;
	gfs2_write_log_header(sdp, jd, head->lh_sequence + 1, 0, lblock,
			      GFS2_LOG_HEAD_UNMOUNT | GFS2_LOG_HEAD_RECOVERY,
			      REQ_PREFLUSH | REQ_FUA | REQ_META | REQ_SYNC);
}