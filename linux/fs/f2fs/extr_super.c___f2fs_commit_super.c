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
struct f2fs_super_block {int dummy; } ;
struct buffer_head {scalar_t__ b_data; } ;

/* Variables and functions */
 scalar_t__ F2FS_SUPER_OFFSET ; 
 int REQ_FUA ; 
 int REQ_PREFLUSH ; 
 int REQ_SYNC ; 
 int __sync_dirty_buffer (struct buffer_head*,int) ; 
 int /*<<< orphan*/  lock_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,struct f2fs_super_block*,int) ; 
 int /*<<< orphan*/  set_buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  unlock_buffer (struct buffer_head*) ; 

__attribute__((used)) static int __f2fs_commit_super(struct buffer_head *bh,
			struct f2fs_super_block *super)
{
	lock_buffer(bh);
	if (super)
		memcpy(bh->b_data + F2FS_SUPER_OFFSET, super, sizeof(*super));
	set_buffer_dirty(bh);
	unlock_buffer(bh);

	/* it's rare case, we can do fua all the time */
	return __sync_dirty_buffer(bh, REQ_SYNC | REQ_PREFLUSH | REQ_FUA);
}