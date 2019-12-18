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
struct gfs2_sbd {int /*<<< orphan*/  sd_freeze_mutex; int /*<<< orphan*/  sd_flags; int /*<<< orphan*/  sd_freeze_gh; int /*<<< orphan*/  sd_freeze_state; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  SDF_FS_FROZEN ; 
 int /*<<< orphan*/  SDF_WITHDRAWN ; 
 scalar_t__ SFS_UNFROZEN ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fs_err (struct gfs2_sbd*,char*,...) ; 
 int gfs2_lock_fs_check_clean (struct gfs2_sbd*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gfs2_freeze(struct super_block *sb)
{
	struct gfs2_sbd *sdp = sb->s_fs_info;
	int error = 0;

	mutex_lock(&sdp->sd_freeze_mutex);
	if (atomic_read(&sdp->sd_freeze_state) != SFS_UNFROZEN)
		goto out;

	if (test_bit(SDF_WITHDRAWN, &sdp->sd_flags)) {
		error = -EINVAL;
		goto out;
	}

	for (;;) {
		error = gfs2_lock_fs_check_clean(sdp, &sdp->sd_freeze_gh);
		if (!error)
			break;

		if (error == -EBUSY)
			fs_err(sdp, "waiting for recovery before freeze\n");
		else
			fs_err(sdp, "error freezing FS: %d\n", error);

		fs_err(sdp, "retrying...\n");
		msleep(1000);
	}
	set_bit(SDF_FS_FROZEN, &sdp->sd_flags);
out:
	mutex_unlock(&sdp->sd_freeze_mutex);
	return error;
}