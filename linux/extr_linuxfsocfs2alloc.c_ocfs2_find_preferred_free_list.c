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
struct ocfs2_per_slot_free_list {int f_inode_type; int f_slot; struct ocfs2_per_slot_free_list* f_next_suballocator; } ;
struct ocfs2_cached_dealloc_ctxt {struct ocfs2_per_slot_free_list* c_first_suballocator; } ;

/* Variables and functions */

__attribute__((used)) static struct ocfs2_per_slot_free_list *
ocfs2_find_preferred_free_list(int type,
			       int preferred_slot,
			       int *real_slot,
			       struct ocfs2_cached_dealloc_ctxt *ctxt)
{
	struct ocfs2_per_slot_free_list *fl = ctxt->c_first_suballocator;

	while (fl) {
		if (fl->f_inode_type == type && fl->f_slot == preferred_slot) {
			*real_slot = fl->f_slot;
			return fl;
		}

		fl = fl->f_next_suballocator;
	}

	/* If we can't find any free list matching preferred slot, just use
	 * the first one.
	 */
	fl = ctxt->c_first_suballocator;
	*real_slot = fl->f_slot;

	return fl;
}