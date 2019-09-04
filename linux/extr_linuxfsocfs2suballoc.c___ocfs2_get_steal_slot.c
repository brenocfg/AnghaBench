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
struct ocfs2_super {int s_inode_steal_slot; int s_meta_steal_slot; int /*<<< orphan*/  osb_lock; } ;

/* Variables and functions */
 int EXTENT_ALLOC_SYSTEM_INODE ; 
 int INODE_ALLOC_SYSTEM_INODE ; 
 int OCFS2_INVALID_SLOT ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __ocfs2_get_steal_slot(struct ocfs2_super *osb, int type)
{
	int slot = OCFS2_INVALID_SLOT;

	spin_lock(&osb->osb_lock);
	if (type == INODE_ALLOC_SYSTEM_INODE)
		slot = osb->s_inode_steal_slot;
	else if (type == EXTENT_ALLOC_SYSTEM_INODE)
		slot = osb->s_meta_steal_slot;
	spin_unlock(&osb->osb_lock);

	return slot;
}