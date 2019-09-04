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
struct super_block {int dummy; } ;
struct mmp_struct {int dummy; } ;
struct buffer_head {int /*<<< orphan*/  b_end_io; scalar_t__ b_data; } ;

/* Variables and functions */
 int REQ_META ; 
 int /*<<< orphan*/  REQ_OP_WRITE ; 
 int REQ_PRIO ; 
 int REQ_SYNC ; 
 int /*<<< orphan*/  buffer_uptodate (struct buffer_head*) ; 
 int /*<<< orphan*/  end_buffer_write_sync ; 
 int /*<<< orphan*/  ext4_mmp_csum_set (struct super_block*,struct mmp_struct*) ; 
 int /*<<< orphan*/  get_bh (struct buffer_head*) ; 
 int /*<<< orphan*/  lock_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  sb_end_write (struct super_block*) ; 
 int /*<<< orphan*/  sb_start_write (struct super_block*) ; 
 int /*<<< orphan*/  submit_bh (int /*<<< orphan*/ ,int,struct buffer_head*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wait_on_buffer (struct buffer_head*) ; 

__attribute__((used)) static int write_mmp_block(struct super_block *sb, struct buffer_head *bh)
{
	struct mmp_struct *mmp = (struct mmp_struct *)(bh->b_data);

	/*
	 * We protect against freezing so that we don't create dirty buffers
	 * on frozen filesystem.
	 */
	sb_start_write(sb);
	ext4_mmp_csum_set(sb, mmp);
	lock_buffer(bh);
	bh->b_end_io = end_buffer_write_sync;
	get_bh(bh);
	submit_bh(REQ_OP_WRITE, REQ_SYNC | REQ_META | REQ_PRIO, bh);
	wait_on_buffer(bh);
	sb_end_write(sb);
	if (unlikely(!buffer_uptodate(bh)))
		return 1;

	return 0;
}