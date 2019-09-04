#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct the_nilfs {scalar_t__ ns_prot_seq; scalar_t__ ns_sbwtime; scalar_t__ ns_sbwcount; TYPE_2__* ns_bdev; struct buffer_head** ns_sbh; struct nilfs_super_block** ns_sbp; } ;
struct super_block {int dummy; } ;
struct nilfs_super_block {int /*<<< orphan*/  s_last_seq; int /*<<< orphan*/  s_wtime; int /*<<< orphan*/  s_last_cno; } ;
struct buffer_head {int dummy; } ;
struct TYPE_4__ {TYPE_1__* bd_inode; } ;
struct TYPE_3__ {int /*<<< orphan*/  i_size; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int /*<<< orphan*/  NILFS_SB2_OFFSET_BYTES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NILFS_SB_OFFSET_BYTES ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nilfs_msg (struct super_block*,int /*<<< orphan*/ ,char*,...) ; 
 struct nilfs_super_block* nilfs_read_super_block (struct super_block*,int /*<<< orphan*/ ,int,struct buffer_head**) ; 
 int /*<<< orphan*/  nilfs_release_super_block (struct the_nilfs*) ; 
 scalar_t__ nilfs_sb2_bad_offset (struct nilfs_super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nilfs_swap_super_block (struct the_nilfs*) ; 
 int nilfs_valid_sb (struct nilfs_super_block*) ; 

__attribute__((used)) static int nilfs_load_super_block(struct the_nilfs *nilfs,
				  struct super_block *sb, int blocksize,
				  struct nilfs_super_block **sbpp)
{
	struct nilfs_super_block **sbp = nilfs->ns_sbp;
	struct buffer_head **sbh = nilfs->ns_sbh;
	u64 sb2off = NILFS_SB2_OFFSET_BYTES(nilfs->ns_bdev->bd_inode->i_size);
	int valid[2], swp = 0;

	sbp[0] = nilfs_read_super_block(sb, NILFS_SB_OFFSET_BYTES, blocksize,
					&sbh[0]);
	sbp[1] = nilfs_read_super_block(sb, sb2off, blocksize, &sbh[1]);

	if (!sbp[0]) {
		if (!sbp[1]) {
			nilfs_msg(sb, KERN_ERR, "unable to read superblock");
			return -EIO;
		}
		nilfs_msg(sb, KERN_WARNING,
			  "unable to read primary superblock (blocksize = %d)",
			  blocksize);
	} else if (!sbp[1]) {
		nilfs_msg(sb, KERN_WARNING,
			  "unable to read secondary superblock (blocksize = %d)",
			  blocksize);
	}

	/*
	 * Compare two super blocks and set 1 in swp if the secondary
	 * super block is valid and newer.  Otherwise, set 0 in swp.
	 */
	valid[0] = nilfs_valid_sb(sbp[0]);
	valid[1] = nilfs_valid_sb(sbp[1]);
	swp = valid[1] && (!valid[0] ||
			   le64_to_cpu(sbp[1]->s_last_cno) >
			   le64_to_cpu(sbp[0]->s_last_cno));

	if (valid[swp] && nilfs_sb2_bad_offset(sbp[swp], sb2off)) {
		brelse(sbh[1]);
		sbh[1] = NULL;
		sbp[1] = NULL;
		valid[1] = 0;
		swp = 0;
	}
	if (!valid[swp]) {
		nilfs_release_super_block(nilfs);
		nilfs_msg(sb, KERN_ERR, "couldn't find nilfs on the device");
		return -EINVAL;
	}

	if (!valid[!swp])
		nilfs_msg(sb, KERN_WARNING,
			  "broken superblock, retrying with spare superblock (blocksize = %d)",
			  blocksize);
	if (swp)
		nilfs_swap_super_block(nilfs);

	nilfs->ns_sbwcount = 0;
	nilfs->ns_sbwtime = le64_to_cpu(sbp[0]->s_wtime);
	nilfs->ns_prot_seq = le64_to_cpu(sbp[valid[1] & !swp]->s_last_seq);
	*sbpp = sbp[0];
	return 0;
}