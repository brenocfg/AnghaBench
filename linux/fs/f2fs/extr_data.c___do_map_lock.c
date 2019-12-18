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
struct f2fs_sb_info {int /*<<< orphan*/  node_change; } ;

/* Variables and functions */
 int F2FS_GET_BLOCK_PRE_AIO ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  f2fs_lock_op (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  f2fs_unlock_op (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

void __do_map_lock(struct f2fs_sb_info *sbi, int flag, bool lock)
{
	if (flag == F2FS_GET_BLOCK_PRE_AIO) {
		if (lock)
			down_read(&sbi->node_change);
		else
			up_read(&sbi->node_change);
	} else {
		if (lock)
			f2fs_lock_op(sbi);
		else
			f2fs_unlock_op(sbi);
	}
}