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
typedef  int /*<<< orphan*/  u32 ;
struct ocfs2_super {int /*<<< orphan*/  s_num_meta_stolen; scalar_t__ slot_num; } ;
struct ocfs2_alloc_context {int ac_bits_wanted; int /*<<< orphan*/  ac_group_search; int /*<<< orphan*/  ac_which; } ;

/* Variables and functions */
 int ALLOC_GROUPS_FROM_GLOBAL ; 
 int ALLOC_NEW_GROUP ; 
 int ENOMEM ; 
 int ENOSPC ; 
 int /*<<< orphan*/  EXTENT_ALLOC_SYSTEM_INODE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  OCFS2_AC_USE_META ; 
 int OCFS2_INVALID_SLOT ; 
 scalar_t__ OCFS2_MAX_TO_STEAL ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct ocfs2_alloc_context* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  ocfs2_block_group_search ; 
 int /*<<< orphan*/  ocfs2_free_ac_resource (struct ocfs2_alloc_context*) ; 
 int /*<<< orphan*/  ocfs2_free_alloc_context (struct ocfs2_alloc_context*) ; 
 int ocfs2_get_meta_steal_slot (struct ocfs2_super*) ; 
 int /*<<< orphan*/  ocfs2_init_meta_steal_slot (struct ocfs2_super*) ; 
 int ocfs2_reserve_suballoc_bits (struct ocfs2_super*,struct ocfs2_alloc_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int ocfs2_steal_meta (struct ocfs2_super*,struct ocfs2_alloc_context*) ; 

int ocfs2_reserve_new_metadata_blocks(struct ocfs2_super *osb,
				      int blocks,
				      struct ocfs2_alloc_context **ac)
{
	int status;
	int slot = ocfs2_get_meta_steal_slot(osb);

	*ac = kzalloc(sizeof(struct ocfs2_alloc_context), GFP_KERNEL);
	if (!(*ac)) {
		status = -ENOMEM;
		mlog_errno(status);
		goto bail;
	}

	(*ac)->ac_bits_wanted = blocks;
	(*ac)->ac_which = OCFS2_AC_USE_META;
	(*ac)->ac_group_search = ocfs2_block_group_search;

	if (slot != OCFS2_INVALID_SLOT &&
		atomic_read(&osb->s_num_meta_stolen) < OCFS2_MAX_TO_STEAL)
		goto extent_steal;

	atomic_set(&osb->s_num_meta_stolen, 0);
	status = ocfs2_reserve_suballoc_bits(osb, (*ac),
					     EXTENT_ALLOC_SYSTEM_INODE,
					     (u32)osb->slot_num, NULL,
					     ALLOC_GROUPS_FROM_GLOBAL|ALLOC_NEW_GROUP);


	if (status >= 0) {
		status = 0;
		if (slot != OCFS2_INVALID_SLOT)
			ocfs2_init_meta_steal_slot(osb);
		goto bail;
	} else if (status < 0 && status != -ENOSPC) {
		mlog_errno(status);
		goto bail;
	}

	ocfs2_free_ac_resource(*ac);

extent_steal:
	status = ocfs2_steal_meta(osb, *ac);
	atomic_inc(&osb->s_num_meta_stolen);
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