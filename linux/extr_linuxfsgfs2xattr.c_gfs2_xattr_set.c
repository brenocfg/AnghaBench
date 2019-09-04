#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct xattr_handler {int /*<<< orphan*/  flags; } ;
struct inode {int dummy; } ;
struct gfs2_inode {TYPE_1__* i_gl; } ;
struct gfs2_holder {int dummy; } ;
struct dentry {int dummy; } ;
struct TYPE_3__ {scalar_t__ gl_state; } ;

/* Variables and functions */
 int EIO ; 
 struct gfs2_inode* GFS2_I (struct inode*) ; 
 scalar_t__ LM_ST_EXCLUSIVE ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int __gfs2_xattr_set (struct inode*,char const*,void const*,size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_glock_dq_uninit (struct gfs2_holder*) ; 
 int /*<<< orphan*/  gfs2_glock_is_locked_by_me (TYPE_1__*) ; 
 int gfs2_glock_nq_init (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ,struct gfs2_holder*) ; 
 scalar_t__ gfs2_holder_initialized (struct gfs2_holder*) ; 
 int /*<<< orphan*/  gfs2_holder_mark_uninitialized (struct gfs2_holder*) ; 
 int gfs2_rsqa_alloc (struct gfs2_inode*) ; 

__attribute__((used)) static int gfs2_xattr_set(const struct xattr_handler *handler,
			  struct dentry *unused, struct inode *inode,
			  const char *name, const void *value,
			  size_t size, int flags)
{
	struct gfs2_inode *ip = GFS2_I(inode);
	struct gfs2_holder gh;
	int ret;

	ret = gfs2_rsqa_alloc(ip);
	if (ret)
		return ret;

	/* May be called from gfs_setattr with the glock locked. */

	if (!gfs2_glock_is_locked_by_me(ip->i_gl)) {
		ret = gfs2_glock_nq_init(ip->i_gl, LM_ST_EXCLUSIVE, 0, &gh);
		if (ret)
			return ret;
	} else {
		if (WARN_ON_ONCE(ip->i_gl->gl_state != LM_ST_EXCLUSIVE))
			return -EIO;
		gfs2_holder_mark_uninitialized(&gh);
	}
	ret = __gfs2_xattr_set(inode, name, value, size, flags, handler->flags);
	if (gfs2_holder_initialized(&gh))
		gfs2_glock_dq_uninit(&gh);
	return ret;
}