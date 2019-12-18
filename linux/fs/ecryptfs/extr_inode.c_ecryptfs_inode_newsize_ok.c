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
struct inode {int dummy; } ;
struct ecryptfs_crypt_stat {int dummy; } ;
typedef  scalar_t__ loff_t ;
struct TYPE_2__ {struct ecryptfs_crypt_stat crypt_stat; } ;

/* Variables and functions */
 TYPE_1__* ecryptfs_inode_to_private (struct inode*) ; 
 scalar_t__ i_size_read (struct inode*) ; 
 int inode_newsize_ok (struct inode*,scalar_t__) ; 
 scalar_t__ upper_size_to_lower_size (struct ecryptfs_crypt_stat*,scalar_t__) ; 

__attribute__((used)) static int ecryptfs_inode_newsize_ok(struct inode *inode, loff_t offset)
{
	struct ecryptfs_crypt_stat *crypt_stat;
	loff_t lower_oldsize, lower_newsize;

	crypt_stat = &ecryptfs_inode_to_private(inode)->crypt_stat;
	lower_oldsize = upper_size_to_lower_size(crypt_stat,
						 i_size_read(inode));
	lower_newsize = upper_size_to_lower_size(crypt_stat, offset);
	if (lower_newsize > lower_oldsize) {
		/*
		 * The eCryptfs inode and the new *lower* size are mixed here
		 * because we may not have the lower i_mutex held and/or it may
		 * not be appropriate to call inode_newsize_ok() with inodes
		 * from other filesystems.
		 */
		return inode_newsize_ok(inode, lower_newsize);
	}

	return 0;
}