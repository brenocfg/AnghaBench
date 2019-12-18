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
struct dnode_of_data {scalar_t__ data_blkaddr; int /*<<< orphan*/  inode; scalar_t__ ofs_in_node; int /*<<< orphan*/  node_page; } ;
typedef  scalar_t__ pgoff_t ;
typedef  scalar_t__ block_t ;

/* Variables and functions */
 scalar_t__ NEW_ADDR ; 
 scalar_t__ NULL_ADDR ; 
 int /*<<< orphan*/  f2fs_may_extent_tree (int /*<<< orphan*/ ) ; 
 scalar_t__ f2fs_start_bidx_of_node (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_update_extent_tree_range (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  ofs_of_node (int /*<<< orphan*/ ) ; 

void f2fs_update_extent_cache(struct dnode_of_data *dn)
{
	pgoff_t fofs;
	block_t blkaddr;

	if (!f2fs_may_extent_tree(dn->inode))
		return;

	if (dn->data_blkaddr == NEW_ADDR)
		blkaddr = NULL_ADDR;
	else
		blkaddr = dn->data_blkaddr;

	fofs = f2fs_start_bidx_of_node(ofs_of_node(dn->node_page), dn->inode) +
								dn->ofs_in_node;
	f2fs_update_extent_tree_range(dn->inode, fofs, blkaddr, 1);
}