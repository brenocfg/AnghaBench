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
struct super_block {int s_flags; struct gfs2_sbd* s_fs_info; } ;
struct gfs2_tune {int gt_statfs_slow; int gt_statfs_quantum; int /*<<< orphan*/  gt_spin; int /*<<< orphan*/  gt_quota_quantum; int /*<<< orphan*/  gt_logd_secs; } ;
struct gfs2_args {int ar_statfs_quantum; scalar_t__ ar_spectator; scalar_t__ ar_localflocks; scalar_t__ ar_meta; int /*<<< orphan*/  ar_quota_quantum; int /*<<< orphan*/  ar_commit; scalar_t__ ar_nobarrier; scalar_t__ ar_posix_acl; int /*<<< orphan*/  ar_hostdata; int /*<<< orphan*/  ar_locktable; int /*<<< orphan*/  ar_lockproto; } ;
struct gfs2_sbd {int /*<<< orphan*/  sd_flags; struct gfs2_args sd_args; struct gfs2_tune sd_tune; } ;
struct fs_context {int sb_flags; struct gfs2_args* fs_private; TYPE_1__* root; } ;
struct TYPE_2__ {struct super_block* d_sb; } ;

/* Variables and functions */
 int EINVAL ; 
 int SB_POSIXACL ; 
 int SB_RDONLY ; 
 int /*<<< orphan*/  SDF_NOBARRIERS ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errorf (struct fs_context*,char*) ; 
 int gfs2_make_fs_ro (struct gfs2_sbd*) ; 
 int gfs2_make_fs_rw (struct gfs2_sbd*) ; 
 int /*<<< orphan*/  gfs2_online_uevent (struct gfs2_sbd*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sync_filesystem (struct super_block*) ; 

__attribute__((used)) static int gfs2_reconfigure(struct fs_context *fc)
{
	struct super_block *sb = fc->root->d_sb;
	struct gfs2_sbd *sdp = sb->s_fs_info;
	struct gfs2_args *oldargs = &sdp->sd_args;
	struct gfs2_args *newargs = fc->fs_private;
	struct gfs2_tune *gt = &sdp->sd_tune;
	int error = 0;

	sync_filesystem(sb);

	spin_lock(&gt->gt_spin);
	oldargs->ar_commit = gt->gt_logd_secs;
	oldargs->ar_quota_quantum = gt->gt_quota_quantum;
	if (gt->gt_statfs_slow)
		oldargs->ar_statfs_quantum = 0;
	else
		oldargs->ar_statfs_quantum = gt->gt_statfs_quantum;
	spin_unlock(&gt->gt_spin);

	if (strcmp(newargs->ar_lockproto, oldargs->ar_lockproto)) {
		errorf(fc, "gfs2: reconfiguration of locking protocol not allowed");
		return -EINVAL;
	}
	if (strcmp(newargs->ar_locktable, oldargs->ar_locktable)) {
		errorf(fc, "gfs2: reconfiguration of lock table not allowed");
		return -EINVAL;
	}
	if (strcmp(newargs->ar_hostdata, oldargs->ar_hostdata)) {
		errorf(fc, "gfs2: reconfiguration of host data not allowed");
		return -EINVAL;
	}
	if (newargs->ar_spectator != oldargs->ar_spectator) {
		errorf(fc, "gfs2: reconfiguration of spectator mode not allowed");
		return -EINVAL;
	}
	if (newargs->ar_localflocks != oldargs->ar_localflocks) {
		errorf(fc, "gfs2: reconfiguration of localflocks not allowed");
		return -EINVAL;
	}
	if (newargs->ar_meta != oldargs->ar_meta) {
		errorf(fc, "gfs2: switching between gfs2 and gfs2meta not allowed");
		return -EINVAL;
	}
	if (oldargs->ar_spectator)
		fc->sb_flags |= SB_RDONLY;

	if ((sb->s_flags ^ fc->sb_flags) & SB_RDONLY) {
		if (fc->sb_flags & SB_RDONLY) {
			error = gfs2_make_fs_ro(sdp);
			if (error)
				errorf(fc, "gfs2: unable to remount read-only");
		} else {
			error = gfs2_make_fs_rw(sdp);
			if (error)
				errorf(fc, "gfs2: unable to remount read-write");
		}
	}
	sdp->sd_args = *newargs;

	if (sdp->sd_args.ar_posix_acl)
		sb->s_flags |= SB_POSIXACL;
	else
		sb->s_flags &= ~SB_POSIXACL;
	if (sdp->sd_args.ar_nobarrier)
		set_bit(SDF_NOBARRIERS, &sdp->sd_flags);
	else
		clear_bit(SDF_NOBARRIERS, &sdp->sd_flags);
	spin_lock(&gt->gt_spin);
	gt->gt_logd_secs = newargs->ar_commit;
	gt->gt_quota_quantum = newargs->ar_quota_quantum;
	if (newargs->ar_statfs_quantum) {
		gt->gt_statfs_slow = 0;
		gt->gt_statfs_quantum = newargs->ar_statfs_quantum;
	}
	else {
		gt->gt_statfs_slow = 1;
		gt->gt_statfs_quantum = 30;
	}
	spin_unlock(&gt->gt_spin);

	gfs2_online_uevent(sdp);
	return error;
}