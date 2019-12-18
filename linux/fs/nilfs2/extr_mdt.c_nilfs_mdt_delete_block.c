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
struct nilfs_inode_info {int /*<<< orphan*/  i_bmap; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 struct nilfs_inode_info* NILFS_I (struct inode*) ; 
 int nilfs_bmap_delete (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  nilfs_mdt_forget_block (struct inode*,unsigned long) ; 
 int /*<<< orphan*/  nilfs_mdt_mark_dirty (struct inode*) ; 

int nilfs_mdt_delete_block(struct inode *inode, unsigned long block)
{
	struct nilfs_inode_info *ii = NILFS_I(inode);
	int err;

	err = nilfs_bmap_delete(ii->i_bmap, block);
	if (!err || err == -ENOENT) {
		nilfs_mdt_mark_dirty(inode);
		nilfs_mdt_forget_block(inode, block);
	}
	return err;
}