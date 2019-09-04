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
struct ubifs_lprops {int flags; int /*<<< orphan*/  list; } ;
struct ubifs_info {int freeable_cnt; scalar_t__ in_a_category_cnt; scalar_t__ main_lebs; int /*<<< orphan*/  frdi_idx_list; int /*<<< orphan*/  freeable_list; int /*<<< orphan*/  empty_list; int /*<<< orphan*/  uncat_list; } ;

/* Variables and functions */
 int LPROPS_CAT_MASK ; 
#define  LPROPS_DIRTY 134 
#define  LPROPS_DIRTY_IDX 133 
#define  LPROPS_EMPTY 132 
#define  LPROPS_FRDI_IDX 131 
#define  LPROPS_FREE 130 
#define  LPROPS_FREEABLE 129 
#define  LPROPS_UNCAT 128 
 int /*<<< orphan*/  add_to_lpt_heap (struct ubifs_info*,struct ubifs_lprops*,int) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ubifs_assert (struct ubifs_info*,int) ; 

void ubifs_add_to_cat(struct ubifs_info *c, struct ubifs_lprops *lprops,
		      int cat)
{
	switch (cat) {
	case LPROPS_DIRTY:
	case LPROPS_DIRTY_IDX:
	case LPROPS_FREE:
		if (add_to_lpt_heap(c, lprops, cat))
			break;
		/* No more room on heap so make it un-categorized */
		cat = LPROPS_UNCAT;
		/* Fall through */
	case LPROPS_UNCAT:
		list_add(&lprops->list, &c->uncat_list);
		break;
	case LPROPS_EMPTY:
		list_add(&lprops->list, &c->empty_list);
		break;
	case LPROPS_FREEABLE:
		list_add(&lprops->list, &c->freeable_list);
		c->freeable_cnt += 1;
		break;
	case LPROPS_FRDI_IDX:
		list_add(&lprops->list, &c->frdi_idx_list);
		break;
	default:
		ubifs_assert(c, 0);
	}

	lprops->flags &= ~LPROPS_CAT_MASK;
	lprops->flags |= cat;
	c->in_a_category_cnt += 1;
	ubifs_assert(c, c->in_a_category_cnt <= c->main_lebs);
}