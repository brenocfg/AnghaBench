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
struct path {scalar_t__ dentry; int /*<<< orphan*/  mnt; } ;
struct TYPE_2__ {int /*<<< orphan*/  mnt; struct dentry* dentry; } ;
struct nameidata {int flags; scalar_t__ last_type; TYPE_1__ path; int /*<<< orphan*/  last; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int ECHILD ; 
 int ENOENT ; 
 scalar_t__ IS_ERR (scalar_t__) ; 
 scalar_t__ LAST_NORM ; 
 int LOOKUP_NO_REVAL ; 
 int LOOKUP_PARENT ; 
 int LOOKUP_RCU ; 
 int PTR_ERR (scalar_t__) ; 
 int /*<<< orphan*/  d_backing_inode (scalar_t__) ; 
 scalar_t__ d_is_negative (scalar_t__) ; 
 scalar_t__ d_lookup (struct dentry*,int /*<<< orphan*/ *) ; 
 scalar_t__ dget (struct dentry*) ; 
 int /*<<< orphan*/  dput (scalar_t__) ; 
 int handle_dots (struct nameidata*,scalar_t__) ; 
 scalar_t__ lookup_slow (int /*<<< orphan*/ *,struct dentry*,int) ; 
 int step_into (struct nameidata*,struct path*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlazy_walk (struct nameidata*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int
mountpoint_last(struct nameidata *nd)
{
	int error = 0;
	struct dentry *dir = nd->path.dentry;
	struct path path;

	/* If we're in rcuwalk, drop out of it to handle last component */
	if (nd->flags & LOOKUP_RCU) {
		if (unlazy_walk(nd))
			return -ECHILD;
	}

	nd->flags &= ~LOOKUP_PARENT;

	if (unlikely(nd->last_type != LAST_NORM)) {
		error = handle_dots(nd, nd->last_type);
		if (error)
			return error;
		path.dentry = dget(nd->path.dentry);
	} else {
		path.dentry = d_lookup(dir, &nd->last);
		if (!path.dentry) {
			/*
			 * No cached dentry. Mounted dentries are pinned in the
			 * cache, so that means that this dentry is probably
			 * a symlink or the path doesn't actually point
			 * to a mounted dentry.
			 */
			path.dentry = lookup_slow(&nd->last, dir,
					     nd->flags | LOOKUP_NO_REVAL);
			if (IS_ERR(path.dentry))
				return PTR_ERR(path.dentry);
		}
	}
	if (d_is_negative(path.dentry)) {
		dput(path.dentry);
		return -ENOENT;
	}
	path.mnt = nd->path.mnt;
	return step_into(nd, &path, 0, d_backing_inode(path.dentry), 0);
}