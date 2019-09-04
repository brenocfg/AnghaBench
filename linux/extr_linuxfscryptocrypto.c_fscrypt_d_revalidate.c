#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct dentry {int d_flags; int /*<<< orphan*/  d_lock; } ;
struct TYPE_3__ {int /*<<< orphan*/ * i_crypt_info; } ;

/* Variables and functions */
 int DCACHE_ENCRYPTED_WITH_KEY ; 
 int ECHILD ; 
 int /*<<< orphan*/  IS_ENCRYPTED (TYPE_1__*) ; 
 unsigned int LOOKUP_RCU ; 
 TYPE_1__* d_inode (struct dentry*) ; 
 scalar_t__ d_is_negative (struct dentry*) ; 
 struct dentry* dget_parent (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fscrypt_d_revalidate(struct dentry *dentry, unsigned int flags)
{
	struct dentry *dir;
	int dir_has_key, cached_with_key;

	if (flags & LOOKUP_RCU)
		return -ECHILD;

	dir = dget_parent(dentry);
	if (!IS_ENCRYPTED(d_inode(dir))) {
		dput(dir);
		return 0;
	}

	spin_lock(&dentry->d_lock);
	cached_with_key = dentry->d_flags & DCACHE_ENCRYPTED_WITH_KEY;
	spin_unlock(&dentry->d_lock);
	dir_has_key = (d_inode(dir)->i_crypt_info != NULL);
	dput(dir);

	/*
	 * If the dentry was cached without the key, and it is a
	 * negative dentry, it might be a valid name.  We can't check
	 * if the key has since been made available due to locking
	 * reasons, so we fail the validation so ext4_lookup() can do
	 * this check.
	 *
	 * We also fail the validation if the dentry was created with
	 * the key present, but we no longer have the key, or vice versa.
	 */
	if ((!cached_with_key && d_is_negative(dentry)) ||
			(!cached_with_key && dir_has_key) ||
			(cached_with_key && !dir_has_key))
		return 0;
	return 1;
}