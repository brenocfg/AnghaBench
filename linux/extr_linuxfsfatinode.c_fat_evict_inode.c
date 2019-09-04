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
struct inode {scalar_t__ i_size; int /*<<< orphan*/  i_nlink; int /*<<< orphan*/  i_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_inode (struct inode*) ; 
 int /*<<< orphan*/  fat_cache_inval_inode (struct inode*) ; 
 int /*<<< orphan*/  fat_detach (struct inode*) ; 
 int /*<<< orphan*/  fat_free_eofblocks (struct inode*) ; 
 int /*<<< orphan*/  fat_truncate_blocks (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  invalidate_inode_buffers (struct inode*) ; 
 int /*<<< orphan*/  truncate_inode_pages_final (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fat_evict_inode(struct inode *inode)
{
	truncate_inode_pages_final(&inode->i_data);
	if (!inode->i_nlink) {
		inode->i_size = 0;
		fat_truncate_blocks(inode, 0);
	} else
		fat_free_eofblocks(inode);

	invalidate_inode_buffers(inode);
	clear_inode(inode);
	fat_cache_inval_inode(inode);
	fat_detach(inode);
}