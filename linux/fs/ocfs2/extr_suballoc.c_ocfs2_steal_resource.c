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
struct ocfs2_super {int slot_num; int max_slots; } ;
struct ocfs2_alloc_context {int dummy; } ;

/* Variables and functions */
 int ENOSPC ; 
 int /*<<< orphan*/  NOT_ALLOC_NEW_GROUP ; 
 int OCFS2_INVALID_SLOT ; 
 int __ocfs2_get_steal_slot (struct ocfs2_super*,int) ; 
 int /*<<< orphan*/  __ocfs2_set_steal_slot (struct ocfs2_super*,int,int) ; 
 int /*<<< orphan*/  ocfs2_free_ac_resource (struct ocfs2_alloc_context*) ; 
 int ocfs2_reserve_suballoc_bits (struct ocfs2_super*,struct ocfs2_alloc_context*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ocfs2_steal_resource(struct ocfs2_super *osb,
				struct ocfs2_alloc_context *ac,
				int type)
{
	int i, status = -ENOSPC;
	int slot = __ocfs2_get_steal_slot(osb, type);

	/* Start to steal resource from the first slot after ours. */
	if (slot == OCFS2_INVALID_SLOT)
		slot = osb->slot_num + 1;

	for (i = 0; i < osb->max_slots; i++, slot++) {
		if (slot == osb->max_slots)
			slot = 0;

		if (slot == osb->slot_num)
			continue;

		status = ocfs2_reserve_suballoc_bits(osb, ac,
						     type,
						     (u32)slot, NULL,
						     NOT_ALLOC_NEW_GROUP);
		if (status >= 0) {
			__ocfs2_set_steal_slot(osb, slot, type);
			break;
		}

		ocfs2_free_ac_resource(ac);
	}

	return status;
}