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
struct super_block {int dummy; } ;
struct inode {int dummy; } ;
struct nilfs_inode_info {struct inode vfs_inode; int /*<<< orphan*/  i_btnode_cache; scalar_t__ i_cno; scalar_t__ i_state; int /*<<< orphan*/ * i_bh; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOFS ; 
 struct nilfs_inode_info* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nilfs_inode_cachep ; 
 int /*<<< orphan*/  nilfs_mapping_init (int /*<<< orphan*/ *,struct inode*) ; 

struct inode *nilfs_alloc_inode(struct super_block *sb)
{
	struct nilfs_inode_info *ii;

	ii = kmem_cache_alloc(nilfs_inode_cachep, GFP_NOFS);
	if (!ii)
		return NULL;
	ii->i_bh = NULL;
	ii->i_state = 0;
	ii->i_cno = 0;
	nilfs_mapping_init(&ii->i_btnode_cache, &ii->vfs_inode);
	return &ii->vfs_inode;
}