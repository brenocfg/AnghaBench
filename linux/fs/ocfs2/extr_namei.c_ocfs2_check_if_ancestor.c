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
struct ocfs2_super {TYPE_1__* root_inode; } ;
struct inode {int dummy; } ;
struct TYPE_2__ {scalar_t__ i_ino; } ;

/* Variables and functions */
 int ENOENT ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 int MAX_LOOKUP_TIMES ; 
 int /*<<< orphan*/  ML_NOTICE ; 
 int PTR_ERR (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,unsigned long long,unsigned long long) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 struct inode* ocfs2_iget (struct ocfs2_super*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ocfs2_inode_lock (struct inode*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_inode_unlock (struct inode*,int /*<<< orphan*/ ) ; 
 int ocfs2_lookup_ino_from_name (struct inode*,char*,int,scalar_t__*) ; 

__attribute__((used)) static int ocfs2_check_if_ancestor(struct ocfs2_super *osb,
		u64 src_inode_no, u64 dest_inode_no)
{
	int ret = 0, i = 0;
	u64 parent_inode_no = 0;
	u64 child_inode_no = src_inode_no;
	struct inode *child_inode;

#define MAX_LOOKUP_TIMES 32
	while (1) {
		child_inode = ocfs2_iget(osb, child_inode_no, 0, 0);
		if (IS_ERR(child_inode)) {
			ret = PTR_ERR(child_inode);
			break;
		}

		ret = ocfs2_inode_lock(child_inode, NULL, 0);
		if (ret < 0) {
			iput(child_inode);
			if (ret != -ENOENT)
				mlog_errno(ret);
			break;
		}

		ret = ocfs2_lookup_ino_from_name(child_inode, "..", 2,
				&parent_inode_no);
		ocfs2_inode_unlock(child_inode, 0);
		iput(child_inode);
		if (ret < 0) {
			ret = -ENOENT;
			break;
		}

		if (parent_inode_no == dest_inode_no) {
			ret = 1;
			break;
		}

		if (parent_inode_no == osb->root_inode->i_ino) {
			ret = 0;
			break;
		}

		child_inode_no = parent_inode_no;

		if (++i >= MAX_LOOKUP_TIMES) {
			mlog(ML_NOTICE, "max lookup times reached, filesystem "
					"may have nested directories, "
					"src inode: %llu, dest inode: %llu.\n",
					(unsigned long long)src_inode_no,
					(unsigned long long)dest_inode_no);
			ret = 0;
			break;
		}
	}

	return ret;
}