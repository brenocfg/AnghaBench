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
struct ecryptfs_inode_info {int /*<<< orphan*/  crypt_stat; int /*<<< orphan*/  lower_file; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecryptfs_destroy_crypt_stat (int /*<<< orphan*/ *) ; 
 struct ecryptfs_inode_info* ecryptfs_inode_to_private (struct inode*) ; 

__attribute__((used)) static void ecryptfs_destroy_inode(struct inode *inode)
{
	struct ecryptfs_inode_info *inode_info;

	inode_info = ecryptfs_inode_to_private(inode);
	BUG_ON(inode_info->lower_file);
	ecryptfs_destroy_crypt_stat(&inode_info->crypt_stat);
}