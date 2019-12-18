#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct ocfs2_group_desc {int /*<<< orphan*/  bg_chain; int /*<<< orphan*/  bg_bits; } ;
struct TYPE_8__ {int /*<<< orphan*/  i_used; } ;
struct TYPE_9__ {TYPE_3__ bitmap1; } ;
struct ocfs2_chain_list {TYPE_2__* cl_recs; } ;
struct TYPE_6__ {struct ocfs2_chain_list i_chain; } ;
struct ocfs2_dinode {TYPE_4__ id1; TYPE_1__ id2; } ;
struct inode {int dummy; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_10__ {scalar_t__ ip_blkno; } ;
struct TYPE_7__ {int /*<<< orphan*/  c_free; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  INODE_CACHE (struct inode*) ; 
 TYPE_5__* OCFS2_I (struct inode*) ; 
 int /*<<< orphan*/  OCFS2_IS_VALID_DINODE (struct ocfs2_dinode*) ; 
 int /*<<< orphan*/  OCFS2_JOURNAL_ACCESS_WRITE ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  cpu_to_le32 (scalar_t__) ; 
 size_t le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_add_cpu (int /*<<< orphan*/ *,unsigned int) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 unsigned int ocfs2_bits_per_group (struct ocfs2_chain_list*) ; 
 int ocfs2_block_group_clear_bits (int /*<<< orphan*/ *,struct inode*,struct ocfs2_group_desc*,struct buffer_head*,unsigned int,unsigned int,void (*) (unsigned int,unsigned long*)) ; 
 int /*<<< orphan*/  ocfs2_block_group_set_bits (int /*<<< orphan*/ *,struct inode*,struct ocfs2_group_desc*,struct buffer_head*,unsigned int,unsigned int) ; 
 int ocfs2_journal_access_di (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct buffer_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_journal_dirty (int /*<<< orphan*/ *,struct buffer_head*) ; 
 int ocfs2_read_group_descriptor (struct inode*,struct ocfs2_dinode*,scalar_t__,struct buffer_head**) ; 
 int /*<<< orphan*/  trace_ocfs2_free_suballoc_bits (unsigned long long,unsigned long long,unsigned int,unsigned int) ; 

__attribute__((used)) static int _ocfs2_free_suballoc_bits(handle_t *handle,
				     struct inode *alloc_inode,
				     struct buffer_head *alloc_bh,
				     unsigned int start_bit,
				     u64 bg_blkno,
				     unsigned int count,
				     void (*undo_fn)(unsigned int bit,
						     unsigned long *bitmap))
{
	int status = 0;
	u32 tmp_used;
	struct ocfs2_dinode *fe = (struct ocfs2_dinode *) alloc_bh->b_data;
	struct ocfs2_chain_list *cl = &fe->id2.i_chain;
	struct buffer_head *group_bh = NULL;
	struct ocfs2_group_desc *group;

	/* The alloc_bh comes from ocfs2_free_dinode() or
	 * ocfs2_free_clusters().  The callers have all locked the
	 * allocator and gotten alloc_bh from the lock call.  This
	 * validates the dinode buffer.  Any corruption that has happened
	 * is a code bug. */
	BUG_ON(!OCFS2_IS_VALID_DINODE(fe));
	BUG_ON((count + start_bit) > ocfs2_bits_per_group(cl));

	trace_ocfs2_free_suballoc_bits(
		(unsigned long long)OCFS2_I(alloc_inode)->ip_blkno,
		(unsigned long long)bg_blkno,
		start_bit, count);

	status = ocfs2_read_group_descriptor(alloc_inode, fe, bg_blkno,
					     &group_bh);
	if (status < 0) {
		mlog_errno(status);
		goto bail;
	}
	group = (struct ocfs2_group_desc *) group_bh->b_data;

	BUG_ON((count + start_bit) > le16_to_cpu(group->bg_bits));

	status = ocfs2_block_group_clear_bits(handle, alloc_inode,
					      group, group_bh,
					      start_bit, count, undo_fn);
	if (status < 0) {
		mlog_errno(status);
		goto bail;
	}

	status = ocfs2_journal_access_di(handle, INODE_CACHE(alloc_inode),
					 alloc_bh, OCFS2_JOURNAL_ACCESS_WRITE);
	if (status < 0) {
		mlog_errno(status);
		ocfs2_block_group_set_bits(handle, alloc_inode, group, group_bh,
				start_bit, count);
		goto bail;
	}

	le32_add_cpu(&cl->cl_recs[le16_to_cpu(group->bg_chain)].c_free,
		     count);
	tmp_used = le32_to_cpu(fe->id1.bitmap1.i_used);
	fe->id1.bitmap1.i_used = cpu_to_le32(tmp_used - count);
	ocfs2_journal_dirty(handle, alloc_bh);

bail:
	brelse(group_bh);

	if (status)
		mlog_errno(status);
	return status;
}