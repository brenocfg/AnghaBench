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
typedef  int /*<<< orphan*/  ntfs_inode ;
struct TYPE_2__ {struct inode vfs_inode; } ;
typedef  TYPE_1__ big_ntfs_inode ;

/* Variables and functions */

__attribute__((used)) static inline struct inode *VFS_I(ntfs_inode *ni)
{
	return &((big_ntfs_inode *)ni)->vfs_inode;
}