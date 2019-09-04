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
struct the_nilfs {scalar_t__ ns_blocksize_bits; scalar_t__ ns_nsegments; int /*<<< orphan*/  ns_sufile; int /*<<< orphan*/  ns_sem; int /*<<< orphan*/  ns_sbsize; int /*<<< orphan*/  ns_segctor_sem; int /*<<< orphan*/  ns_blocks_per_segment; } ;
struct super_block {TYPE_1__* s_bdev; struct the_nilfs* s_fs_info; } ;
struct nilfs_super_block {void* s_nsegments; void* s_dev_size; int /*<<< orphan*/  s_state; } ;
typedef  scalar_t__ loff_t ;
typedef  scalar_t__ __u64 ;
struct TYPE_2__ {int /*<<< orphan*/  bd_inode; } ;

/* Variables and functions */
 int EIO ; 
 int ERANGE ; 
 int NILFS_RESIZE_FS ; 
 scalar_t__ NILFS_SB2_OFFSET_BYTES (scalar_t__) ; 
 int /*<<< orphan*/  NILFS_SB_COMMIT_ALL ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 void* cpu_to_le64 (scalar_t__) ; 
 int /*<<< orphan*/  do_div (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 scalar_t__ i_size_read (int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (struct nilfs_super_block**) ; 
 int /*<<< orphan*/  memcpy (struct nilfs_super_block*,struct nilfs_super_block*,int /*<<< orphan*/ ) ; 
 int nilfs_commit_super (struct super_block*,int /*<<< orphan*/ ) ; 
 int nilfs_construct_segment (struct super_block*) ; 
 int /*<<< orphan*/  nilfs_move_2nd_super (struct super_block*,scalar_t__) ; 
 struct nilfs_super_block** nilfs_prepare_super (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nilfs_set_log_cursor (struct nilfs_super_block*,struct the_nilfs*) ; 
 int nilfs_sufile_resize (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  nilfs_sufile_set_alloc_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int nilfs_resize_fs(struct super_block *sb, __u64 newsize)
{
	struct the_nilfs *nilfs = sb->s_fs_info;
	struct nilfs_super_block **sbp;
	__u64 devsize, newnsegs;
	loff_t sb2off;
	int ret;

	ret = -ERANGE;
	devsize = i_size_read(sb->s_bdev->bd_inode);
	if (newsize > devsize)
		goto out;

	/*
	 * Write lock is required to protect some functions depending
	 * on the number of segments, the number of reserved segments,
	 * and so forth.
	 */
	down_write(&nilfs->ns_segctor_sem);

	sb2off = NILFS_SB2_OFFSET_BYTES(newsize);
	newnsegs = sb2off >> nilfs->ns_blocksize_bits;
	do_div(newnsegs, nilfs->ns_blocks_per_segment);

	ret = nilfs_sufile_resize(nilfs->ns_sufile, newnsegs);
	up_write(&nilfs->ns_segctor_sem);
	if (ret < 0)
		goto out;

	ret = nilfs_construct_segment(sb);
	if (ret < 0)
		goto out;

	down_write(&nilfs->ns_sem);
	nilfs_move_2nd_super(sb, sb2off);
	ret = -EIO;
	sbp = nilfs_prepare_super(sb, 0);
	if (likely(sbp)) {
		nilfs_set_log_cursor(sbp[0], nilfs);
		/*
		 * Drop NILFS_RESIZE_FS flag for compatibility with
		 * mount-time resize which may be implemented in a
		 * future release.
		 */
		sbp[0]->s_state = cpu_to_le16(le16_to_cpu(sbp[0]->s_state) &
					      ~NILFS_RESIZE_FS);
		sbp[0]->s_dev_size = cpu_to_le64(newsize);
		sbp[0]->s_nsegments = cpu_to_le64(nilfs->ns_nsegments);
		if (sbp[1])
			memcpy(sbp[1], sbp[0], nilfs->ns_sbsize);
		ret = nilfs_commit_super(sb, NILFS_SB_COMMIT_ALL);
	}
	up_write(&nilfs->ns_sem);

	/*
	 * Reset the range of allocatable segments last.  This order
	 * is important in the case of expansion because the secondary
	 * superblock must be protected from log write until migration
	 * completes.
	 */
	if (!ret)
		nilfs_sufile_set_alloc_range(nilfs->ns_sufile, 0, newnsegs - 1);
out:
	return ret;
}