#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct inode {int /*<<< orphan*/  i_sb; } ;
struct ecryptfs_mount_crypt_stat {int flags; } ;
struct ecryptfs_crypt_stat {int flags; int /*<<< orphan*/  cs_mutex; } ;
struct dentry {int dummy; } ;
struct TYPE_4__ {struct ecryptfs_crypt_stat crypt_stat; } ;
struct TYPE_3__ {struct ecryptfs_mount_crypt_stat mount_crypt_stat; } ;

/* Variables and functions */
 int ECRYPTFS_ENCRYPTED ; 
 int ECRYPTFS_I_SIZE_INITIALIZED ; 
 int ECRYPTFS_KEY_VALID ; 
 int ECRYPTFS_PLAINTEXT_PASSTHROUGH_ENABLED ; 
 int ECRYPTFS_POLICY_APPLIED ; 
 int ECRYPTFS_XATTR_METADATA_ENABLED ; 
 int EIO ; 
 struct inode* d_inode (struct dentry*) ; 
 int ecryptfs_initialize_file (struct dentry*,struct inode*) ; 
 int /*<<< orphan*/  ecryptfs_inode_to_lower (struct inode*) ; 
 TYPE_2__* ecryptfs_inode_to_private (struct inode*) ; 
 int ecryptfs_read_metadata (struct dentry*) ; 
 TYPE_1__* ecryptfs_superblock_to_private (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i_size_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int read_or_initialize_metadata(struct dentry *dentry)
{
	struct inode *inode = d_inode(dentry);
	struct ecryptfs_mount_crypt_stat *mount_crypt_stat;
	struct ecryptfs_crypt_stat *crypt_stat;
	int rc;

	crypt_stat = &ecryptfs_inode_to_private(inode)->crypt_stat;
	mount_crypt_stat = &ecryptfs_superblock_to_private(
						inode->i_sb)->mount_crypt_stat;
	mutex_lock(&crypt_stat->cs_mutex);

	if (crypt_stat->flags & ECRYPTFS_POLICY_APPLIED &&
	    crypt_stat->flags & ECRYPTFS_KEY_VALID) {
		rc = 0;
		goto out;
	}

	rc = ecryptfs_read_metadata(dentry);
	if (!rc)
		goto out;

	if (mount_crypt_stat->flags & ECRYPTFS_PLAINTEXT_PASSTHROUGH_ENABLED) {
		crypt_stat->flags &= ~(ECRYPTFS_I_SIZE_INITIALIZED
				       | ECRYPTFS_ENCRYPTED);
		rc = 0;
		goto out;
	}

	if (!(mount_crypt_stat->flags & ECRYPTFS_XATTR_METADATA_ENABLED) &&
	    !i_size_read(ecryptfs_inode_to_lower(inode))) {
		rc = ecryptfs_initialize_file(dentry, inode);
		if (!rc)
			goto out;
	}

	rc = -EIO;
out:
	mutex_unlock(&crypt_stat->cs_mutex);
	return rc;
}