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
struct mmp_struct {int /*<<< orphan*/  mmp_magic; } ;
struct buffer_head {scalar_t__ b_data; int /*<<< orphan*/  b_end_io; } ;
typedef  int /*<<< orphan*/  ext4_fsblk_t ;

/* Variables and functions */
 int EFSBADCRC ; 
 int EFSCORRUPTED ; 
 int EIO ; 
 int ENOMEM ; 
 scalar_t__ EXT4_MMP_MAGIC ; 
 int REQ_META ; 
 int /*<<< orphan*/  REQ_OP_READ ; 
 int REQ_PRIO ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  buffer_uptodate (struct buffer_head*) ; 
 int /*<<< orphan*/  clear_buffer_uptodate (struct buffer_head*) ; 
 int /*<<< orphan*/  end_buffer_read_sync ; 
 int /*<<< orphan*/  ext4_mmp_csum_verify (struct super_block*,struct mmp_struct*) ; 
 int /*<<< orphan*/  ext4_warning (struct super_block*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_bh (struct buffer_head*) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_buffer (struct buffer_head*) ; 
 struct buffer_head* sb_getblk (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  submit_bh (int /*<<< orphan*/ ,int,struct buffer_head*) ; 
 int /*<<< orphan*/  wait_on_buffer (struct buffer_head*) ; 

__attribute__((used)) static int read_mmp_block(struct super_block *sb, struct buffer_head **bh,
			  ext4_fsblk_t mmp_block)
{
	struct mmp_struct *mmp;
	int ret;

	if (*bh)
		clear_buffer_uptodate(*bh);

	/* This would be sb_bread(sb, mmp_block), except we need to be sure
	 * that the MD RAID device cache has been bypassed, and that the read
	 * is not blocked in the elevator. */
	if (!*bh) {
		*bh = sb_getblk(sb, mmp_block);
		if (!*bh) {
			ret = -ENOMEM;
			goto warn_exit;
		}
	}

	get_bh(*bh);
	lock_buffer(*bh);
	(*bh)->b_end_io = end_buffer_read_sync;
	submit_bh(REQ_OP_READ, REQ_META | REQ_PRIO, *bh);
	wait_on_buffer(*bh);
	if (!buffer_uptodate(*bh)) {
		ret = -EIO;
		goto warn_exit;
	}
	mmp = (struct mmp_struct *)((*bh)->b_data);
	if (le32_to_cpu(mmp->mmp_magic) != EXT4_MMP_MAGIC) {
		ret = -EFSCORRUPTED;
		goto warn_exit;
	}
	if (!ext4_mmp_csum_verify(sb, mmp)) {
		ret = -EFSBADCRC;
		goto warn_exit;
	}
	return 0;
warn_exit:
	brelse(*bh);
	*bh = NULL;
	ext4_warning(sb, "Error %d while reading MMP block %llu",
		     ret, mmp_block);
	return ret;
}