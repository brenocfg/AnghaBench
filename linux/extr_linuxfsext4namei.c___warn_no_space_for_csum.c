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

/* Variables and functions */
 int /*<<< orphan*/  __ext4_warning_inode (struct inode*,char const*,unsigned int,char*) ; 

__attribute__((used)) static void __warn_no_space_for_csum(struct inode *inode, const char *func,
				     unsigned int line)
{
	__ext4_warning_inode(inode, func, line,
		"No space for directory leaf checksum. Please run e2fsck -D.");
}