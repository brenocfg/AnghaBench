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
struct ecryptfs_inode_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ecryptfs_inode_info_cache ; 
 struct ecryptfs_inode_info* ecryptfs_inode_to_private (struct inode*) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct ecryptfs_inode_info*) ; 

__attribute__((used)) static void ecryptfs_free_inode(struct inode *inode)
{
	struct ecryptfs_inode_info *inode_info;
	inode_info = ecryptfs_inode_to_private(inode);

	kmem_cache_free(ecryptfs_inode_info_cache, inode_info);
}