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
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 int ext4_destroy_inline_data_nolock (int /*<<< orphan*/ *,struct inode*) ; 
 int /*<<< orphan*/  ext4_write_lock_xattr (struct inode*,int*) ; 
 int /*<<< orphan*/  ext4_write_unlock_xattr (struct inode*,int*) ; 

int ext4_destroy_inline_data(handle_t *handle, struct inode *inode)
{
	int ret, no_expand;

	ext4_write_lock_xattr(inode, &no_expand);
	ret = ext4_destroy_inline_data_nolock(handle, inode);
	ext4_write_unlock_xattr(inode, &no_expand);

	return ret;
}