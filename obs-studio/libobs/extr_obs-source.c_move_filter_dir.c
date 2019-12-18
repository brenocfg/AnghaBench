#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_8__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int num; TYPE_1__** array; } ;
struct TYPE_11__ {struct TYPE_11__* filter_target; TYPE_8__ filters; } ;
typedef  TYPE_1__ obs_source_t ;
typedef  enum obs_order_movement { ____Placeholder_obs_order_movement } obs_order_movement ;

/* Variables and functions */
 size_t DARRAY_INVALID ; 
 int OBS_ORDER_MOVE_BOTTOM ; 
 int OBS_ORDER_MOVE_DOWN ; 
 int OBS_ORDER_MOVE_TOP ; 
 int OBS_ORDER_MOVE_UP ; 
 size_t da_find (TYPE_8__,TYPE_1__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  da_move_item (TYPE_8__,size_t,int) ; 
 size_t find_next_filter (TYPE_1__*,TYPE_1__*,size_t) ; 
 size_t find_prev_filter (TYPE_1__*,TYPE_1__*,size_t) ; 

__attribute__((used)) static bool move_filter_dir(obs_source_t *source, obs_source_t *filter,
			    enum obs_order_movement movement)
{
	size_t idx;

	idx = da_find(source->filters, &filter, 0);
	if (idx == DARRAY_INVALID)
		return false;

	if (movement == OBS_ORDER_MOVE_UP) {
		size_t next_id = find_next_filter(source, filter, idx);
		if (next_id == DARRAY_INVALID)
			return false;
		da_move_item(source->filters, idx, next_id);

	} else if (movement == OBS_ORDER_MOVE_DOWN) {
		size_t prev_id = find_prev_filter(source, filter, idx);
		if (prev_id == DARRAY_INVALID)
			return false;
		da_move_item(source->filters, idx, prev_id);

	} else if (movement == OBS_ORDER_MOVE_TOP) {
		if (idx == source->filters.num - 1)
			return false;
		da_move_item(source->filters, idx, source->filters.num - 1);

	} else if (movement == OBS_ORDER_MOVE_BOTTOM) {
		if (idx == 0)
			return false;
		da_move_item(source->filters, idx, 0);
	}

	/* reorder filter targets, not the nicest way of dealing with things */
	for (size_t i = 0; i < source->filters.num; i++) {
		obs_source_t *next_filter =
			(i == source->filters.num - 1)
				? source
				: source->filters.array[i + 1];

		source->filters.array[i]->filter_target = next_filter;
	}

	return true;
}