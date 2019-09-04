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
struct inode {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int EPERM ; 
 scalar_t__ IS_ENCRYPTED (struct inode*) ; 
 unsigned int RENAME_EXCHANGE ; 
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 int /*<<< orphan*/  fscrypt_has_permitted_context (struct inode*,int /*<<< orphan*/ ) ; 
 int fscrypt_require_key (struct inode*) ; 

int __fscrypt_prepare_rename(struct inode *old_dir, struct dentry *old_dentry,
			     struct inode *new_dir, struct dentry *new_dentry,
			     unsigned int flags)
{
	int err;

	err = fscrypt_require_key(old_dir);
	if (err)
		return err;

	err = fscrypt_require_key(new_dir);
	if (err)
		return err;

	if (old_dir != new_dir) {
		if (IS_ENCRYPTED(new_dir) &&
		    !fscrypt_has_permitted_context(new_dir,
						   d_inode(old_dentry)))
			return -EPERM;

		if ((flags & RENAME_EXCHANGE) &&
		    IS_ENCRYPTED(old_dir) &&
		    !fscrypt_has_permitted_context(old_dir,
						   d_inode(new_dentry)))
			return -EPERM;
	}
	return 0;
}