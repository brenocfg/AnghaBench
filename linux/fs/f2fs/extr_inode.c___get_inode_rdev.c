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
struct f2fs_inode {scalar_t__* i_addr; } ;

/* Variables and functions */
 scalar_t__ S_ISBLK (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISCHR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISFIFO (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISSOCK (int /*<<< orphan*/ ) ; 
 int get_extra_isize (struct inode*) ; 
 int /*<<< orphan*/  le32_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  new_decode_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  old_decode_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __get_inode_rdev(struct inode *inode, struct f2fs_inode *ri)
{
	int extra_size = get_extra_isize(inode);

	if (S_ISCHR(inode->i_mode) || S_ISBLK(inode->i_mode) ||
			S_ISFIFO(inode->i_mode) || S_ISSOCK(inode->i_mode)) {
		if (ri->i_addr[extra_size])
			inode->i_rdev = old_decode_dev(
				le32_to_cpu(ri->i_addr[extra_size]));
		else
			inode->i_rdev = new_decode_dev(
				le32_to_cpu(ri->i_addr[extra_size + 1]));
	}
}