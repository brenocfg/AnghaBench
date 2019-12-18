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
struct ocfs2_super {TYPE_1__* journal; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct TYPE_2__ {int /*<<< orphan*/  j_checkpointed; } ;

/* Variables and functions */
 int /*<<< orphan*/  INODE_CACHE (struct inode*) ; 
 struct ocfs2_super* OCFS2_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_ci_fully_checkpointed (int /*<<< orphan*/ ) ; 
 scalar_t__ ocfs2_mount_local (struct ocfs2_super*) ; 
 int /*<<< orphan*/  ocfs2_start_checkpoint (struct ocfs2_super*) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void ocfs2_checkpoint_inode(struct inode *inode)
{
	struct ocfs2_super *osb = OCFS2_SB(inode->i_sb);

	if (ocfs2_mount_local(osb))
		return;

	if (!ocfs2_ci_fully_checkpointed(INODE_CACHE(inode))) {
		/* WARNING: This only kicks off a single
		 * checkpoint. If someone races you and adds more
		 * metadata to the journal, you won't know, and will
		 * wind up waiting *a lot* longer than necessary. Right
		 * now we only use this in clear_inode so that's
		 * OK. */
		ocfs2_start_checkpoint(osb);

		wait_event(osb->journal->j_checkpointed,
			   ocfs2_ci_fully_checkpointed(INODE_CACHE(inode)));
	}
}