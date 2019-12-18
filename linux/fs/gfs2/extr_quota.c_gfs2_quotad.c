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
struct gfs2_tune {int /*<<< orphan*/  gt_quota_quantum; int /*<<< orphan*/  gt_statfs_quantum; } ;
struct gfs2_sbd {int /*<<< orphan*/  sd_quota_wait; scalar_t__ sd_statfs_force_sync; int /*<<< orphan*/  sd_trunc_lock; int /*<<< orphan*/  sd_trunc_list; int /*<<< orphan*/  sd_vfs; struct gfs2_tune sd_tune; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_WAIT (int /*<<< orphan*/ ) ; 
 unsigned long HZ ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  finish_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int gfs2_quota_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int gfs2_statfs_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long gfs2_tune_get (struct gfs2_sbd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gt_statfs_quantum ; 
 int /*<<< orphan*/  kthread_should_stop () ; 
 int list_empty (int /*<<< orphan*/ *) ; 
 unsigned long min (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  prepare_to_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  quotad_check_timeo (struct gfs2_sbd*,char*,int (*) (int /*<<< orphan*/ ,int /*<<< orphan*/ ),unsigned long,unsigned long*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  quotad_check_trunc_list (struct gfs2_sbd*) ; 
 int /*<<< orphan*/  quotad_error (struct gfs2_sbd*,char*,int) ; 
 scalar_t__ schedule_timeout (unsigned long) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  try_to_freeze () ; 
 int /*<<< orphan*/  wait ; 

int gfs2_quotad(void *data)
{
	struct gfs2_sbd *sdp = data;
	struct gfs2_tune *tune = &sdp->sd_tune;
	unsigned long statfs_timeo = 0;
	unsigned long quotad_timeo = 0;
	unsigned long t = 0;
	DEFINE_WAIT(wait);
	int empty;

	while (!kthread_should_stop()) {

		/* Update the master statfs file */
		if (sdp->sd_statfs_force_sync) {
			int error = gfs2_statfs_sync(sdp->sd_vfs, 0);
			quotad_error(sdp, "statfs", error);
			statfs_timeo = gfs2_tune_get(sdp, gt_statfs_quantum) * HZ;
		}
		else
			quotad_check_timeo(sdp, "statfs", gfs2_statfs_sync, t,
				   	   &statfs_timeo,
					   &tune->gt_statfs_quantum);

		/* Update quota file */
		quotad_check_timeo(sdp, "sync", gfs2_quota_sync, t,
				   &quotad_timeo, &tune->gt_quota_quantum);

		/* Check for & recover partially truncated inodes */
		quotad_check_trunc_list(sdp);

		try_to_freeze();

		t = min(quotad_timeo, statfs_timeo);

		prepare_to_wait(&sdp->sd_quota_wait, &wait, TASK_INTERRUPTIBLE);
		spin_lock(&sdp->sd_trunc_lock);
		empty = list_empty(&sdp->sd_trunc_list);
		spin_unlock(&sdp->sd_trunc_lock);
		if (empty && !sdp->sd_statfs_force_sync)
			t -= schedule_timeout(t);
		else
			t = 0;
		finish_wait(&sdp->sd_quota_wait, &wait);
	}

	return 0;
}