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
struct TYPE_2__ {int /*<<< orphan*/  mnt_sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  S_IFREG ; 
 int /*<<< orphan*/  inode_init_owner (struct inode*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct inode* new_inode (int /*<<< orphan*/ ) ; 
 TYPE_1__* test_mnt ; 

struct inode *btrfs_new_test_inode(void)
{
	struct inode *inode;

	inode = new_inode(test_mnt->mnt_sb);
	if (inode)
		inode_init_owner(inode, NULL, S_IFREG);

	return inode;
}