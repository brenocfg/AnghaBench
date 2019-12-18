#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct path {struct dentry* dentry; } ;
struct kstat {size_t size; } ;
struct ecryptfs_mount_crypt_stat {int flags; } ;
struct dentry {int /*<<< orphan*/  d_sb; } ;
struct TYPE_2__ {struct ecryptfs_mount_crypt_stat mount_crypt_stat; } ;

/* Variables and functions */
 int ECRYPTFS_GLOBAL_ENCRYPT_FILENAMES ; 
 int /*<<< orphan*/  IS_ERR (char*) ; 
 int PTR_ERR (char*) ; 
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 char* ecryptfs_readlink_lower (struct dentry*,size_t*) ; 
 TYPE_1__* ecryptfs_superblock_to_private (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  generic_fillattr (int /*<<< orphan*/ ,struct kstat*) ; 
 int /*<<< orphan*/  kfree (char*) ; 

__attribute__((used)) static int ecryptfs_getattr_link(const struct path *path, struct kstat *stat,
				 u32 request_mask, unsigned int flags)
{
	struct dentry *dentry = path->dentry;
	struct ecryptfs_mount_crypt_stat *mount_crypt_stat;
	int rc = 0;

	mount_crypt_stat = &ecryptfs_superblock_to_private(
						dentry->d_sb)->mount_crypt_stat;
	generic_fillattr(d_inode(dentry), stat);
	if (mount_crypt_stat->flags & ECRYPTFS_GLOBAL_ENCRYPT_FILENAMES) {
		char *target;
		size_t targetsiz;

		target = ecryptfs_readlink_lower(dentry, &targetsiz);
		if (!IS_ERR(target)) {
			kfree(target);
			stat->size = targetsiz;
		} else {
			rc = PTR_ERR(target);
		}
	}
	return rc;
}