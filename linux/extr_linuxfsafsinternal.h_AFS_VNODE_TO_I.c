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
struct afs_vnode {struct inode vfs_inode; } ;

/* Variables and functions */

__attribute__((used)) static inline struct inode *AFS_VNODE_TO_I(struct afs_vnode *vnode)
{
	return &vnode->vfs_inode;
}