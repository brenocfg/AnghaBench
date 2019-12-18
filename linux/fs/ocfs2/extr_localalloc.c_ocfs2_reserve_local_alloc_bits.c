#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int u32 ;
struct ocfs2_super {unsigned int local_alloc_bits; int /*<<< orphan*/  slot_num; TYPE_3__* local_alloc_bh; int /*<<< orphan*/  sb; int /*<<< orphan*/  osb_lock; } ;
struct TYPE_4__ {int /*<<< orphan*/  i_used; int /*<<< orphan*/  i_total; } ;
struct TYPE_5__ {TYPE_1__ bitmap1; } ;
struct ocfs2_dinode {TYPE_2__ id1; int /*<<< orphan*/  i_blkno; } ;
struct ocfs2_alloc_context {scalar_t__ ac_max_block; TYPE_3__* ac_bh; int /*<<< orphan*/  ac_which; int /*<<< orphan*/  ac_alloc_slot; struct inode* ac_inode; } ;
struct inode {int dummy; } ;
struct TYPE_6__ {scalar_t__ b_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOENT ; 
 int ENOSPC ; 
 int /*<<< orphan*/  LOCAL_ALLOC_SYSTEM_INODE ; 
 int /*<<< orphan*/  OCFS2_AC_USE_LOCAL ; 
 int /*<<< orphan*/  get_bh (TYPE_3__*) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_error (int /*<<< orphan*/ ,char*,unsigned long long,scalar_t__,scalar_t__) ; 
 struct inode* ocfs2_get_system_file_inode (struct ocfs2_super*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_la_state_enabled (struct ocfs2_super*) ; 
 scalar_t__ ocfs2_local_alloc_count_bits (struct ocfs2_dinode*) ; 
 int ocfs2_local_alloc_slide_window (struct ocfs2_super*,struct inode*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_ocfs2_reserve_local_alloc_bits (unsigned long long,unsigned int,int /*<<< orphan*/ ,int) ; 

int ocfs2_reserve_local_alloc_bits(struct ocfs2_super *osb,
				   u32 bits_wanted,
				   struct ocfs2_alloc_context *ac)
{
	int status;
	struct ocfs2_dinode *alloc;
	struct inode *local_alloc_inode;
	unsigned int free_bits;

	BUG_ON(!ac);

	local_alloc_inode =
		ocfs2_get_system_file_inode(osb,
					    LOCAL_ALLOC_SYSTEM_INODE,
					    osb->slot_num);
	if (!local_alloc_inode) {
		status = -ENOENT;
		mlog_errno(status);
		goto bail;
	}

	inode_lock(local_alloc_inode);

	/*
	 * We must double check state and allocator bits because
	 * another process may have changed them while holding i_mutex.
	 */
	spin_lock(&osb->osb_lock);
	if (!ocfs2_la_state_enabled(osb) ||
	    (bits_wanted > osb->local_alloc_bits)) {
		spin_unlock(&osb->osb_lock);
		status = -ENOSPC;
		goto bail;
	}
	spin_unlock(&osb->osb_lock);

	alloc = (struct ocfs2_dinode *) osb->local_alloc_bh->b_data;

#ifdef CONFIG_OCFS2_DEBUG_FS
	if (le32_to_cpu(alloc->id1.bitmap1.i_used) !=
	    ocfs2_local_alloc_count_bits(alloc)) {
		status = ocfs2_error(osb->sb, "local alloc inode %llu says it has %u used bits, but a count shows %u\n",
				(unsigned long long)le64_to_cpu(alloc->i_blkno),
				le32_to_cpu(alloc->id1.bitmap1.i_used),
				ocfs2_local_alloc_count_bits(alloc));
		goto bail;
	}
#endif

	free_bits = le32_to_cpu(alloc->id1.bitmap1.i_total) -
		le32_to_cpu(alloc->id1.bitmap1.i_used);
	if (bits_wanted > free_bits) {
		/* uhoh, window change time. */
		status =
			ocfs2_local_alloc_slide_window(osb, local_alloc_inode);
		if (status < 0) {
			if (status != -ENOSPC)
				mlog_errno(status);
			goto bail;
		}

		/*
		 * Under certain conditions, the window slide code
		 * might have reduced the number of bits available or
		 * disabled the the local alloc entirely. Re-check
		 * here and return -ENOSPC if necessary.
		 */
		status = -ENOSPC;
		if (!ocfs2_la_state_enabled(osb))
			goto bail;

		free_bits = le32_to_cpu(alloc->id1.bitmap1.i_total) -
			le32_to_cpu(alloc->id1.bitmap1.i_used);
		if (bits_wanted > free_bits)
			goto bail;
	}

	ac->ac_inode = local_alloc_inode;
	/* We should never use localalloc from another slot */
	ac->ac_alloc_slot = osb->slot_num;
	ac->ac_which = OCFS2_AC_USE_LOCAL;
	get_bh(osb->local_alloc_bh);
	ac->ac_bh = osb->local_alloc_bh;
	status = 0;
bail:
	if (status < 0 && local_alloc_inode) {
		inode_unlock(local_alloc_inode);
		iput(local_alloc_inode);
	}

	trace_ocfs2_reserve_local_alloc_bits(
		(unsigned long long)ac->ac_max_block,
		bits_wanted, osb->slot_num, status);

	if (status)
		mlog_errno(status);
	return status;
}