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
typedef  scalar_t__ time64_t ;
struct nilfs_segment_usage {int /*<<< orphan*/  su_nblocks; int /*<<< orphan*/  su_lastmod; } ;
struct inode {int dummy; } ;
struct buffer_head {int /*<<< orphan*/  b_page; } ;
typedef  int /*<<< orphan*/  __u64 ;
struct TYPE_2__ {int /*<<< orphan*/  mi_sem; } ;

/* Variables and functions */
 TYPE_1__* NILFS_MDT (struct inode*) ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  cpu_to_le32 (unsigned long) ; 
 int /*<<< orphan*/  cpu_to_le64 (scalar_t__) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 void* kmap_atomic (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap_atomic (void*) ; 
 int /*<<< orphan*/  mark_buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  nilfs_mdt_mark_dirty (struct inode*) ; 
 int /*<<< orphan*/  nilfs_segment_usage_error (struct nilfs_segment_usage*) ; 
 struct nilfs_segment_usage* nilfs_sufile_block_get_segment_usage (struct inode*,int /*<<< orphan*/ ,struct buffer_head*,void*) ; 
 int nilfs_sufile_get_segment_usage_block (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct buffer_head**) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int nilfs_sufile_set_segment_usage(struct inode *sufile, __u64 segnum,
				   unsigned long nblocks, time64_t modtime)
{
	struct buffer_head *bh;
	struct nilfs_segment_usage *su;
	void *kaddr;
	int ret;

	down_write(&NILFS_MDT(sufile)->mi_sem);
	ret = nilfs_sufile_get_segment_usage_block(sufile, segnum, 0, &bh);
	if (ret < 0)
		goto out_sem;

	kaddr = kmap_atomic(bh->b_page);
	su = nilfs_sufile_block_get_segment_usage(sufile, segnum, bh, kaddr);
	WARN_ON(nilfs_segment_usage_error(su));
	if (modtime)
		su->su_lastmod = cpu_to_le64(modtime);
	su->su_nblocks = cpu_to_le32(nblocks);
	kunmap_atomic(kaddr);

	mark_buffer_dirty(bh);
	nilfs_mdt_mark_dirty(sufile);
	brelse(bh);

 out_sem:
	up_write(&NILFS_MDT(sufile)->mi_sem);
	return ret;
}