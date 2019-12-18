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
struct fscrypt_name {scalar_t__ is_ciphertext_name; } ;
struct dentry {int /*<<< orphan*/  d_lock; int /*<<< orphan*/  d_flags; int /*<<< orphan*/  d_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCACHE_ENCRYPTED_NAME ; 
 int ENOENT ; 
 int /*<<< orphan*/  d_set_d_op (struct dentry*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fscrypt_d_ops ; 
 int fscrypt_setup_filename (struct inode*,int /*<<< orphan*/ *,int,struct fscrypt_name*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int __fscrypt_prepare_lookup(struct inode *dir, struct dentry *dentry,
			     struct fscrypt_name *fname)
{
	int err = fscrypt_setup_filename(dir, &dentry->d_name, 1, fname);

	if (err && err != -ENOENT)
		return err;

	if (fname->is_ciphertext_name) {
		spin_lock(&dentry->d_lock);
		dentry->d_flags |= DCACHE_ENCRYPTED_NAME;
		spin_unlock(&dentry->d_lock);
		d_set_d_op(dentry, &fscrypt_d_ops);
	}
	return err;
}