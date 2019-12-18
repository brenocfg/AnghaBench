#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct inode {int i_size; } ;
struct hfs_btree {int free_nodes; int node_size_shift; int node_count; TYPE_2__* sb; struct inode* inode; } ;
typedef  int loff_t ;
struct TYPE_6__ {int phys_size; int fs_blocks; scalar_t__ alloc_blocks; } ;
struct TYPE_5__ {int s_blocksize_bits; } ;
struct TYPE_4__ {int alloc_blksz; } ;

/* Variables and functions */
 TYPE_3__* HFS_I (struct inode*) ; 
 TYPE_1__* HFS_SB (TYPE_2__*) ; 
 int hfs_extend_file (struct inode*) ; 
 int /*<<< orphan*/  inode_set_bytes (struct inode*,int) ; 

int hfs_bmap_reserve(struct hfs_btree *tree, int rsvd_nodes)
{
	struct inode *inode = tree->inode;
	u32 count;
	int res;

	while (tree->free_nodes < rsvd_nodes) {
		res = hfs_extend_file(inode);
		if (res)
			return res;
		HFS_I(inode)->phys_size = inode->i_size =
				(loff_t)HFS_I(inode)->alloc_blocks *
				HFS_SB(tree->sb)->alloc_blksz;
		HFS_I(inode)->fs_blocks = inode->i_size >>
					  tree->sb->s_blocksize_bits;
		inode_set_bytes(inode, inode->i_size);
		count = inode->i_size >> tree->node_size_shift;
		tree->free_nodes += count - tree->node_count;
		tree->node_count = count;
	}
	return 0;
}