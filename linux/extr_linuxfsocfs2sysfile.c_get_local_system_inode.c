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
typedef  int u32 ;
struct ocfs2_super {int /*<<< orphan*/  osb_lock; struct inode** local_system_inodes; int /*<<< orphan*/  max_slots; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int NUM_LOCAL_SYSTEM_INODES ; 
 int OCFS2_FIRST_LOCAL_SYSTEM_INODE ; 
 int OCFS2_INVALID_SLOT ; 
 int OCFS2_LAST_LOCAL_SYSTEM_INODE ; 
 int /*<<< orphan*/  array3_size (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct inode**) ; 
 struct inode** kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct inode **get_local_system_inode(struct ocfs2_super *osb,
					     int type,
					     u32 slot)
{
	int index;
	struct inode **local_system_inodes, **free = NULL;

	BUG_ON(slot == OCFS2_INVALID_SLOT);
	BUG_ON(type < OCFS2_FIRST_LOCAL_SYSTEM_INODE ||
	       type > OCFS2_LAST_LOCAL_SYSTEM_INODE);

	spin_lock(&osb->osb_lock);
	local_system_inodes = osb->local_system_inodes;
	spin_unlock(&osb->osb_lock);

	if (unlikely(!local_system_inodes)) {
		local_system_inodes =
			kzalloc(array3_size(sizeof(struct inode *),
					    NUM_LOCAL_SYSTEM_INODES,
					    osb->max_slots),
				GFP_NOFS);
		if (!local_system_inodes) {
			mlog_errno(-ENOMEM);
			/*
			 * return NULL here so that ocfs2_get_sytem_file_inodes
			 * will try to create an inode and use it. We will try
			 * to initialize local_system_inodes next time.
			 */
			return NULL;
		}

		spin_lock(&osb->osb_lock);
		if (osb->local_system_inodes) {
			/* Someone has initialized it for us. */
			free = local_system_inodes;
			local_system_inodes = osb->local_system_inodes;
		} else
			osb->local_system_inodes = local_system_inodes;
		spin_unlock(&osb->osb_lock);
		kfree(free);
	}

	index = (slot * NUM_LOCAL_SYSTEM_INODES) +
		(type - OCFS2_FIRST_LOCAL_SYSTEM_INODE);

	return &local_system_inodes[index];
}