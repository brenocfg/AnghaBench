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
typedef  int u64 ;
struct TYPE_2__ {int i_blocks; } ;
struct afs_vnode {TYPE_1__ vfs_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  i_size_write (TYPE_1__*,int) ; 

__attribute__((used)) static void afs_set_i_size(struct afs_vnode *vnode, u64 size)
{
	i_size_write(&vnode->vfs_inode, size);
	vnode->vfs_inode.i_blocks = ((size + 1023) >> 10) << 1;
}