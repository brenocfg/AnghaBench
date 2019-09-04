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

/* Variables and functions */
 int /*<<< orphan*/  I_DIRTY_SYNC ; 
 int __nilfs_mark_inode_dirty (struct inode*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int nilfs_mark_inode_dirty_sync(struct inode *inode)
{
	return __nilfs_mark_inode_dirty(inode, I_DIRTY_SYNC);
}