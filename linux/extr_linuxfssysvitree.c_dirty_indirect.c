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
struct buffer_head {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_SYNC (struct inode*) ; 
 int /*<<< orphan*/  mark_buffer_dirty_inode (struct buffer_head*,struct inode*) ; 
 int /*<<< orphan*/  sync_dirty_buffer (struct buffer_head*) ; 

__attribute__((used)) static inline void dirty_indirect(struct buffer_head *bh, struct inode *inode)
{
	mark_buffer_dirty_inode(bh, inode);
	if (IS_SYNC(inode))
		sync_dirty_buffer(bh);
}