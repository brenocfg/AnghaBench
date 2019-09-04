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
struct super_block {int /*<<< orphan*/  s_umount; } ;
typedef  enum wb_reason { ____Placeholder_wb_reason } wb_reason ;

/* Variables and functions */
 int /*<<< orphan*/  __writeback_inodes_sb_nr (struct super_block*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  down_read_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_nr_dirty_pages () ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

void try_to_writeback_inodes_sb(struct super_block *sb, enum wb_reason reason)
{
	if (!down_read_trylock(&sb->s_umount))
		return;

	__writeback_inodes_sb_nr(sb, get_nr_dirty_pages(), reason, true);
	up_read(&sb->s_umount);
}