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
struct dentry {int /*<<< orphan*/  d_lock; int /*<<< orphan*/  d_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCACHE_ENCRYPTED_WITH_KEY ; 
 int /*<<< orphan*/  d_set_d_op (struct dentry*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fscrypt_d_ops ; 
 int fscrypt_get_encryption_info (struct inode*) ; 
 scalar_t__ fscrypt_has_encryption_key (struct inode*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int __fscrypt_prepare_lookup(struct inode *dir, struct dentry *dentry)
{
	int err = fscrypt_get_encryption_info(dir);

	if (err)
		return err;

	if (fscrypt_has_encryption_key(dir)) {
		spin_lock(&dentry->d_lock);
		dentry->d_flags |= DCACHE_ENCRYPTED_WITH_KEY;
		spin_unlock(&dentry->d_lock);
	}

	d_set_d_op(dentry, &fscrypt_d_ops);
	return 0;
}