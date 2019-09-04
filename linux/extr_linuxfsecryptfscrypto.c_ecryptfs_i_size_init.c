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
typedef  scalar_t__ u64 ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct ecryptfs_mount_crypt_stat {int flags; } ;
struct ecryptfs_crypt_stat {int flags; scalar_t__ metadata_size; } ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_4__ {struct ecryptfs_crypt_stat crypt_stat; } ;
struct TYPE_3__ {struct ecryptfs_mount_crypt_stat mount_crypt_stat; } ;

/* Variables and functions */
 int ECRYPTFS_ENCRYPTED_VIEW_ENABLED ; 
 int ECRYPTFS_I_SIZE_INITIALIZED ; 
 int ECRYPTFS_METADATA_IN_XATTR ; 
 int /*<<< orphan*/  ecryptfs_inode_to_lower (struct inode*) ; 
 TYPE_2__* ecryptfs_inode_to_private (struct inode*) ; 
 TYPE_1__* ecryptfs_superblock_to_private (int /*<<< orphan*/ ) ; 
 scalar_t__ get_unaligned_be64 (char const*) ; 
 scalar_t__ i_size_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i_size_write (struct inode*,int /*<<< orphan*/ ) ; 

void ecryptfs_i_size_init(const char *page_virt, struct inode *inode)
{
	struct ecryptfs_mount_crypt_stat *mount_crypt_stat;
	struct ecryptfs_crypt_stat *crypt_stat;
	u64 file_size;

	crypt_stat = &ecryptfs_inode_to_private(inode)->crypt_stat;
	mount_crypt_stat =
		&ecryptfs_superblock_to_private(inode->i_sb)->mount_crypt_stat;
	if (mount_crypt_stat->flags & ECRYPTFS_ENCRYPTED_VIEW_ENABLED) {
		file_size = i_size_read(ecryptfs_inode_to_lower(inode));
		if (crypt_stat->flags & ECRYPTFS_METADATA_IN_XATTR)
			file_size += crypt_stat->metadata_size;
	} else
		file_size = get_unaligned_be64(page_virt);
	i_size_write(inode, (loff_t)file_size);
	crypt_stat->flags |= ECRYPTFS_I_SIZE_INITIALIZED;
}