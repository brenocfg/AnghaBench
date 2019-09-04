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
struct inode {int /*<<< orphan*/  i_mode; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  EXT2_I (struct inode*) ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __ext2_truncate_blocks (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dax_sem_down_write (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dax_sem_up_write (int /*<<< orphan*/ ) ; 
 scalar_t__ ext2_inode_is_fast_symlink (struct inode*) ; 

__attribute__((used)) static void ext2_truncate_blocks(struct inode *inode, loff_t offset)
{
	if (!(S_ISREG(inode->i_mode) || S_ISDIR(inode->i_mode) ||
	    S_ISLNK(inode->i_mode)))
		return;
	if (ext2_inode_is_fast_symlink(inode))
		return;

	dax_sem_down_write(EXT2_I(inode));
	__ext2_truncate_blocks(inode, offset);
	dax_sem_up_write(EXT2_I(inode));
}