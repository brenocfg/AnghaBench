#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct file {int dummy; } ;
struct dentry {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  i_ino; } ;

/* Variables and functions */
 int EPERM ; 
 scalar_t__ IS_ENCRYPTED (TYPE_1__*) ; 
 TYPE_1__* d_inode (struct dentry*) ; 
 struct dentry* dget_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  file_dentry (struct file*) ; 
 int /*<<< orphan*/  fscrypt_has_permitted_context (TYPE_1__*,struct inode*) ; 
 int fscrypt_require_key (struct inode*) ; 
 int /*<<< orphan*/  fscrypt_warn (struct inode*,char*,int /*<<< orphan*/ ) ; 

int fscrypt_file_open(struct inode *inode, struct file *filp)
{
	int err;
	struct dentry *dir;

	err = fscrypt_require_key(inode);
	if (err)
		return err;

	dir = dget_parent(file_dentry(filp));
	if (IS_ENCRYPTED(d_inode(dir)) &&
	    !fscrypt_has_permitted_context(d_inode(dir), inode)) {
		fscrypt_warn(inode,
			     "Inconsistent encryption context (parent directory: %lu)",
			     d_inode(dir)->i_ino);
		err = -EPERM;
	}
	dput(dir);
	return err;
}