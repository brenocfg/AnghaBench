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
struct nilfs_root {int /*<<< orphan*/  blocks_count; } ;
struct inode {int dummy; } ;
struct TYPE_2__ {struct nilfs_root* i_root; } ;

/* Variables and functions */
 TYPE_1__* NILFS_I (struct inode*) ; 
 int /*<<< orphan*/  atomic64_sub (int,int /*<<< orphan*/ *) ; 
 int i_blocksize (struct inode*) ; 
 int /*<<< orphan*/  inode_sub_bytes (struct inode*,int) ; 

void nilfs_inode_sub_blocks(struct inode *inode, int n)
{
	struct nilfs_root *root = NILFS_I(inode)->i_root;

	inode_sub_bytes(inode, i_blocksize(inode) * n);
	if (root)
		atomic64_sub(n, &root->blocks_count);
}