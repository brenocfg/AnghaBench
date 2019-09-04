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
struct ocfs2_super {int dummy; } ;
struct ocfs2_alloc_context {int /*<<< orphan*/  ac_group_search; int /*<<< orphan*/  ac_which; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_NEW_GROUP ; 
 int ENOSPC ; 
 int /*<<< orphan*/  GLOBAL_BITMAP_SYSTEM_INODE ; 
 int /*<<< orphan*/  OCFS2_AC_USE_MAIN ; 
 int /*<<< orphan*/  OCFS2_INVALID_SLOT ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  ocfs2_cluster_group_search ; 
 int ocfs2_reserve_suballoc_bits (struct ocfs2_super*,struct ocfs2_alloc_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int ocfs2_reserve_cluster_bitmap_bits(struct ocfs2_super *osb,
				      struct ocfs2_alloc_context *ac)
{
	int status;

	ac->ac_which = OCFS2_AC_USE_MAIN;
	ac->ac_group_search = ocfs2_cluster_group_search;

	status = ocfs2_reserve_suballoc_bits(osb, ac,
					     GLOBAL_BITMAP_SYSTEM_INODE,
					     OCFS2_INVALID_SLOT, NULL,
					     ALLOC_NEW_GROUP);
	if (status < 0 && status != -ENOSPC)
		mlog_errno(status);

	return status;
}