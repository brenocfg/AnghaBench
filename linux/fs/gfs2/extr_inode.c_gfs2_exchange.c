#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  umode_t ;
struct inode {int dummy; } ;
struct gfs2_sbd {int /*<<< orphan*/  sd_rename_gl; } ;
struct TYPE_4__ {scalar_t__ i_nlink; int /*<<< orphan*/  i_mode; } ;
struct gfs2_inode {TYPE_1__ i_inode; int /*<<< orphan*/  i_gl; } ;
struct gfs2_holder {int dummy; } ;
struct dentry {int /*<<< orphan*/  d_name; struct inode* d_inode; } ;

/* Variables and functions */
 int ENOENT ; 
 struct gfs2_inode* GFS2_I (struct inode*) ; 
 struct gfs2_sbd* GFS2_SB (struct inode*) ; 
 int /*<<< orphan*/  GL_ASYNC ; 
 int /*<<< orphan*/  IF2DT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LM_ST_EXCLUSIVE ; 
 int /*<<< orphan*/  MAY_WRITE ; 
 int RES_DINODE ; 
 int RES_LEAF ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drop_nlink (TYPE_1__*) ; 
 int gfs2_dir_mvino (struct gfs2_inode*,int /*<<< orphan*/ *,struct gfs2_inode*,int /*<<< orphan*/ ) ; 
 int gfs2_glock_async_wait (unsigned int,struct gfs2_holder*) ; 
 int /*<<< orphan*/  gfs2_glock_dq (struct gfs2_holder*) ; 
 int /*<<< orphan*/  gfs2_glock_dq_uninit (struct gfs2_holder*) ; 
 int gfs2_glock_nq (struct gfs2_holder*) ; 
 int gfs2_glock_nq_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gfs2_holder*) ; 
 int /*<<< orphan*/  gfs2_holder_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gfs2_holder*) ; 
 scalar_t__ gfs2_holder_initialized (struct gfs2_holder*) ; 
 int /*<<< orphan*/  gfs2_holder_mark_uninitialized (struct gfs2_holder*) ; 
 scalar_t__ gfs2_holder_queued (struct gfs2_holder*) ; 
 int /*<<< orphan*/  gfs2_holder_uninit (struct gfs2_holder*) ; 
 int gfs2_ok_to_move (struct gfs2_inode*,struct gfs2_inode*) ; 
 int gfs2_permission (struct inode*,int /*<<< orphan*/ ) ; 
 int gfs2_rindex_update (struct gfs2_sbd*) ; 
 int gfs2_trans_begin (struct gfs2_sbd*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_trans_end (struct gfs2_sbd*) ; 
 int gfs2_unlink_ok (struct gfs2_inode*,int /*<<< orphan*/ *,struct gfs2_inode*) ; 
 int /*<<< orphan*/  inc_nlink (TYPE_1__*) ; 
 int /*<<< orphan*/  mark_inode_dirty (TYPE_1__*) ; 
 int update_moved_ino (struct gfs2_inode*,struct gfs2_inode*,scalar_t__) ; 

__attribute__((used)) static int gfs2_exchange(struct inode *odir, struct dentry *odentry,
			 struct inode *ndir, struct dentry *ndentry,
			 unsigned int flags)
{
	struct gfs2_inode *odip = GFS2_I(odir);
	struct gfs2_inode *ndip = GFS2_I(ndir);
	struct gfs2_inode *oip = GFS2_I(odentry->d_inode);
	struct gfs2_inode *nip = GFS2_I(ndentry->d_inode);
	struct gfs2_sbd *sdp = GFS2_SB(odir);
	struct gfs2_holder ghs[4], r_gh;
	unsigned int num_gh;
	unsigned int x;
	umode_t old_mode = oip->i_inode.i_mode;
	umode_t new_mode = nip->i_inode.i_mode;
	int error;

	gfs2_holder_mark_uninitialized(&r_gh);
	error = gfs2_rindex_update(sdp);
	if (error)
		return error;

	if (odip != ndip) {
		error = gfs2_glock_nq_init(sdp->sd_rename_gl, LM_ST_EXCLUSIVE,
					   0, &r_gh);
		if (error)
			goto out;

		if (S_ISDIR(old_mode)) {
			/* don't move a directory into its subdir */
			error = gfs2_ok_to_move(oip, ndip);
			if (error)
				goto out_gunlock_r;
		}

		if (S_ISDIR(new_mode)) {
			/* don't move a directory into its subdir */
			error = gfs2_ok_to_move(nip, odip);
			if (error)
				goto out_gunlock_r;
		}
	}

	num_gh = 1;
	gfs2_holder_init(odip->i_gl, LM_ST_EXCLUSIVE, GL_ASYNC, ghs);
	if (odip != ndip) {
		gfs2_holder_init(ndip->i_gl, LM_ST_EXCLUSIVE, GL_ASYNC,
				 ghs + num_gh);
		num_gh++;
	}
	gfs2_holder_init(oip->i_gl, LM_ST_EXCLUSIVE, GL_ASYNC, ghs + num_gh);
	num_gh++;

	gfs2_holder_init(nip->i_gl, LM_ST_EXCLUSIVE, GL_ASYNC, ghs + num_gh);
	num_gh++;

	for (x = 0; x < num_gh; x++) {
		error = gfs2_glock_nq(ghs + x);
		if (error)
			goto out_gunlock;
	}

	error = gfs2_glock_async_wait(num_gh, ghs);
	if (error)
		goto out_gunlock;

	error = -ENOENT;
	if (oip->i_inode.i_nlink == 0 || nip->i_inode.i_nlink == 0)
		goto out_gunlock;

	error = gfs2_unlink_ok(odip, &odentry->d_name, oip);
	if (error)
		goto out_gunlock;
	error = gfs2_unlink_ok(ndip, &ndentry->d_name, nip);
	if (error)
		goto out_gunlock;

	if (S_ISDIR(old_mode)) {
		error = gfs2_permission(odentry->d_inode, MAY_WRITE);
		if (error)
			goto out_gunlock;
	}
	if (S_ISDIR(new_mode)) {
		error = gfs2_permission(ndentry->d_inode, MAY_WRITE);
		if (error)
			goto out_gunlock;
	}
	error = gfs2_trans_begin(sdp, 4 * RES_DINODE + 4 * RES_LEAF, 0);
	if (error)
		goto out_gunlock;

	error = update_moved_ino(oip, ndip, S_ISDIR(old_mode));
	if (error)
		goto out_end_trans;

	error = update_moved_ino(nip, odip, S_ISDIR(new_mode));
	if (error)
		goto out_end_trans;

	error = gfs2_dir_mvino(ndip, &ndentry->d_name, oip,
			       IF2DT(old_mode));
	if (error)
		goto out_end_trans;

	error = gfs2_dir_mvino(odip, &odentry->d_name, nip,
			       IF2DT(new_mode));
	if (error)
		goto out_end_trans;

	if (odip != ndip) {
		if (S_ISDIR(new_mode) && !S_ISDIR(old_mode)) {
			inc_nlink(&odip->i_inode);
			drop_nlink(&ndip->i_inode);
		} else if (S_ISDIR(old_mode) && !S_ISDIR(new_mode)) {
			inc_nlink(&ndip->i_inode);
			drop_nlink(&odip->i_inode);
		}
	}
	mark_inode_dirty(&ndip->i_inode);
	if (odip != ndip)
		mark_inode_dirty(&odip->i_inode);

out_end_trans:
	gfs2_trans_end(sdp);
out_gunlock:
	while (x--) {
		if (gfs2_holder_queued(ghs + x))
			gfs2_glock_dq(ghs + x);
		gfs2_holder_uninit(ghs + x);
	}
out_gunlock_r:
	if (gfs2_holder_initialized(&r_gh))
		gfs2_glock_dq_uninit(&r_gh);
out:
	return error;
}