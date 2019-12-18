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
struct ecryptfs_mount_crypt_stat {int flags; } ;
struct ecryptfs_crypt_stat {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECRYPTFS_ENCFN_USE_FEK ; 
 int /*<<< orphan*/  ECRYPTFS_ENCFN_USE_MOUNT_FNEK ; 
 int ECRYPTFS_ENCRYPTED_VIEW_ENABLED ; 
 int /*<<< orphan*/  ECRYPTFS_ENCRYPT_FILENAMES ; 
 int ECRYPTFS_GLOBAL_ENCFN_USE_FEK ; 
 int ECRYPTFS_GLOBAL_ENCFN_USE_MOUNT_FNEK ; 
 int ECRYPTFS_GLOBAL_ENCRYPT_FILENAMES ; 
 int /*<<< orphan*/  ECRYPTFS_METADATA_IN_XATTR ; 
 int /*<<< orphan*/  ECRYPTFS_VIEW_AS_ENCRYPTED ; 
 int ECRYPTFS_XATTR_METADATA_ENABLED ; 

__attribute__((used)) static void ecryptfs_copy_mount_wide_flags_to_inode_flags(
	struct ecryptfs_crypt_stat *crypt_stat,
	struct ecryptfs_mount_crypt_stat *mount_crypt_stat)
{
	if (mount_crypt_stat->flags & ECRYPTFS_XATTR_METADATA_ENABLED)
		crypt_stat->flags |= ECRYPTFS_METADATA_IN_XATTR;
	if (mount_crypt_stat->flags & ECRYPTFS_ENCRYPTED_VIEW_ENABLED)
		crypt_stat->flags |= ECRYPTFS_VIEW_AS_ENCRYPTED;
	if (mount_crypt_stat->flags & ECRYPTFS_GLOBAL_ENCRYPT_FILENAMES) {
		crypt_stat->flags |= ECRYPTFS_ENCRYPT_FILENAMES;
		if (mount_crypt_stat->flags
		    & ECRYPTFS_GLOBAL_ENCFN_USE_MOUNT_FNEK)
			crypt_stat->flags |= ECRYPTFS_ENCFN_USE_MOUNT_FNEK;
		else if (mount_crypt_stat->flags
			 & ECRYPTFS_GLOBAL_ENCFN_USE_FEK)
			crypt_stat->flags |= ECRYPTFS_ENCFN_USE_FEK;
	}
}