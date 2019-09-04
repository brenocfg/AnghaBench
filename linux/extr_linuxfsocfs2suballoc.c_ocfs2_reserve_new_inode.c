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
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct ocfs2_super {int s_mount_opt; int /*<<< orphan*/  s_num_inodes_stolen; int /*<<< orphan*/  osb_lock; scalar_t__ osb_inode_alloc_group; scalar_t__ slot_num; } ;
struct ocfs2_alloc_context {int ac_bits_wanted; scalar_t__ ac_max_block; int /*<<< orphan*/  ac_group_search; int /*<<< orphan*/  ac_which; } ;

/* Variables and functions */
 int ALLOC_GROUPS_FROM_GLOBAL ; 
 int ALLOC_NEW_GROUP ; 
 int ENOMEM ; 
 int ENOSPC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INODE_ALLOC_SYSTEM_INODE ; 
 int /*<<< orphan*/  OCFS2_AC_USE_INODE ; 
 int OCFS2_INVALID_SLOT ; 
 scalar_t__ OCFS2_MAX_TO_STEAL ; 
 int OCFS2_MOUNT_INODE64 ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct ocfs2_alloc_context* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  ocfs2_block_group_search ; 
 int /*<<< orphan*/  ocfs2_free_ac_resource (struct ocfs2_alloc_context*) ; 
 int /*<<< orphan*/  ocfs2_free_alloc_context (struct ocfs2_alloc_context*) ; 
 int ocfs2_get_inode_steal_slot (struct ocfs2_super*) ; 
 int /*<<< orphan*/  ocfs2_init_inode_steal_slot (struct ocfs2_super*) ; 
 int ocfs2_reserve_suballoc_bits (struct ocfs2_super*,struct ocfs2_alloc_context*,int /*<<< orphan*/ ,scalar_t__,scalar_t__*,int) ; 
 int ocfs2_steal_inode (struct ocfs2_super*,struct ocfs2_alloc_context*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_ocfs2_reserve_new_inode_new_group (unsigned long long) ; 

int ocfs2_reserve_new_inode(struct ocfs2_super *osb,
			    struct ocfs2_alloc_context **ac)
{
	int status;
	int slot = ocfs2_get_inode_steal_slot(osb);
	u64 alloc_group;

	*ac = kzalloc(sizeof(struct ocfs2_alloc_context), GFP_KERNEL);
	if (!(*ac)) {
		status = -ENOMEM;
		mlog_errno(status);
		goto bail;
	}

	(*ac)->ac_bits_wanted = 1;
	(*ac)->ac_which = OCFS2_AC_USE_INODE;

	(*ac)->ac_group_search = ocfs2_block_group_search;

	/*
	 * stat(2) can't handle i_ino > 32bits, so we tell the
	 * lower levels not to allocate us a block group past that
	 * limit.  The 'inode64' mount option avoids this behavior.
	 */
	if (!(osb->s_mount_opt & OCFS2_MOUNT_INODE64))
		(*ac)->ac_max_block = (u32)~0U;

	/*
	 * slot is set when we successfully steal inode from other nodes.
	 * It is reset in 3 places:
	 * 1. when we flush the truncate log
	 * 2. when we complete local alloc recovery.
	 * 3. when we successfully allocate from our own slot.
	 * After it is set, we will go on stealing inodes until we find the
	 * need to check our slots to see whether there is some space for us.
	 */
	if (slot != OCFS2_INVALID_SLOT &&
	    atomic_read(&osb->s_num_inodes_stolen) < OCFS2_MAX_TO_STEAL)
		goto inode_steal;

	atomic_set(&osb->s_num_inodes_stolen, 0);
	alloc_group = osb->osb_inode_alloc_group;
	status = ocfs2_reserve_suballoc_bits(osb, *ac,
					     INODE_ALLOC_SYSTEM_INODE,
					     (u32)osb->slot_num,
					     &alloc_group,
					     ALLOC_NEW_GROUP |
					     ALLOC_GROUPS_FROM_GLOBAL);
	if (status >= 0) {
		status = 0;

		spin_lock(&osb->osb_lock);
		osb->osb_inode_alloc_group = alloc_group;
		spin_unlock(&osb->osb_lock);
		trace_ocfs2_reserve_new_inode_new_group(
			(unsigned long long)alloc_group);

		/*
		 * Some inodes must be freed by us, so try to allocate
		 * from our own next time.
		 */
		if (slot != OCFS2_INVALID_SLOT)
			ocfs2_init_inode_steal_slot(osb);
		goto bail;
	} else if (status < 0 && status != -ENOSPC) {
		mlog_errno(status);
		goto bail;
	}

	ocfs2_free_ac_resource(*ac);

inode_steal:
	status = ocfs2_steal_inode(osb, *ac);
	atomic_inc(&osb->s_num_inodes_stolen);
	if (status < 0) {
		if (status != -ENOSPC)
			mlog_errno(status);
		goto bail;
	}

	status = 0;
bail:
	if ((status < 0) && *ac) {
		ocfs2_free_alloc_context(*ac);
		*ac = NULL;
	}

	if (status)
		mlog_errno(status);
	return status;
}