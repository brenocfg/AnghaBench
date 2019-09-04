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
struct inode {int dummy; } ;
struct ext4_ext_path {scalar_t__ p_bh; } ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_2__ {int /*<<< orphan*/  i_data_sem; } ;

/* Variables and functions */
 TYPE_1__* EXT4_I (struct inode*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int __ext4_handle_dirty_metadata (char const*,unsigned int,int /*<<< orphan*/ *,struct inode*,scalar_t__) ; 
 int /*<<< orphan*/  ext4_extent_block_csum_set (struct inode*,int /*<<< orphan*/ ) ; 
 int ext4_mark_inode_dirty (int /*<<< orphan*/ *,struct inode*) ; 
 int /*<<< orphan*/  ext_block_hdr (scalar_t__) ; 
 int /*<<< orphan*/  rwsem_is_locked (int /*<<< orphan*/ *) ; 

int __ext4_ext_dirty(const char *where, unsigned int line, handle_t *handle,
		     struct inode *inode, struct ext4_ext_path *path)
{
	int err;

	WARN_ON(!rwsem_is_locked(&EXT4_I(inode)->i_data_sem));
	if (path->p_bh) {
		ext4_extent_block_csum_set(inode, ext_block_hdr(path->p_bh));
		/* path points to block */
		err = __ext4_handle_dirty_metadata(where, line, handle,
						   inode, path->p_bh);
	} else {
		/* path points to leaf/index in inode body */
		err = ext4_mark_inode_dirty(handle, inode);
	}
	return err;
}