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
struct nilfs_sufile_info {int allocmax; int allocmin; int /*<<< orphan*/  ncleansegs; } ;
struct nilfs_sufile_header {int /*<<< orphan*/  sh_last_alloc; int /*<<< orphan*/  sh_ndirtysegs; int /*<<< orphan*/  sh_ncleansegs; } ;
struct nilfs_segment_usage {int dummy; } ;
struct inode {int dummy; } ;
struct buffer_head {int /*<<< orphan*/  b_page; } ;
typedef  int __u64 ;
struct TYPE_2__ {size_t mi_entry_size; int /*<<< orphan*/  mi_sem; } ;

/* Variables and functions */
 int ENOSPC ; 
 TYPE_1__* NILFS_MDT (struct inode*) ; 
 struct nilfs_sufile_info* NILFS_SUI (struct inode*) ; 
 int bh_offset (struct buffer_head*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  cpu_to_le64 (int) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 void* kmap_atomic (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap_atomic (void*) ; 
 int /*<<< orphan*/  le64_add_cpu (int /*<<< orphan*/ *,int) ; 
 int le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mark_buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  nilfs_mdt_mark_dirty (struct inode*) ; 
 int /*<<< orphan*/  nilfs_segment_usage_clean (struct nilfs_segment_usage*) ; 
 int /*<<< orphan*/  nilfs_segment_usage_set_dirty (struct nilfs_segment_usage*) ; 
 struct nilfs_segment_usage* nilfs_sufile_block_get_segment_usage (struct inode*,int,struct buffer_head*,void*) ; 
 int nilfs_sufile_get_header_block (struct inode*,struct buffer_head**) ; 
 unsigned long nilfs_sufile_get_nsegments (struct inode*) ; 
 int nilfs_sufile_get_segment_usage_block (struct inode*,int,int,struct buffer_head**) ; 
 unsigned long nilfs_sufile_segment_usages_in_block (struct inode*,int,int) ; 
 int /*<<< orphan*/  trace_nilfs2_segment_usage_allocated (struct inode*,int) ; 
 int /*<<< orphan*/  trace_nilfs2_segment_usage_check (struct inode*,int,unsigned long) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int nilfs_sufile_alloc(struct inode *sufile, __u64 *segnump)
{
	struct buffer_head *header_bh, *su_bh;
	struct nilfs_sufile_header *header;
	struct nilfs_segment_usage *su;
	struct nilfs_sufile_info *sui = NILFS_SUI(sufile);
	size_t susz = NILFS_MDT(sufile)->mi_entry_size;
	__u64 segnum, maxsegnum, last_alloc;
	void *kaddr;
	unsigned long nsegments, nsus, cnt;
	int ret, j;

	down_write(&NILFS_MDT(sufile)->mi_sem);

	ret = nilfs_sufile_get_header_block(sufile, &header_bh);
	if (ret < 0)
		goto out_sem;
	kaddr = kmap_atomic(header_bh->b_page);
	header = kaddr + bh_offset(header_bh);
	last_alloc = le64_to_cpu(header->sh_last_alloc);
	kunmap_atomic(kaddr);

	nsegments = nilfs_sufile_get_nsegments(sufile);
	maxsegnum = sui->allocmax;
	segnum = last_alloc + 1;
	if (segnum < sui->allocmin || segnum > sui->allocmax)
		segnum = sui->allocmin;

	for (cnt = 0; cnt < nsegments; cnt += nsus) {
		if (segnum > maxsegnum) {
			if (cnt < sui->allocmax - sui->allocmin + 1) {
				/*
				 * wrap around in the limited region.
				 * if allocation started from
				 * sui->allocmin, this never happens.
				 */
				segnum = sui->allocmin;
				maxsegnum = last_alloc;
			} else if (segnum > sui->allocmin &&
				   sui->allocmax + 1 < nsegments) {
				segnum = sui->allocmax + 1;
				maxsegnum = nsegments - 1;
			} else if (sui->allocmin > 0)  {
				segnum = 0;
				maxsegnum = sui->allocmin - 1;
			} else {
				break; /* never happens */
			}
		}
		trace_nilfs2_segment_usage_check(sufile, segnum, cnt);
		ret = nilfs_sufile_get_segment_usage_block(sufile, segnum, 1,
							   &su_bh);
		if (ret < 0)
			goto out_header;
		kaddr = kmap_atomic(su_bh->b_page);
		su = nilfs_sufile_block_get_segment_usage(
			sufile, segnum, su_bh, kaddr);

		nsus = nilfs_sufile_segment_usages_in_block(
			sufile, segnum, maxsegnum);
		for (j = 0; j < nsus; j++, su = (void *)su + susz, segnum++) {
			if (!nilfs_segment_usage_clean(su))
				continue;
			/* found a clean segment */
			nilfs_segment_usage_set_dirty(su);
			kunmap_atomic(kaddr);

			kaddr = kmap_atomic(header_bh->b_page);
			header = kaddr + bh_offset(header_bh);
			le64_add_cpu(&header->sh_ncleansegs, -1);
			le64_add_cpu(&header->sh_ndirtysegs, 1);
			header->sh_last_alloc = cpu_to_le64(segnum);
			kunmap_atomic(kaddr);

			sui->ncleansegs--;
			mark_buffer_dirty(header_bh);
			mark_buffer_dirty(su_bh);
			nilfs_mdt_mark_dirty(sufile);
			brelse(su_bh);
			*segnump = segnum;

			trace_nilfs2_segment_usage_allocated(sufile, segnum);

			goto out_header;
		}

		kunmap_atomic(kaddr);
		brelse(su_bh);
	}

	/* no segments left */
	ret = -ENOSPC;

 out_header:
	brelse(header_bh);

 out_sem:
	up_write(&NILFS_MDT(sufile)->mi_sem);
	return ret;
}