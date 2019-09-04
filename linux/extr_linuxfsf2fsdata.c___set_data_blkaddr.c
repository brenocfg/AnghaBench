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
struct f2fs_node {int dummy; } ;
struct dnode_of_data {int ofs_in_node; int /*<<< orphan*/  data_blkaddr; int /*<<< orphan*/  inode; int /*<<< orphan*/  node_page; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 struct f2fs_node* F2FS_NODE (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_INODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * blkaddr_in_node (struct f2fs_node*) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 scalar_t__ f2fs_has_extra_attr (int /*<<< orphan*/ ) ; 
 int get_extra_isize (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __set_data_blkaddr(struct dnode_of_data *dn)
{
	struct f2fs_node *rn = F2FS_NODE(dn->node_page);
	__le32 *addr_array;
	int base = 0;

	if (IS_INODE(dn->node_page) && f2fs_has_extra_attr(dn->inode))
		base = get_extra_isize(dn->inode);

	/* Get physical address of data block */
	addr_array = blkaddr_in_node(rn);
	addr_array[base + dn->ofs_in_node] = cpu_to_le32(dn->data_blkaddr);
}