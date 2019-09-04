#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct path {struct dentry* dentry; } ;
struct TYPE_5__ {int /*<<< orphan*/  size; int /*<<< orphan*/  mode; } ;
struct TYPE_4__ {int /*<<< orphan*/  dentry; } ;
struct ovl_copy_up_ctx {TYPE_2__ stat; scalar_t__ metacopy; int /*<<< orphan*/  dentry; TYPE_1__ lowerpath; scalar_t__ origin; } ;
struct dentry {int /*<<< orphan*/  d_inode; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  EOPNOTSUPP ; 
 int /*<<< orphan*/  OVL_XATTR_METACOPY ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 scalar_t__ WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_unlock (int /*<<< orphan*/ ) ; 
 int ovl_check_setxattr (int /*<<< orphan*/ ,struct dentry*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ovl_copy_up_data (struct path*,struct path*,int /*<<< orphan*/ ) ; 
 int ovl_copy_xattr (int /*<<< orphan*/ ,struct dentry*) ; 
 int /*<<< orphan*/  ovl_path_lowerdata (int /*<<< orphan*/ ,struct path*) ; 
 int /*<<< orphan*/  ovl_path_upper (int /*<<< orphan*/ ,struct path*) ; 
 int ovl_set_attr (struct dentry*,TYPE_2__*) ; 
 int ovl_set_origin (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dentry*) ; 
 int ovl_set_size (struct dentry*,TYPE_2__*) ; 

__attribute__((used)) static int ovl_copy_up_inode(struct ovl_copy_up_ctx *c, struct dentry *temp)
{
	int err;

	/*
	 * Copy up data first and then xattrs. Writing data after
	 * xattrs will remove security.capability xattr automatically.
	 */
	if (S_ISREG(c->stat.mode) && !c->metacopy) {
		struct path upperpath, datapath;

		ovl_path_upper(c->dentry, &upperpath);
		if (WARN_ON(upperpath.dentry != NULL))
			return -EIO;
		upperpath.dentry = temp;

		ovl_path_lowerdata(c->dentry, &datapath);
		err = ovl_copy_up_data(&datapath, &upperpath, c->stat.size);
		if (err)
			return err;
	}

	err = ovl_copy_xattr(c->lowerpath.dentry, temp);
	if (err)
		return err;

	/*
	 * Store identifier of lower inode in upper inode xattr to
	 * allow lookup of the copy up origin inode.
	 *
	 * Don't set origin when we are breaking the association with a lower
	 * hard link.
	 */
	if (c->origin) {
		err = ovl_set_origin(c->dentry, c->lowerpath.dentry, temp);
		if (err)
			return err;
	}

	if (c->metacopy) {
		err = ovl_check_setxattr(c->dentry, temp, OVL_XATTR_METACOPY,
					 NULL, 0, -EOPNOTSUPP);
		if (err)
			return err;
	}

	inode_lock(temp->d_inode);
	if (c->metacopy)
		err = ovl_set_size(temp, &c->stat);
	if (!err)
		err = ovl_set_attr(temp, &c->stat);
	inode_unlock(temp->d_inode);

	return err;
}