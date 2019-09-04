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
struct gfs2_holder {int dummy; } ;
struct gfs2_sbd {struct gfs2_holder sd_live_gh; int /*<<< orphan*/  sd_rename_gl; int /*<<< orphan*/  sd_freeze_gl; } ;

/* Variables and functions */
 int /*<<< orphan*/  CREATE ; 
 int /*<<< orphan*/  GFS2_FREEZE_LOCK ; 
 int /*<<< orphan*/  GFS2_LIVE_LOCK ; 
 int /*<<< orphan*/  GFS2_MOUNT_LOCK ; 
 int /*<<< orphan*/  GFS2_RENAME_LOCK ; 
 int GL_EXACT ; 
 int GL_NOCACHE ; 
 int LM_FLAG_NOEXP ; 
 int /*<<< orphan*/  LM_ST_EXCLUSIVE ; 
 int /*<<< orphan*/  LM_ST_SHARED ; 
 int /*<<< orphan*/  fs_err (struct gfs2_sbd*,char*,int) ; 
 int /*<<< orphan*/  gfs2_freeze_glops ; 
 int /*<<< orphan*/  gfs2_glock_dq_uninit (struct gfs2_holder*) ; 
 int gfs2_glock_get (struct gfs2_sbd*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int gfs2_glock_nq_num (struct gfs2_sbd*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,struct gfs2_holder*) ; 
 int /*<<< orphan*/  gfs2_glock_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_nondisk_glops ; 

__attribute__((used)) static int init_locking(struct gfs2_sbd *sdp, struct gfs2_holder *mount_gh,
			int undo)
{
	int error = 0;

	if (undo)
		goto fail_trans;

	error = gfs2_glock_nq_num(sdp,
				  GFS2_MOUNT_LOCK, &gfs2_nondisk_glops,
				  LM_ST_EXCLUSIVE, LM_FLAG_NOEXP | GL_NOCACHE,
				  mount_gh);
	if (error) {
		fs_err(sdp, "can't acquire mount glock: %d\n", error);
		goto fail;
	}

	error = gfs2_glock_nq_num(sdp,
				  GFS2_LIVE_LOCK, &gfs2_nondisk_glops,
				  LM_ST_SHARED,
				  LM_FLAG_NOEXP | GL_EXACT,
				  &sdp->sd_live_gh);
	if (error) {
		fs_err(sdp, "can't acquire live glock: %d\n", error);
		goto fail_mount;
	}

	error = gfs2_glock_get(sdp, GFS2_RENAME_LOCK, &gfs2_nondisk_glops,
			       CREATE, &sdp->sd_rename_gl);
	if (error) {
		fs_err(sdp, "can't create rename glock: %d\n", error);
		goto fail_live;
	}

	error = gfs2_glock_get(sdp, GFS2_FREEZE_LOCK, &gfs2_freeze_glops,
			       CREATE, &sdp->sd_freeze_gl);
	if (error) {
		fs_err(sdp, "can't create transaction glock: %d\n", error);
		goto fail_rename;
	}

	return 0;

fail_trans:
	gfs2_glock_put(sdp->sd_freeze_gl);
fail_rename:
	gfs2_glock_put(sdp->sd_rename_gl);
fail_live:
	gfs2_glock_dq_uninit(&sdp->sd_live_gh);
fail_mount:
	gfs2_glock_dq_uninit(mount_gh);
fail:
	return error;
}