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
struct ocfs2_super {int /*<<< orphan*/  sb; } ;
struct ocfs2_dinode {int /*<<< orphan*/  i_check; } ;
struct inode {int dummy; } ;
struct buffer_head {scalar_t__ b_data; int /*<<< orphan*/  b_size; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INODE_CACHE (struct inode*) ; 
 int /*<<< orphan*/  LOCAL_ALLOC_SYSTEM_INODE ; 
 int /*<<< orphan*/  OCFS2_BH_IGNORE_CACHE ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  kfree (struct ocfs2_dinode*) ; 
 struct ocfs2_dinode* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct ocfs2_dinode*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  ocfs2_clear_local_alloc (struct ocfs2_dinode*) ; 
 int /*<<< orphan*/  ocfs2_compute_meta_ecc (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 struct inode* ocfs2_get_system_file_inode (struct ocfs2_super*,int /*<<< orphan*/ ,int) ; 
 int ocfs2_read_inode_block_full (struct inode*,struct buffer_head**,int /*<<< orphan*/ ) ; 
 int ocfs2_write_block (struct ocfs2_super*,struct buffer_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_ocfs2_begin_local_alloc_recovery (int) ; 

int ocfs2_begin_local_alloc_recovery(struct ocfs2_super *osb,
				     int slot_num,
				     struct ocfs2_dinode **alloc_copy)
{
	int status = 0;
	struct buffer_head *alloc_bh = NULL;
	struct inode *inode = NULL;
	struct ocfs2_dinode *alloc;

	trace_ocfs2_begin_local_alloc_recovery(slot_num);

	*alloc_copy = NULL;

	inode = ocfs2_get_system_file_inode(osb,
					    LOCAL_ALLOC_SYSTEM_INODE,
					    slot_num);
	if (!inode) {
		status = -EINVAL;
		mlog_errno(status);
		goto bail;
	}

	inode_lock(inode);

	status = ocfs2_read_inode_block_full(inode, &alloc_bh,
					     OCFS2_BH_IGNORE_CACHE);
	if (status < 0) {
		mlog_errno(status);
		goto bail;
	}

	*alloc_copy = kmalloc(alloc_bh->b_size, GFP_KERNEL);
	if (!(*alloc_copy)) {
		status = -ENOMEM;
		goto bail;
	}
	memcpy((*alloc_copy), alloc_bh->b_data, alloc_bh->b_size);

	alloc = (struct ocfs2_dinode *) alloc_bh->b_data;
	ocfs2_clear_local_alloc(alloc);

	ocfs2_compute_meta_ecc(osb->sb, alloc_bh->b_data, &alloc->i_check);
	status = ocfs2_write_block(osb, alloc_bh, INODE_CACHE(inode));
	if (status < 0)
		mlog_errno(status);

bail:
	if (status < 0) {
		kfree(*alloc_copy);
		*alloc_copy = NULL;
	}

	brelse(alloc_bh);

	if (inode) {
		inode_unlock(inode);
		iput(inode);
	}

	if (status)
		mlog_errno(status);
	return status;
}