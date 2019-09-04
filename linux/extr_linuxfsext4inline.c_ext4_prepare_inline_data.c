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
struct inode {int dummy; } ;
struct ext4_inode_info {scalar_t__ i_inline_off; } ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 int ENOSPC ; 
 struct ext4_inode_info* EXT4_I (struct inode*) ; 
 int /*<<< orphan*/  EXT4_STATE_MAY_INLINE_DATA ; 
 int ext4_create_inline_data (int /*<<< orphan*/ *,struct inode*,unsigned int) ; 
 int ext4_get_max_inline_size (struct inode*) ; 
 int /*<<< orphan*/  ext4_test_inode_state (struct inode*,int /*<<< orphan*/ ) ; 
 int ext4_update_inline_data (int /*<<< orphan*/ *,struct inode*,unsigned int) ; 
 int /*<<< orphan*/  ext4_write_lock_xattr (struct inode*,int*) ; 
 int /*<<< orphan*/  ext4_write_unlock_xattr (struct inode*,int*) ; 

__attribute__((used)) static int ext4_prepare_inline_data(handle_t *handle, struct inode *inode,
				    unsigned int len)
{
	int ret, size, no_expand;
	struct ext4_inode_info *ei = EXT4_I(inode);

	if (!ext4_test_inode_state(inode, EXT4_STATE_MAY_INLINE_DATA))
		return -ENOSPC;

	size = ext4_get_max_inline_size(inode);
	if (size < len)
		return -ENOSPC;

	ext4_write_lock_xattr(inode, &no_expand);

	if (ei->i_inline_off)
		ret = ext4_update_inline_data(handle, inode, len);
	else
		ret = ext4_create_inline_data(handle, inode, len);

	ext4_write_unlock_xattr(inode, &no_expand);
	return ret;
}