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
struct ext4_iloc {int dummy; } ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  EXT4_STATE_MAY_INLINE_DATA ; 
 int /*<<< orphan*/  ext4_create_inline_data (int /*<<< orphan*/ *,struct inode*,int) ; 
 int /*<<< orphan*/  ext4_set_inode_state (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_write_inline_data (struct inode*,struct ext4_iloc*,void*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ext4_restore_inline_data(handle_t *handle, struct inode *inode,
				     struct ext4_iloc *iloc,
				     void *buf, int inline_size)
{
	ext4_create_inline_data(handle, inode, inline_size);
	ext4_write_inline_data(inode, iloc, buf, 0, inline_size);
	ext4_set_inode_state(inode, EXT4_STATE_MAY_INLINE_DATA);
}