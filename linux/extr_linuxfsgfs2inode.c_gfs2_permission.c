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
struct inode {int dummy; } ;
struct gfs2_inode {int /*<<< orphan*/  i_gl; } ;
struct gfs2_holder {int dummy; } ;

/* Variables and functions */
 int ECHILD ; 
 int EPERM ; 
 struct gfs2_inode* GFS2_I (struct inode*) ; 
 scalar_t__ IS_IMMUTABLE (struct inode*) ; 
 int /*<<< orphan*/  LM_FLAG_ANY ; 
 int /*<<< orphan*/  LM_ST_SHARED ; 
 int MAY_NOT_BLOCK ; 
 int MAY_WRITE ; 
 int generic_permission (struct inode*,int) ; 
 int /*<<< orphan*/  gfs2_glock_dq_uninit (struct gfs2_holder*) ; 
 int /*<<< orphan*/ * gfs2_glock_is_locked_by_me (int /*<<< orphan*/ ) ; 
 int gfs2_glock_nq_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gfs2_holder*) ; 
 scalar_t__ gfs2_holder_initialized (struct gfs2_holder*) ; 
 int /*<<< orphan*/  gfs2_holder_mark_uninitialized (struct gfs2_holder*) ; 

int gfs2_permission(struct inode *inode, int mask)
{
	struct gfs2_inode *ip;
	struct gfs2_holder i_gh;
	int error;

	gfs2_holder_mark_uninitialized(&i_gh);
	ip = GFS2_I(inode);
	if (gfs2_glock_is_locked_by_me(ip->i_gl) == NULL) {
		if (mask & MAY_NOT_BLOCK)
			return -ECHILD;
		error = gfs2_glock_nq_init(ip->i_gl, LM_ST_SHARED, LM_FLAG_ANY, &i_gh);
		if (error)
			return error;
	}

	if ((mask & MAY_WRITE) && IS_IMMUTABLE(inode))
		error = -EPERM;
	else
		error = generic_permission(inode, mask);
	if (gfs2_holder_initialized(&i_gh))
		gfs2_glock_dq_uninit(&i_gh);

	return error;
}