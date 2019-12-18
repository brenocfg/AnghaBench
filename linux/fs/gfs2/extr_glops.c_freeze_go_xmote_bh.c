#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct gfs2_sbd {scalar_t__ sd_log_sequence; int /*<<< orphan*/  sd_flags; TYPE_3__* sd_jdesc; } ;
struct gfs2_log_header_host {int lh_flags; int /*<<< orphan*/  lh_blkno; scalar_t__ lh_sequence; } ;
struct gfs2_inode {struct gfs2_glock* i_gl; } ;
struct gfs2_holder {int dummy; } ;
struct TYPE_4__ {struct gfs2_sbd* ln_sbd; } ;
struct gfs2_glock {TYPE_2__* gl_ops; TYPE_1__ gl_name; } ;
struct TYPE_6__ {int /*<<< orphan*/  jd_inode; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* go_inval ) (struct gfs2_glock*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DIO_METADATA ; 
 struct gfs2_inode* GFS2_I (int /*<<< orphan*/ ) ; 
 int GFS2_LOG_HEAD_UNMOUNT ; 
 int /*<<< orphan*/  SDF_JOURNAL_LIVE ; 
 int /*<<< orphan*/  SDF_WITHDRAWN ; 
 int /*<<< orphan*/  gfs2_consist (struct gfs2_sbd*) ; 
 int gfs2_find_jhead (TYPE_3__*,struct gfs2_log_header_host*,int) ; 
 int /*<<< orphan*/  gfs2_log_pointers_init (struct gfs2_sbd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct gfs2_glock*,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int freeze_go_xmote_bh(struct gfs2_glock *gl, struct gfs2_holder *gh)
{
	struct gfs2_sbd *sdp = gl->gl_name.ln_sbd;
	struct gfs2_inode *ip = GFS2_I(sdp->sd_jdesc->jd_inode);
	struct gfs2_glock *j_gl = ip->i_gl;
	struct gfs2_log_header_host head;
	int error;

	if (test_bit(SDF_JOURNAL_LIVE, &sdp->sd_flags)) {
		j_gl->gl_ops->go_inval(j_gl, DIO_METADATA);

		error = gfs2_find_jhead(sdp->sd_jdesc, &head, false);
		if (error)
			gfs2_consist(sdp);
		if (!(head.lh_flags & GFS2_LOG_HEAD_UNMOUNT))
			gfs2_consist(sdp);

		/*  Initialize some head of the log stuff  */
		if (!test_bit(SDF_WITHDRAWN, &sdp->sd_flags)) {
			sdp->sd_log_sequence = head.lh_sequence + 1;
			gfs2_log_pointers_init(sdp, head.lh_blkno);
		}
	}
	return 0;
}