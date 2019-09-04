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
struct TYPE_2__ {int /*<<< orphan*/  len; int /*<<< orphan*/  name; } ;
struct ovl_copy_up_ctx {scalar_t__ tmpfile; int /*<<< orphan*/  workdir; TYPE_1__ destname; int /*<<< orphan*/  destdir; } ;
struct inode {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct dentry*) ; 
 int PTR_ERR (struct dentry*) ; 
 struct inode* d_inode (int /*<<< orphan*/ ) ; 
 struct dentry* dget (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 struct dentry* lookup_one_len (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ovl_do_link (struct dentry*,struct inode*,struct dentry*) ; 
 int ovl_do_rename (struct inode*,struct dentry*,struct inode*,struct dentry*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ovl_install_temp(struct ovl_copy_up_ctx *c, struct dentry *temp,
			    struct dentry **newdentry)
{
	int err;
	struct dentry *upper;
	struct inode *udir = d_inode(c->destdir);

	upper = lookup_one_len(c->destname.name, c->destdir, c->destname.len);
	if (IS_ERR(upper))
		return PTR_ERR(upper);

	if (c->tmpfile)
		err = ovl_do_link(temp, udir, upper);
	else
		err = ovl_do_rename(d_inode(c->workdir), temp, udir, upper, 0);

	if (!err)
		*newdentry = dget(c->tmpfile ? upper : temp);
	dput(upper);

	return err;
}