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
struct ocfs2_super {int max_slots; } ;
struct inode {int dummy; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EACCES ; 
 int /*<<< orphan*/  JOURNAL_SYSTEM_INODE ; 
 int /*<<< orphan*/  OCFS2_BH_IGNORE_CACHE ; 
 int /*<<< orphan*/  SET_INODE_JOURNAL (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 scalar_t__ is_bad_inode (struct inode*) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 struct inode* ocfs2_get_system_file_inode (struct ocfs2_super*,int /*<<< orphan*/ ,int) ; 
 int ocfs2_read_inode_block_full (struct inode*,struct buffer_head**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ocfs2_read_journal_inode(struct ocfs2_super *osb,
				    int slot_num,
				    struct buffer_head **bh,
				    struct inode **ret_inode)
{
	int status = -EACCES;
	struct inode *inode = NULL;

	BUG_ON(slot_num >= osb->max_slots);

	inode = ocfs2_get_system_file_inode(osb, JOURNAL_SYSTEM_INODE,
					    slot_num);
	if (!inode || is_bad_inode(inode)) {
		mlog_errno(status);
		goto bail;
	}
	SET_INODE_JOURNAL(inode);

	status = ocfs2_read_inode_block_full(inode, bh, OCFS2_BH_IGNORE_CACHE);
	if (status < 0) {
		mlog_errno(status);
		goto bail;
	}

	status = 0;

bail:
	if (inode) {
		if (status || !ret_inode)
			iput(inode);
		else
			*ret_inode = inode;
	}
	return status;
}