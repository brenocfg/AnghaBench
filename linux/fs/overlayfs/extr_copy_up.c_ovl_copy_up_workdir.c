#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ovl_cu_creds {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  len; int /*<<< orphan*/  name; } ;
struct TYPE_5__ {int /*<<< orphan*/  dentry; } ;
struct TYPE_4__ {int mode; int /*<<< orphan*/  rdev; } ;
struct ovl_copy_up_ctx {int /*<<< orphan*/  destdir; int /*<<< orphan*/  workdir; int /*<<< orphan*/  dentry; int /*<<< orphan*/  metacopy; TYPE_3__ destname; TYPE_2__ lowerpath; scalar_t__ indexed; TYPE_1__ stat; int /*<<< orphan*/  link; } ;
struct ovl_cattr {int mode; int /*<<< orphan*/  link; int /*<<< orphan*/  rdev; } ;
struct inode {int i_mode; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct dentry*) ; 
 int /*<<< orphan*/  OVL_WHITEOUTS ; 
 int PTR_ERR (struct dentry*) ; 
 int S_IFMT ; 
 scalar_t__ S_ISDIR (int) ; 
 struct inode* d_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 struct dentry* lookup_one_len (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ovl_cleanup (struct inode*,struct dentry*) ; 
 int ovl_copy_up_inode (struct ovl_copy_up_ctx*,struct dentry*) ; 
 int ovl_create_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dentry*) ; 
 struct dentry* ovl_create_temp (int /*<<< orphan*/ ,struct ovl_cattr*) ; 
 int ovl_do_rename (struct inode*,struct dentry*,struct inode*,struct dentry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ovl_inode_update (struct inode*,struct dentry*) ; 
 int ovl_lock_rename_workdir (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ovl_prep_cu_creds (int /*<<< orphan*/ ,struct ovl_cu_creds*) ; 
 int /*<<< orphan*/  ovl_revert_cu_creds (struct ovl_cu_creds*) ; 
 int /*<<< orphan*/  ovl_set_flag (int /*<<< orphan*/ ,struct inode*) ; 
 int /*<<< orphan*/  ovl_set_upperdata (struct inode*) ; 
 int /*<<< orphan*/  unlock_rename (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ovl_copy_up_workdir(struct ovl_copy_up_ctx *c)
{
	struct inode *inode;
	struct inode *udir = d_inode(c->destdir), *wdir = d_inode(c->workdir);
	struct dentry *temp, *upper;
	struct ovl_cu_creds cc;
	int err;
	struct ovl_cattr cattr = {
		/* Can't properly set mode on creation because of the umask */
		.mode = c->stat.mode & S_IFMT,
		.rdev = c->stat.rdev,
		.link = c->link
	};

	err = ovl_lock_rename_workdir(c->workdir, c->destdir);
	if (err)
		return err;

	err = ovl_prep_cu_creds(c->dentry, &cc);
	if (err)
		goto unlock;

	temp = ovl_create_temp(c->workdir, &cattr);
	ovl_revert_cu_creds(&cc);

	err = PTR_ERR(temp);
	if (IS_ERR(temp))
		goto unlock;

	err = ovl_copy_up_inode(c, temp);
	if (err)
		goto cleanup;

	if (S_ISDIR(c->stat.mode) && c->indexed) {
		err = ovl_create_index(c->dentry, c->lowerpath.dentry, temp);
		if (err)
			goto cleanup;
	}

	upper = lookup_one_len(c->destname.name, c->destdir, c->destname.len);
	err = PTR_ERR(upper);
	if (IS_ERR(upper))
		goto cleanup;

	err = ovl_do_rename(wdir, temp, udir, upper, 0);
	dput(upper);
	if (err)
		goto cleanup;

	if (!c->metacopy)
		ovl_set_upperdata(d_inode(c->dentry));
	inode = d_inode(c->dentry);
	ovl_inode_update(inode, temp);
	if (S_ISDIR(inode->i_mode))
		ovl_set_flag(OVL_WHITEOUTS, inode);
unlock:
	unlock_rename(c->workdir, c->destdir);

	return err;

cleanup:
	ovl_cleanup(wdir, temp);
	dput(temp);
	goto unlock;
}