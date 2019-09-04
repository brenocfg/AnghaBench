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
typedef  scalar_t__ umode_t ;
struct posix_acl {scalar_t__ a_count; } ;
struct inode {scalar_t__ i_mode; int /*<<< orphan*/  i_ctime; } ;
struct gfs2_inode {int /*<<< orphan*/  i_gl; } ;
struct gfs2_holder {int dummy; } ;

/* Variables and functions */
 int ACL_TYPE_ACCESS ; 
 int E2BIG ; 
 scalar_t__ GFS2_ACL_MAX_ENTRIES (int /*<<< orphan*/ ) ; 
 struct gfs2_inode* GFS2_I (struct inode*) ; 
 int /*<<< orphan*/  GFS2_SB (struct inode*) ; 
 int /*<<< orphan*/  LM_ST_EXCLUSIVE ; 
 int __gfs2_set_acl (struct inode*,struct posix_acl*,int) ; 
 int /*<<< orphan*/  current_time (struct inode*) ; 
 int /*<<< orphan*/  gfs2_glock_dq_uninit (struct gfs2_holder*) ; 
 int /*<<< orphan*/  gfs2_glock_is_locked_by_me (int /*<<< orphan*/ ) ; 
 int gfs2_glock_nq_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gfs2_holder*) ; 
 int gfs2_rsqa_alloc (struct gfs2_inode*) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 int posix_acl_update_mode (struct inode*,scalar_t__*,struct posix_acl**) ; 

int gfs2_set_acl(struct inode *inode, struct posix_acl *acl, int type)
{
	struct gfs2_inode *ip = GFS2_I(inode);
	struct gfs2_holder gh;
	bool need_unlock = false;
	int ret;
	umode_t mode;

	if (acl && acl->a_count > GFS2_ACL_MAX_ENTRIES(GFS2_SB(inode)))
		return -E2BIG;

	ret = gfs2_rsqa_alloc(ip);
	if (ret)
		return ret;

	if (!gfs2_glock_is_locked_by_me(ip->i_gl)) {
		ret = gfs2_glock_nq_init(ip->i_gl, LM_ST_EXCLUSIVE, 0, &gh);
		if (ret)
			return ret;
		need_unlock = true;
	}

	mode = inode->i_mode;
	if (type == ACL_TYPE_ACCESS && acl) {
		ret = posix_acl_update_mode(inode, &mode, &acl);
		if (ret)
			goto unlock;
	}

	ret = __gfs2_set_acl(inode, acl, type);
	if (!ret && mode != inode->i_mode) {
		inode->i_ctime = current_time(inode);
		inode->i_mode = mode;
		mark_inode_dirty(inode);
	}
unlock:
	if (need_unlock)
		gfs2_glock_dq_uninit(&gh);
	return ret;
}