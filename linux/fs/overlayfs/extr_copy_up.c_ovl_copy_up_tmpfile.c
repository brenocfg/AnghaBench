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
struct ovl_cu_creds {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  len; int /*<<< orphan*/  name; } ;
struct TYPE_3__ {int /*<<< orphan*/  mode; } ;
struct ovl_copy_up_ctx {int /*<<< orphan*/  dentry; int /*<<< orphan*/  metacopy; TYPE_2__ destname; int /*<<< orphan*/  destdir; TYPE_1__ stat; int /*<<< orphan*/  workdir; } ;
struct inode {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct dentry*) ; 
 int /*<<< orphan*/  I_MUTEX_PARENT ; 
 int PTR_ERR (struct dentry*) ; 
 struct inode* d_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  inode_lock_nested (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 struct dentry* lookup_one_len (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ovl_copy_up_inode (struct ovl_copy_up_ctx*,struct dentry*) ; 
 int ovl_do_link (struct dentry*,struct inode*,struct dentry*) ; 
 struct dentry* ovl_do_tmpfile (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ovl_inode_update (struct inode*,struct dentry*) ; 
 int ovl_prep_cu_creds (int /*<<< orphan*/ ,struct ovl_cu_creds*) ; 
 int /*<<< orphan*/  ovl_revert_cu_creds (struct ovl_cu_creds*) ; 
 int /*<<< orphan*/  ovl_set_upperdata (struct inode*) ; 

__attribute__((used)) static int ovl_copy_up_tmpfile(struct ovl_copy_up_ctx *c)
{
	struct inode *udir = d_inode(c->destdir);
	struct dentry *temp, *upper;
	struct ovl_cu_creds cc;
	int err;

	err = ovl_prep_cu_creds(c->dentry, &cc);
	if (err)
		return err;

	temp = ovl_do_tmpfile(c->workdir, c->stat.mode);
	ovl_revert_cu_creds(&cc);

	if (IS_ERR(temp))
		return PTR_ERR(temp);

	err = ovl_copy_up_inode(c, temp);
	if (err)
		goto out_dput;

	inode_lock_nested(udir, I_MUTEX_PARENT);

	upper = lookup_one_len(c->destname.name, c->destdir, c->destname.len);
	err = PTR_ERR(upper);
	if (!IS_ERR(upper)) {
		err = ovl_do_link(temp, udir, upper);
		dput(upper);
	}
	inode_unlock(udir);

	if (err)
		goto out_dput;

	if (!c->metacopy)
		ovl_set_upperdata(d_inode(c->dentry));
	ovl_inode_update(d_inode(c->dentry), temp);

	return 0;

out_dput:
	dput(temp);
	return err;
}