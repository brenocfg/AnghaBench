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
typedef  int /*<<< orphan*/  ntfs_inode ;

/* Variables and functions */
 int /*<<< orphan*/  VFS_I (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  inode_init_once (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ntfs_big_inode_init_once(void *foo)
{
	ntfs_inode *ni = (ntfs_inode *)foo;

	inode_init_once(VFS_I(ni));
}