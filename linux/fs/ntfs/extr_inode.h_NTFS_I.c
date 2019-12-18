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
typedef  int /*<<< orphan*/  ntfs_inode ;

/* Variables and functions */
 int /*<<< orphan*/  big_ntfs_inode ; 
 scalar_t__ container_of (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_inode ; 

__attribute__((used)) static inline ntfs_inode *NTFS_I(struct inode *inode)
{
	return (ntfs_inode *)container_of(inode, big_ntfs_inode, vfs_inode);
}