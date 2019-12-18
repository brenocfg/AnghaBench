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
struct inode {int /*<<< orphan*/  i_rdev; int /*<<< orphan*/  i_mode; } ;
struct f2fs_inode {void** i_addr; } ;

/* Variables and functions */
 scalar_t__ S_ISBLK (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISCHR (int /*<<< orphan*/ ) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int get_extra_isize (struct inode*) ; 
 int /*<<< orphan*/  new_encode_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  old_encode_dev (int /*<<< orphan*/ ) ; 
 scalar_t__ old_valid_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __set_inode_rdev(struct inode *inode, struct f2fs_inode *ri)
{
	int extra_size = get_extra_isize(inode);

	if (S_ISCHR(inode->i_mode) || S_ISBLK(inode->i_mode)) {
		if (old_valid_dev(inode->i_rdev)) {
			ri->i_addr[extra_size] =
				cpu_to_le32(old_encode_dev(inode->i_rdev));
			ri->i_addr[extra_size + 1] = 0;
		} else {
			ri->i_addr[extra_size] = 0;
			ri->i_addr[extra_size + 1] =
				cpu_to_le32(new_encode_dev(inode->i_rdev));
			ri->i_addr[extra_size + 2] = 0;
		}
	}
}