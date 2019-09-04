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
struct ocfs2_lock_holder {int dummy; } ;
struct inode {int dummy; } ;
struct buffer_head {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ip_xattr_sem; } ;

/* Variables and functions */
 TYPE_1__* OCFS2_I (struct inode*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_inode_lock_tracker (struct inode*,struct buffer_head**,int /*<<< orphan*/ ,struct ocfs2_lock_holder*) ; 
 int /*<<< orphan*/  ocfs2_inode_unlock_tracker (struct inode*,int /*<<< orphan*/ ,struct ocfs2_lock_holder*,int) ; 
 int ocfs2_xattr_get_nolock (struct inode*,struct buffer_head*,int,char const*,void*,size_t) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ocfs2_xattr_get(struct inode *inode,
			   int name_index,
			   const char *name,
			   void *buffer,
			   size_t buffer_size)
{
	int ret, had_lock;
	struct buffer_head *di_bh = NULL;
	struct ocfs2_lock_holder oh;

	had_lock = ocfs2_inode_lock_tracker(inode, &di_bh, 0, &oh);
	if (had_lock < 0) {
		mlog_errno(had_lock);
		return had_lock;
	}
	down_read(&OCFS2_I(inode)->ip_xattr_sem);
	ret = ocfs2_xattr_get_nolock(inode, di_bh, name_index,
				     name, buffer, buffer_size);
	up_read(&OCFS2_I(inode)->ip_xattr_sem);

	ocfs2_inode_unlock_tracker(inode, 0, &oh, had_lock);

	brelse(di_bh);

	return ret;
}