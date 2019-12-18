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
struct super_block {struct gfs2_sbd* s_fs_info; } ;
struct gfs2_sbd {int /*<<< orphan*/  sd_flags; int /*<<< orphan*/  sd_freeze_mutex; int /*<<< orphan*/  sd_freeze_gh; int /*<<< orphan*/  sd_freeze_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDF_FS_FROZEN ; 
 scalar_t__ SFS_FROZEN ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gfs2_glock_dq_uninit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gfs2_holder_initialized (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int wait_on_bit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gfs2_unfreeze(struct super_block *sb)
{
	struct gfs2_sbd *sdp = sb->s_fs_info;

	mutex_lock(&sdp->sd_freeze_mutex);
        if (atomic_read(&sdp->sd_freeze_state) != SFS_FROZEN ||
	    !gfs2_holder_initialized(&sdp->sd_freeze_gh)) {
		mutex_unlock(&sdp->sd_freeze_mutex);
                return 0;
	}

	gfs2_glock_dq_uninit(&sdp->sd_freeze_gh);
	mutex_unlock(&sdp->sd_freeze_mutex);
	return wait_on_bit(&sdp->sd_flags, SDF_FS_FROZEN, TASK_INTERRUPTIBLE);
}