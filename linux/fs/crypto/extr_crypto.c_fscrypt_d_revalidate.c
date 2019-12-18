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
struct dentry {int d_flags; } ;

/* Variables and functions */
 int DCACHE_ENCRYPTED_NAME ; 
 int ECHILD ; 
 unsigned int LOOKUP_RCU ; 
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 struct dentry* dget_parent (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int fscrypt_get_encryption_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fscrypt_has_encryption_key (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fscrypt_d_revalidate(struct dentry *dentry, unsigned int flags)
{
	struct dentry *dir;
	int err;
	int valid;

	/*
	 * Plaintext names are always valid, since fscrypt doesn't support
	 * reverting to ciphertext names without evicting the directory's inode
	 * -- which implies eviction of the dentries in the directory.
	 */
	if (!(dentry->d_flags & DCACHE_ENCRYPTED_NAME))
		return 1;

	/*
	 * Ciphertext name; valid if the directory's key is still unavailable.
	 *
	 * Although fscrypt forbids rename() on ciphertext names, we still must
	 * use dget_parent() here rather than use ->d_parent directly.  That's
	 * because a corrupted fs image may contain directory hard links, which
	 * the VFS handles by moving the directory's dentry tree in the dcache
	 * each time ->lookup() finds the directory and it already has a dentry
	 * elsewhere.  Thus ->d_parent can be changing, and we must safely grab
	 * a reference to some ->d_parent to prevent it from being freed.
	 */

	if (flags & LOOKUP_RCU)
		return -ECHILD;

	dir = dget_parent(dentry);
	err = fscrypt_get_encryption_info(d_inode(dir));
	valid = !fscrypt_has_encryption_key(d_inode(dir));
	dput(dir);

	if (err < 0)
		return err;

	return valid;
}