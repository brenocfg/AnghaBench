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
struct iattr {int ia_valid; int /*<<< orphan*/  ia_size; } ;
struct dentry {int dummy; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int ATTR_SIZE ; 
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 struct dentry* ecryptfs_dentry_to_lower (struct dentry*) ; 
 int ecryptfs_inode_newsize_ok (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_unlock (int /*<<< orphan*/ ) ; 
 int notify_change (struct dentry*,struct iattr*,int /*<<< orphan*/ *) ; 
 int truncate_upper (struct dentry*,struct iattr*,struct iattr*) ; 

int ecryptfs_truncate(struct dentry *dentry, loff_t new_length)
{
	struct iattr ia = { .ia_valid = ATTR_SIZE, .ia_size = new_length };
	struct iattr lower_ia = { .ia_valid = 0 };
	int rc;

	rc = ecryptfs_inode_newsize_ok(d_inode(dentry), new_length);
	if (rc)
		return rc;

	rc = truncate_upper(dentry, &ia, &lower_ia);
	if (!rc && lower_ia.ia_valid & ATTR_SIZE) {
		struct dentry *lower_dentry = ecryptfs_dentry_to_lower(dentry);

		inode_lock(d_inode(lower_dentry));
		rc = notify_change(lower_dentry, &lower_ia, NULL);
		inode_unlock(d_inode(lower_dentry));
	}
	return rc;
}