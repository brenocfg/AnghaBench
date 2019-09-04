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
struct path {int /*<<< orphan*/  dentry; int /*<<< orphan*/  mnt; } ;
struct TYPE_2__ {int /*<<< orphan*/  mnt; int /*<<< orphan*/  dentry; } ;
struct nameidata {scalar_t__ last_type; TYPE_1__ path; int /*<<< orphan*/  flags; int /*<<< orphan*/  last; scalar_t__ depth; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ LAST_NORM ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int WALK_MORE ; 
 struct inode* d_backing_inode (int /*<<< orphan*/ ) ; 
 int d_is_negative (int /*<<< orphan*/ ) ; 
 int follow_managed (struct path*,struct nameidata*) ; 
 int handle_dots (struct nameidata*,scalar_t__) ; 
 int lookup_fast (struct nameidata*,struct path*,struct inode**,unsigned int*) ; 
 int /*<<< orphan*/  lookup_slow (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  path_to_nameidata (struct path*,struct nameidata*) ; 
 int /*<<< orphan*/  put_link (struct nameidata*) ; 
 int step_into (struct nameidata*,struct path*,int,struct inode*,unsigned int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int walk_component(struct nameidata *nd, int flags)
{
	struct path path;
	struct inode *inode;
	unsigned seq;
	int err;
	/*
	 * "." and ".." are special - ".." especially so because it has
	 * to be able to know about the current root directory and
	 * parent relationships.
	 */
	if (unlikely(nd->last_type != LAST_NORM)) {
		err = handle_dots(nd, nd->last_type);
		if (!(flags & WALK_MORE) && nd->depth)
			put_link(nd);
		return err;
	}
	err = lookup_fast(nd, &path, &inode, &seq);
	if (unlikely(err <= 0)) {
		if (err < 0)
			return err;
		path.dentry = lookup_slow(&nd->last, nd->path.dentry,
					  nd->flags);
		if (IS_ERR(path.dentry))
			return PTR_ERR(path.dentry);

		path.mnt = nd->path.mnt;
		err = follow_managed(&path, nd);
		if (unlikely(err < 0))
			return err;

		if (unlikely(d_is_negative(path.dentry))) {
			path_to_nameidata(&path, nd);
			return -ENOENT;
		}

		seq = 0;	/* we are already out of RCU mode */
		inode = d_backing_inode(path.dentry);
	}

	return step_into(nd, &path, flags, inode, seq);
}