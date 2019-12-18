#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct super_block {int s_flags; TYPE_1__* s_bdev; } ;
struct ext4_super_block {int /*<<< orphan*/  s_free_inodes_count; void* s_kbytes_written; } ;
struct buffer_head {int dummy; } ;
struct TYPE_5__ {int s_sectors_written_start; int /*<<< orphan*/  s_freeinodes_counter; int /*<<< orphan*/  s_freeclusters_counter; scalar_t__ s_kbytes_written; struct buffer_head* s_sbh; struct ext4_super_block* s_es; } ;
struct TYPE_4__ {scalar_t__ bd_part; } ;

/* Variables and functions */
 int /*<<< orphan*/  BARRIER ; 
 int /*<<< orphan*/  BUFFER_TRACE (struct buffer_head*,char*) ; 
 int /*<<< orphan*/  EXT4_C2B (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* EXT4_SB (struct super_block*) ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int REQ_FUA ; 
 int REQ_SYNC ; 
 int SB_RDONLY ; 
 size_t STAT_WRITE ; 
 int __sync_dirty_buffer (struct buffer_head*,int) ; 
 scalar_t__ block_device_ejected (struct super_block*) ; 
 int /*<<< orphan*/  buffer_mapped (struct buffer_head*) ; 
 int /*<<< orphan*/  buffer_uptodate (struct buffer_head*) ; 
 scalar_t__ buffer_write_io_error (struct buffer_head*) ; 
 int /*<<< orphan*/  clear_buffer_write_io_error (struct buffer_head*) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 void* cpu_to_le64 (scalar_t__) ; 
 int /*<<< orphan*/  ext4_free_blocks_count_set (struct ext4_super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_msg (struct super_block*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ext4_superblock_csum_set (struct super_block*) ; 
 int /*<<< orphan*/  ext4_update_tstamp (struct ext4_super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  mark_buffer_dirty (struct buffer_head*) ; 
 int part_stat_read (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ percpu_counter_initialized (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  percpu_counter_sum_positive (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  s_wtime ; 
 int /*<<< orphan*/ * sectors ; 
 int /*<<< orphan*/  set_buffer_uptodate (struct buffer_head*) ; 
 scalar_t__ test_opt (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_buffer (struct buffer_head*) ; 

__attribute__((used)) static int ext4_commit_super(struct super_block *sb, int sync)
{
	struct ext4_super_block *es = EXT4_SB(sb)->s_es;
	struct buffer_head *sbh = EXT4_SB(sb)->s_sbh;
	int error = 0;

	if (!sbh || block_device_ejected(sb))
		return error;

	/*
	 * The superblock bh should be mapped, but it might not be if the
	 * device was hot-removed. Not much we can do but fail the I/O.
	 */
	if (!buffer_mapped(sbh))
		return error;

	/*
	 * If the file system is mounted read-only, don't update the
	 * superblock write time.  This avoids updating the superblock
	 * write time when we are mounting the root file system
	 * read/only but we need to replay the journal; at that point,
	 * for people who are east of GMT and who make their clock
	 * tick in localtime for Windows bug-for-bug compatibility,
	 * the clock is set in the future, and this will cause e2fsck
	 * to complain and force a full file system check.
	 */
	if (!(sb->s_flags & SB_RDONLY))
		ext4_update_tstamp(es, s_wtime);
	if (sb->s_bdev->bd_part)
		es->s_kbytes_written =
			cpu_to_le64(EXT4_SB(sb)->s_kbytes_written +
			    ((part_stat_read(sb->s_bdev->bd_part,
					     sectors[STAT_WRITE]) -
			      EXT4_SB(sb)->s_sectors_written_start) >> 1));
	else
		es->s_kbytes_written =
			cpu_to_le64(EXT4_SB(sb)->s_kbytes_written);
	if (percpu_counter_initialized(&EXT4_SB(sb)->s_freeclusters_counter))
		ext4_free_blocks_count_set(es,
			EXT4_C2B(EXT4_SB(sb), percpu_counter_sum_positive(
				&EXT4_SB(sb)->s_freeclusters_counter)));
	if (percpu_counter_initialized(&EXT4_SB(sb)->s_freeinodes_counter))
		es->s_free_inodes_count =
			cpu_to_le32(percpu_counter_sum_positive(
				&EXT4_SB(sb)->s_freeinodes_counter));
	BUFFER_TRACE(sbh, "marking dirty");
	ext4_superblock_csum_set(sb);
	if (sync)
		lock_buffer(sbh);
	if (buffer_write_io_error(sbh) || !buffer_uptodate(sbh)) {
		/*
		 * Oh, dear.  A previous attempt to write the
		 * superblock failed.  This could happen because the
		 * USB device was yanked out.  Or it could happen to
		 * be a transient write error and maybe the block will
		 * be remapped.  Nothing we can do but to retry the
		 * write and hope for the best.
		 */
		ext4_msg(sb, KERN_ERR, "previous I/O error to "
		       "superblock detected");
		clear_buffer_write_io_error(sbh);
		set_buffer_uptodate(sbh);
	}
	mark_buffer_dirty(sbh);
	if (sync) {
		unlock_buffer(sbh);
		error = __sync_dirty_buffer(sbh,
			REQ_SYNC | (test_opt(sb, BARRIER) ? REQ_FUA : 0));
		if (buffer_write_io_error(sbh)) {
			ext4_msg(sb, KERN_ERR, "I/O error while writing "
			       "superblock");
			clear_buffer_write_io_error(sbh);
			set_buffer_uptodate(sbh);
		}
	}
	return error;
}