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
struct objagg_obj {int root_id; } ;
struct objagg_hints_node {unsigned int root_id; } ;
struct objagg {int /*<<< orphan*/  root_ida; TYPE_1__* hints; } ;
struct TYPE_2__ {unsigned int root_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int OBJAGG_OBJ_ROOT_ID_INVALID ; 
 int ida_alloc_range (int /*<<< orphan*/ *,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int objagg_obj_root_id_alloc(struct objagg *objagg,
				    struct objagg_obj *objagg_obj,
				    struct objagg_hints_node *hnode)
{
	unsigned int min, max;
	int root_id;

	/* In case there are no hints available, the root id is invalid. */
	if (!objagg->hints) {
		objagg_obj->root_id = OBJAGG_OBJ_ROOT_ID_INVALID;
		return 0;
	}

	if (hnode) {
		min = hnode->root_id;
		max = hnode->root_id;
	} else {
		/* For objects with no hint, start after the last
		 * hinted root_id.
		 */
		min = objagg->hints->root_count;
		max = ~0;
	}

	root_id = ida_alloc_range(&objagg->root_ida, min, max, GFP_KERNEL);

	if (root_id < 0)
		return root_id;
	objagg_obj->root_id = root_id;
	return 0;
}