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
struct afs_vnode {int /*<<< orphan*/  vfs_inode; } ;
struct afs_net {int dummy; } ;

/* Variables and functions */
 struct afs_net* afs_i2net (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline struct afs_net *afs_v2net(struct afs_vnode *vnode)
{
	return afs_i2net(&vnode->vfs_inode);
}