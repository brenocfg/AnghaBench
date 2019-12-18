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
struct ubifs_lpt_heap {int /*<<< orphan*/  max_cnt; int /*<<< orphan*/  cnt; } ;
struct ubifs_lprops {int flags; scalar_t__ dirty; scalar_t__ free; } ;
struct TYPE_2__ {int empty_lebs; int taken_empty_lebs; } ;
struct ubifs_info {int freeable_cnt; int lsave_cnt; TYPE_1__ lst; scalar_t__ dark_wm; struct ubifs_lpt_heap* lpt_heap; } ;

/* Variables and functions */
 int LPROPS_CAT_MASK ; 
#define  LPROPS_DIRTY 133 
#define  LPROPS_DIRTY_IDX 132 
#define  LPROPS_EMPTY 131 
#define  LPROPS_FRDI_IDX 130 
#define  LPROPS_FREE 129 
#define  LPROPS_FREEABLE 128 

__attribute__((used)) static int valuable(struct ubifs_info *c, const struct ubifs_lprops *lprops)
{
	int n, cat = lprops->flags & LPROPS_CAT_MASK;
	struct ubifs_lpt_heap *heap;

	switch (cat) {
	case LPROPS_DIRTY:
	case LPROPS_DIRTY_IDX:
	case LPROPS_FREE:
		heap = &c->lpt_heap[cat - 1];
		if (heap->cnt < heap->max_cnt)
			return 1;
		if (lprops->free + lprops->dirty >= c->dark_wm)
			return 1;
		return 0;
	case LPROPS_EMPTY:
		n = c->lst.empty_lebs + c->freeable_cnt -
		    c->lst.taken_empty_lebs;
		if (n < c->lsave_cnt)
			return 1;
		return 0;
	case LPROPS_FREEABLE:
		return 1;
	case LPROPS_FRDI_IDX:
		return 1;
	}
	return 0;
}