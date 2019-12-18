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
 int ext4_xattr_inode_update_ref (int /*<<< orphan*/ *,struct inode*,int) ; 

__attribute__((used)) static int ext4_xattr_inode_dec_ref(handle_t *handle, struct inode *ea_inode)
{
	return ext4_xattr_inode_update_ref(handle, ea_inode, -1);
}