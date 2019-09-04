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
struct inode {int /*<<< orphan*/  i_ino; } ;
struct TYPE_2__ {int /*<<< orphan*/  root; } ;

/* Variables and functions */
 TYPE_1__* BTRFS_I (struct inode*) ; 
 int /*<<< orphan*/  __insert_inode_hash (struct inode*,unsigned long) ; 
 unsigned long btrfs_inode_hash (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void btrfs_insert_inode_hash(struct inode *inode)
{
	unsigned long h = btrfs_inode_hash(inode->i_ino, BTRFS_I(inode)->root);

	__insert_inode_hash(inode, h);
}