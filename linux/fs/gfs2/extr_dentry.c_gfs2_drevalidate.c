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
struct inode {int dummy; } ;
struct TYPE_4__ {TYPE_1__* ls_ops; } ;
struct gfs2_sbd {TYPE_2__ sd_lockstruct; } ;
struct gfs2_inode {int /*<<< orphan*/  i_gl; } ;
struct gfs2_holder {int dummy; } ;
struct dentry {int /*<<< orphan*/  d_name; } ;
struct TYPE_3__ {int /*<<< orphan*/ * lm_mount; } ;

/* Variables and functions */
 int ECHILD ; 
 int ENOENT ; 
 struct gfs2_inode* GFS2_I (struct inode*) ; 
 struct gfs2_sbd* GFS2_SB (struct inode*) ; 
 int /*<<< orphan*/  LM_ST_SHARED ; 
 unsigned int LOOKUP_RCU ; 
 struct inode* d_inode (struct dentry*) ; 
 struct dentry* dget_parent (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int gfs2_dir_check (struct inode*,int /*<<< orphan*/ *,struct gfs2_inode*) ; 
 int /*<<< orphan*/  gfs2_glock_dq_uninit (struct gfs2_holder*) ; 
 int /*<<< orphan*/ * gfs2_glock_is_locked_by_me (int /*<<< orphan*/ ) ; 
 int gfs2_glock_nq_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gfs2_holder*) ; 
 scalar_t__ is_bad_inode (struct inode*) ; 

__attribute__((used)) static int gfs2_drevalidate(struct dentry *dentry, unsigned int flags)
{
	struct dentry *parent;
	struct gfs2_sbd *sdp;
	struct gfs2_inode *dip;
	struct inode *inode;
	struct gfs2_holder d_gh;
	struct gfs2_inode *ip = NULL;
	int error, valid = 0;
	int had_lock = 0;

	if (flags & LOOKUP_RCU)
		return -ECHILD;

	parent = dget_parent(dentry);
	sdp = GFS2_SB(d_inode(parent));
	dip = GFS2_I(d_inode(parent));
	inode = d_inode(dentry);

	if (inode) {
		if (is_bad_inode(inode))
			goto out;
		ip = GFS2_I(inode);
	}

	if (sdp->sd_lockstruct.ls_ops->lm_mount == NULL) {
		valid = 1;
		goto out;
	}

	had_lock = (gfs2_glock_is_locked_by_me(dip->i_gl) != NULL);
	if (!had_lock) {
		error = gfs2_glock_nq_init(dip->i_gl, LM_ST_SHARED, 0, &d_gh);
		if (error)
			goto out;
	}

	error = gfs2_dir_check(d_inode(parent), &dentry->d_name, ip);
	valid = inode ? !error : (error == -ENOENT);

	if (!had_lock)
		gfs2_glock_dq_uninit(&d_gh);
out:
	dput(parent);
	return valid;
}