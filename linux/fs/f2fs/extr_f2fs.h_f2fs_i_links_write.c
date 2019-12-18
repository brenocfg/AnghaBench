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
 int /*<<< orphan*/  drop_nlink (struct inode*) ; 
 int /*<<< orphan*/  f2fs_mark_inode_dirty_sync (struct inode*,int) ; 
 int /*<<< orphan*/  inc_nlink (struct inode*) ; 

__attribute__((used)) static inline void f2fs_i_links_write(struct inode *inode, bool inc)
{
	if (inc)
		inc_nlink(inode);
	else
		drop_nlink(inode);
	f2fs_mark_inode_dirty_sync(inode, true);
}