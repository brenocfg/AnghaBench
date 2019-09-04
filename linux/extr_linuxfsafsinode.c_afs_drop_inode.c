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
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 TYPE_1__* AFS_FS_I (struct inode*) ; 
 int /*<<< orphan*/  AFS_VNODE_PSEUDODIR ; 
 int /*<<< orphan*/  _enter (char*) ; 
 int generic_delete_inode (struct inode*) ; 
 int generic_drop_inode (struct inode*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int afs_drop_inode(struct inode *inode)
{
	_enter("");

	if (test_bit(AFS_VNODE_PSEUDODIR, &AFS_FS_I(inode)->flags))
		return generic_delete_inode(inode);
	else
		return generic_drop_inode(inode);
}