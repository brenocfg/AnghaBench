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
struct the_nilfs {int /*<<< orphan*/  ns_sb; int /*<<< orphan*/  ns_blocksize; int /*<<< orphan*/  ns_bdev; } ;
struct nilfs_recovery_info {int /*<<< orphan*/  ri_lsegs_start; int /*<<< orphan*/  ri_super_root; } ;
struct buffer_head {int /*<<< orphan*/  b_size; int /*<<< orphan*/  b_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 struct buffer_head* __getblk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nilfs_get_segnum_of_block (struct the_nilfs*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nilfs_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  set_buffer_dirty (struct buffer_head*) ; 
 int sync_dirty_buffer (struct buffer_head*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void nilfs_finish_roll_forward(struct the_nilfs *nilfs,
				      struct nilfs_recovery_info *ri)
{
	struct buffer_head *bh;
	int err;

	if (nilfs_get_segnum_of_block(nilfs, ri->ri_lsegs_start) !=
	    nilfs_get_segnum_of_block(nilfs, ri->ri_super_root))
		return;

	bh = __getblk(nilfs->ns_bdev, ri->ri_lsegs_start, nilfs->ns_blocksize);
	BUG_ON(!bh);
	memset(bh->b_data, 0, bh->b_size);
	set_buffer_dirty(bh);
	err = sync_dirty_buffer(bh);
	if (unlikely(err))
		nilfs_msg(nilfs->ns_sb, KERN_WARNING,
			  "buffer sync write failed during post-cleaning of recovery.");
	brelse(bh);
}