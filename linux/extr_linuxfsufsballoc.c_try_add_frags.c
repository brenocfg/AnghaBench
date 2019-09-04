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
typedef  scalar_t__ u32 ;
struct inode {scalar_t__ i_blocks; int /*<<< orphan*/  i_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  __inode_add_bytes (struct inode*,unsigned int) ; 
 int /*<<< orphan*/  __inode_sub_bytes (struct inode*,unsigned int) ; 
 unsigned int i_blocksize (struct inode*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static bool try_add_frags(struct inode *inode, unsigned frags)
{
	unsigned size = frags * i_blocksize(inode);
	spin_lock(&inode->i_lock);
	__inode_add_bytes(inode, size);
	if (unlikely((u32)inode->i_blocks != inode->i_blocks)) {
		__inode_sub_bytes(inode, size);
		spin_unlock(&inode->i_lock);
		return false;
	}
	spin_unlock(&inode->i_lock);
	return true;
}