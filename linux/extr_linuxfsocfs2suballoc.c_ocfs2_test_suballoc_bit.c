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
typedef  scalar_t__ u16 ;
struct ocfs2_super {int dummy; } ;
struct ocfs2_group_desc {scalar_t__ bg_bitmap; } ;
struct TYPE_2__ {int /*<<< orphan*/  i_chain; } ;
struct ocfs2_dinode {TYPE_1__ id2; } ;
struct inode {int dummy; } ;
struct buffer_head {scalar_t__ b_data; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ML_ERROR ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,unsigned long long,int) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_bits_per_group (int /*<<< orphan*/ *) ; 
 int ocfs2_read_group_descriptor (struct inode*,struct ocfs2_dinode*,scalar_t__,struct buffer_head**) ; 
 int ocfs2_test_bit (scalar_t__,unsigned long*) ; 
 scalar_t__ ocfs2_which_suballoc_group (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  trace_ocfs2_test_suballoc_bit (unsigned long long,unsigned int) ; 

__attribute__((used)) static int ocfs2_test_suballoc_bit(struct ocfs2_super *osb,
				   struct inode *suballoc,
				   struct buffer_head *alloc_bh,
				   u64 group_blkno, u64 blkno,
				   u16 bit, int *res)
{
	struct ocfs2_dinode *alloc_di;
	struct ocfs2_group_desc *group;
	struct buffer_head *group_bh = NULL;
	u64 bg_blkno;
	int status;

	trace_ocfs2_test_suballoc_bit((unsigned long long)blkno,
				      (unsigned int)bit);

	alloc_di = (struct ocfs2_dinode *)alloc_bh->b_data;
	if ((bit + 1) > ocfs2_bits_per_group(&alloc_di->id2.i_chain)) {
		mlog(ML_ERROR, "suballoc bit %u out of range of %u\n",
		     (unsigned int)bit,
		     ocfs2_bits_per_group(&alloc_di->id2.i_chain));
		status = -EINVAL;
		goto bail;
	}

	bg_blkno = group_blkno ? group_blkno :
		   ocfs2_which_suballoc_group(blkno, bit);
	status = ocfs2_read_group_descriptor(suballoc, alloc_di, bg_blkno,
					     &group_bh);
	if (status < 0) {
		mlog(ML_ERROR, "read group %llu failed %d\n",
		     (unsigned long long)bg_blkno, status);
		goto bail;
	}

	group = (struct ocfs2_group_desc *) group_bh->b_data;
	*res = ocfs2_test_bit(bit, (unsigned long *)group->bg_bitmap);

bail:
	brelse(group_bh);

	if (status)
		mlog_errno(status);
	return status;
}