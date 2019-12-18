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
struct inode {int /*<<< orphan*/  i_writecount; } ;
struct file {int f_mode; scalar_t__ private_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  i_data_sem; int /*<<< orphan*/  i_reserved_data_blocks; } ;

/* Variables and functions */
 TYPE_1__* EXT4_I (struct inode*) ; 
 int /*<<< orphan*/  EXT4_STATE_DA_ALLOC_CLOSE ; 
 int FMODE_WRITE ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ext4_alloc_da_blocks (struct inode*) ; 
 int /*<<< orphan*/  ext4_clear_inode_state (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_discard_preallocations (struct inode*) ; 
 int /*<<< orphan*/  ext4_htree_free_dir_info (scalar_t__) ; 
 scalar_t__ ext4_test_inode_state (struct inode*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_dx (struct inode*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ext4_release_file(struct inode *inode, struct file *filp)
{
	if (ext4_test_inode_state(inode, EXT4_STATE_DA_ALLOC_CLOSE)) {
		ext4_alloc_da_blocks(inode);
		ext4_clear_inode_state(inode, EXT4_STATE_DA_ALLOC_CLOSE);
	}
	/* if we are the last writer on the inode, drop the block reservation */
	if ((filp->f_mode & FMODE_WRITE) &&
			(atomic_read(&inode->i_writecount) == 1) &&
		        !EXT4_I(inode)->i_reserved_data_blocks)
	{
		down_write(&EXT4_I(inode)->i_data_sem);
		ext4_discard_preallocations(inode);
		up_write(&EXT4_I(inode)->i_data_sem);
	}
	if (is_dx(inode) && filp->private_data)
		ext4_htree_free_dir_info(filp->private_data);

	return 0;
}