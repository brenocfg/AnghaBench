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
typedef  scalar_t__ u64 ;
struct super_block {int dummy; } ;
struct inode {struct super_block* i_sb; } ;
struct buffer_head {int dummy; } ;
typedef  scalar_t__ loff_t ;
struct TYPE_2__ {scalar_t__ ip_blkno; } ;

/* Variables and functions */
 TYPE_1__* OCFS2_I (struct inode*) ; 
 scalar_t__ i_size_read (struct inode*) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 scalar_t__ ocfs2_align_bytes_to_blocks (struct super_block*,scalar_t__) ; 
 int ocfs2_zero_extend_get_range (struct inode*,struct buffer_head*,scalar_t__,scalar_t__,scalar_t__*,scalar_t__*) ; 
 int ocfs2_zero_extend_range (struct inode*,scalar_t__,scalar_t__,struct buffer_head*) ; 
 int /*<<< orphan*/  trace_ocfs2_zero_extend (unsigned long long,unsigned long long,unsigned long long) ; 

int ocfs2_zero_extend(struct inode *inode, struct buffer_head *di_bh,
		      loff_t zero_to_size)
{
	int ret = 0;
	u64 zero_start, range_start = 0, range_end = 0;
	struct super_block *sb = inode->i_sb;

	zero_start = ocfs2_align_bytes_to_blocks(sb, i_size_read(inode));
	trace_ocfs2_zero_extend((unsigned long long)OCFS2_I(inode)->ip_blkno,
				(unsigned long long)zero_start,
				(unsigned long long)i_size_read(inode));
	while (zero_start < zero_to_size) {
		ret = ocfs2_zero_extend_get_range(inode, di_bh, zero_start,
						  zero_to_size,
						  &range_start,
						  &range_end);
		if (ret) {
			mlog_errno(ret);
			break;
		}
		if (!range_end)
			break;
		/* Trim the ends */
		if (range_start < zero_start)
			range_start = zero_start;
		if (range_end > zero_to_size)
			range_end = zero_to_size;

		ret = ocfs2_zero_extend_range(inode, range_start,
					      range_end, di_bh);
		if (ret) {
			mlog_errno(ret);
			break;
		}
		zero_start = range_end;
	}

	return ret;
}