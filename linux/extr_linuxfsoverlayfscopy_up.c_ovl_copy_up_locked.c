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
struct TYPE_6__ {int /*<<< orphan*/  dentry; } ;
struct TYPE_5__ {int /*<<< orphan*/  mode; } ;
struct ovl_copy_up_ctx {int /*<<< orphan*/  workdir; scalar_t__ tmpfile; int /*<<< orphan*/  dentry; int /*<<< orphan*/  metacopy; TYPE_3__ lowerpath; scalar_t__ indexed; TYPE_2__ stat; TYPE_1__* destdir; } ;
struct inode {int /*<<< orphan*/  i_mode; } ;
struct dentry {int dummy; } ;
struct TYPE_4__ {struct inode* d_inode; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct dentry*) ; 
 int /*<<< orphan*/  I_MUTEX_PARENT ; 
 int /*<<< orphan*/  OVL_WHITEOUTS ; 
 int PTR_ERR (struct dentry*) ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 struct inode* d_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  inode_lock_nested (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 int /*<<< orphan*/  ovl_cleanup (struct inode*,struct dentry*) ; 
 int ovl_copy_up_inode (struct ovl_copy_up_ctx*,struct dentry*) ; 
 int ovl_create_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dentry*) ; 
 struct dentry* ovl_get_tmpfile (struct ovl_copy_up_ctx*) ; 
 int /*<<< orphan*/  ovl_inode_update (struct inode*,struct dentry*) ; 
 int ovl_install_temp (struct ovl_copy_up_ctx*,struct dentry*,struct dentry**) ; 
 int /*<<< orphan*/  ovl_set_flag (int /*<<< orphan*/ ,struct inode*) ; 
 int /*<<< orphan*/  ovl_set_upperdata (struct inode*) ; 

__attribute__((used)) static int ovl_copy_up_locked(struct ovl_copy_up_ctx *c)
{
	struct inode *udir = c->destdir->d_inode;
	struct inode *inode;
	struct dentry *newdentry = NULL;
	struct dentry *temp;
	int err;

	temp = ovl_get_tmpfile(c);
	if (IS_ERR(temp))
		return PTR_ERR(temp);

	err = ovl_copy_up_inode(c, temp);
	if (err)
		goto out;

	if (S_ISDIR(c->stat.mode) && c->indexed) {
		err = ovl_create_index(c->dentry, c->lowerpath.dentry, temp);
		if (err)
			goto out;
	}

	if (c->tmpfile) {
		inode_lock_nested(udir, I_MUTEX_PARENT);
		err = ovl_install_temp(c, temp, &newdentry);
		inode_unlock(udir);
	} else {
		err = ovl_install_temp(c, temp, &newdentry);
	}
	if (err)
		goto out;

	if (!c->metacopy)
		ovl_set_upperdata(d_inode(c->dentry));
	inode = d_inode(c->dentry);
	ovl_inode_update(inode, newdentry);
	if (S_ISDIR(inode->i_mode))
		ovl_set_flag(OVL_WHITEOUTS, inode);

out:
	if (err && !c->tmpfile)
		ovl_cleanup(d_inode(c->workdir), temp);
	dput(temp);
	return err;

}