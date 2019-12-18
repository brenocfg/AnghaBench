#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct ext4_ext_path {int dummy; } ;
struct TYPE_6__ {int h_buffer_credits; } ;
typedef  TYPE_1__ handle_t ;

/* Variables and functions */
 int EAGAIN ; 
 int ext4_ext_get_access (TYPE_1__*,struct inode*,struct ext4_ext_path*) ; 
 int ext4_ext_truncate_extend_restart (TYPE_1__*,struct inode*,int) ; 
 int /*<<< orphan*/  ext4_handle_valid (TYPE_1__*) ; 
 int ext4_writepage_trans_blocks (struct inode*) ; 

__attribute__((used)) static int
ext4_access_path(handle_t *handle, struct inode *inode,
		struct ext4_ext_path *path)
{
	int credits, err;

	if (!ext4_handle_valid(handle))
		return 0;

	/*
	 * Check if need to extend journal credits
	 * 3 for leaf, sb, and inode plus 2 (bmap and group
	 * descriptor) for each block group; assume two block
	 * groups
	 */
	if (handle->h_buffer_credits < 7) {
		credits = ext4_writepage_trans_blocks(inode);
		err = ext4_ext_truncate_extend_restart(handle, inode, credits);
		/* EAGAIN is success */
		if (err && err != -EAGAIN)
			return err;
	}

	err = ext4_ext_get_access(handle, inode, path);
	return err;
}