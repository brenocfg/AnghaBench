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
struct dentry {int d_flags; } ;

/* Variables and functions */
 int DCACHE_ENCRYPTED_NAME ; 
 int ENOKEY ; 
 int EXDEV ; 
 int /*<<< orphan*/  fscrypt_has_permitted_context (struct inode*,struct inode*) ; 
 int fscrypt_require_key (struct inode*) ; 

int __fscrypt_prepare_link(struct inode *inode, struct inode *dir,
			   struct dentry *dentry)
{
	int err;

	err = fscrypt_require_key(dir);
	if (err)
		return err;

	/* ... in case we looked up ciphertext name before key was added */
	if (dentry->d_flags & DCACHE_ENCRYPTED_NAME)
		return -ENOKEY;

	if (!fscrypt_has_permitted_context(dir, inode))
		return -EXDEV;

	return 0;
}