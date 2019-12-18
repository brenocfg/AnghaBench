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

/* Variables and functions */
 int /*<<< orphan*/  NILFS_I (struct inode*) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nilfs_inode_cachep ; 
 scalar_t__ nilfs_is_metadata_file_inode (struct inode*) ; 
 int /*<<< orphan*/  nilfs_mdt_destroy (struct inode*) ; 

__attribute__((used)) static void nilfs_free_inode(struct inode *inode)
{
	if (nilfs_is_metadata_file_inode(inode))
		nilfs_mdt_destroy(inode);

	kmem_cache_free(nilfs_inode_cachep, NILFS_I(inode));
}