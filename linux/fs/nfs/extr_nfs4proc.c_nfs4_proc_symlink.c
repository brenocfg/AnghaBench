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
struct page {int dummy; } ;
struct nfs4_label {int dummy; } ;
struct nfs4_exception {int interruptible; scalar_t__ retry; } ;
struct inode {int dummy; } ;
struct iattr {int dummy; } ;
struct dentry {int /*<<< orphan*/  d_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFS_SERVER (struct inode*) ; 
 int _nfs4_proc_symlink (struct inode*,struct dentry*,struct page*,unsigned int,struct iattr*,struct nfs4_label*) ; 
 int nfs4_handle_exception (int /*<<< orphan*/ ,int,struct nfs4_exception*) ; 
 struct nfs4_label* nfs4_label_init_security (struct inode*,struct dentry*,struct iattr*,struct nfs4_label*) ; 
 int /*<<< orphan*/  nfs4_label_release_security (struct nfs4_label*) ; 
 int /*<<< orphan*/  trace_nfs4_symlink (struct inode*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int nfs4_proc_symlink(struct inode *dir, struct dentry *dentry,
		struct page *page, unsigned int len, struct iattr *sattr)
{
	struct nfs4_exception exception = {
		.interruptible = true,
	};
	struct nfs4_label l, *label = NULL;
	int err;

	label = nfs4_label_init_security(dir, dentry, sattr, &l);

	do {
		err = _nfs4_proc_symlink(dir, dentry, page, len, sattr, label);
		trace_nfs4_symlink(dir, &dentry->d_name, err);
		err = nfs4_handle_exception(NFS_SERVER(dir), err,
				&exception);
	} while (exception.retry);

	nfs4_label_release_security(label);
	return err;
}