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
struct super_block {int dummy; } ;
struct ext2_super_block {void* s_wtime; void* s_free_inodes_count; void* s_free_blocks_count; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_sbh; int /*<<< orphan*/  s_lock; } ;

/* Variables and functions */
 TYPE_1__* EXT2_SB (struct super_block*) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext2_clear_super_error (struct super_block*) ; 
 int /*<<< orphan*/  ext2_count_free_blocks (struct super_block*) ; 
 int /*<<< orphan*/  ext2_count_free_inodes (struct super_block*) ; 
 int /*<<< orphan*/  ktime_get_real_seconds () ; 
 int /*<<< orphan*/  mark_buffer_dirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sync_dirty_buffer (int /*<<< orphan*/ ) ; 

void ext2_sync_super(struct super_block *sb, struct ext2_super_block *es,
		     int wait)
{
	ext2_clear_super_error(sb);
	spin_lock(&EXT2_SB(sb)->s_lock);
	es->s_free_blocks_count = cpu_to_le32(ext2_count_free_blocks(sb));
	es->s_free_inodes_count = cpu_to_le32(ext2_count_free_inodes(sb));
	es->s_wtime = cpu_to_le32(ktime_get_real_seconds());
	/* unlock before we do IO */
	spin_unlock(&EXT2_SB(sb)->s_lock);
	mark_buffer_dirty(EXT2_SB(sb)->s_sbh);
	if (wait)
		sync_dirty_buffer(EXT2_SB(sb)->s_sbh);
}