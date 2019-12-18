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
struct gfs2_sbd {TYPE_1__* sd_jdesc; int /*<<< orphan*/  sd_log_blks_free; int /*<<< orphan*/  sd_reserving_log; int /*<<< orphan*/  sd_reserving_log_wait; int /*<<< orphan*/  sd_vfs; int /*<<< orphan*/ * sd_logd_process; int /*<<< orphan*/ * sd_quotad_process; int /*<<< orphan*/  sd_flags; int /*<<< orphan*/  sd_freeze_gl; } ;
struct gfs2_holder {int dummy; } ;
struct TYPE_2__ {scalar_t__ jd_blocks; } ;

/* Variables and functions */
 int GFS2_LFC_MAKE_FS_RO ; 
 int GFS2_LOG_HEAD_FLUSH_SHUTDOWN ; 
 int /*<<< orphan*/  GL_NOCACHE ; 
 int /*<<< orphan*/  LM_ST_SHARED ; 
 int /*<<< orphan*/  SDF_WITHDRAWN ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_assert_warn (struct gfs2_sbd*,int) ; 
 int /*<<< orphan*/  gfs2_delete_workqueue ; 
 int /*<<< orphan*/  gfs2_glock_dq_uninit (struct gfs2_holder*) ; 
 int gfs2_glock_nq_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gfs2_holder*) ; 
 scalar_t__ gfs2_holder_initialized (struct gfs2_holder*) ; 
 int /*<<< orphan*/  gfs2_log_flush (struct gfs2_sbd*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  gfs2_quota_cleanup (struct gfs2_sbd*) ; 
 int /*<<< orphan*/  gfs2_quota_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_statfs_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kthread_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

int gfs2_make_fs_ro(struct gfs2_sbd *sdp)
{
	struct gfs2_holder freeze_gh;
	int error;

	error = gfs2_glock_nq_init(sdp->sd_freeze_gl, LM_ST_SHARED, GL_NOCACHE,
				   &freeze_gh);
	if (error && !test_bit(SDF_WITHDRAWN, &sdp->sd_flags))
		return error;

	flush_workqueue(gfs2_delete_workqueue);
	if (sdp->sd_quotad_process)
		kthread_stop(sdp->sd_quotad_process);
	sdp->sd_quotad_process = NULL;
	if (sdp->sd_logd_process)
		kthread_stop(sdp->sd_logd_process);
	sdp->sd_logd_process = NULL;

	gfs2_quota_sync(sdp->sd_vfs, 0);
	gfs2_statfs_sync(sdp->sd_vfs, 0);

	gfs2_log_flush(sdp, NULL, GFS2_LOG_HEAD_FLUSH_SHUTDOWN |
		       GFS2_LFC_MAKE_FS_RO);
	wait_event(sdp->sd_reserving_log_wait, atomic_read(&sdp->sd_reserving_log) == 0);
	gfs2_assert_warn(sdp, atomic_read(&sdp->sd_log_blks_free) == sdp->sd_jdesc->jd_blocks);

	if (gfs2_holder_initialized(&freeze_gh))
		gfs2_glock_dq_uninit(&freeze_gh);

	gfs2_quota_cleanup(sdp);

	return error;
}