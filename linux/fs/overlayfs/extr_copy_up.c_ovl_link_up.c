#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct ovl_copy_up_ctx {TYPE_2__* dentry; int /*<<< orphan*/  pstat; TYPE_2__* parent; } ;
struct inode {int dummy; } ;
struct dentry {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  len; int /*<<< orphan*/  name; } ;
struct TYPE_8__ {TYPE_1__ d_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (struct dentry*) ; 
 int /*<<< orphan*/  I_MUTEX_PARENT ; 
 int PTR_ERR (struct dentry*) ; 
 struct inode* d_inode (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  inode_lock_nested (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 struct dentry* lookup_one_len (int /*<<< orphan*/ ,struct dentry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ovl_dentry_set_upper_alias (TYPE_2__*) ; 
 struct dentry* ovl_dentry_upper (TYPE_2__*) ; 
 int ovl_do_link (struct dentry*,struct inode*,struct dentry*) ; 
 int ovl_set_impure (TYPE_2__*,struct dentry*) ; 
 int ovl_set_nlink_lower (TYPE_2__*) ; 
 int ovl_set_nlink_upper (TYPE_2__*) ; 
 int /*<<< orphan*/  ovl_set_timestamps (struct dentry*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ovl_link_up(struct ovl_copy_up_ctx *c)
{
	int err;
	struct dentry *upper;
	struct dentry *upperdir = ovl_dentry_upper(c->parent);
	struct inode *udir = d_inode(upperdir);

	/* Mark parent "impure" because it may now contain non-pure upper */
	err = ovl_set_impure(c->parent, upperdir);
	if (err)
		return err;

	err = ovl_set_nlink_lower(c->dentry);
	if (err)
		return err;

	inode_lock_nested(udir, I_MUTEX_PARENT);
	upper = lookup_one_len(c->dentry->d_name.name, upperdir,
			       c->dentry->d_name.len);
	err = PTR_ERR(upper);
	if (!IS_ERR(upper)) {
		err = ovl_do_link(ovl_dentry_upper(c->dentry), udir, upper);
		dput(upper);

		if (!err) {
			/* Restore timestamps on parent (best effort) */
			ovl_set_timestamps(upperdir, &c->pstat);
			ovl_dentry_set_upper_alias(c->dentry);
		}
	}
	inode_unlock(udir);
	if (err)
		return err;

	err = ovl_set_nlink_upper(c->dentry);

	return err;
}