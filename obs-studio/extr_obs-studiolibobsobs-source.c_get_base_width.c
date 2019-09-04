#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_5__ {scalar_t__ data; } ;
struct TYPE_6__ {scalar_t__ type; int /*<<< orphan*/  (* get_width ) (scalar_t__) ;} ;
struct TYPE_7__ {int /*<<< orphan*/  async_width; scalar_t__ async_active; struct TYPE_7__* filter_target; TYPE_1__ context; TYPE_2__ info; scalar_t__ enabled; int /*<<< orphan*/  transition_actual_cx; int /*<<< orphan*/  filter_parent; } ;
typedef  TYPE_3__ obs_source_t ;

/* Variables and functions */
 scalar_t__ OBS_SOURCE_TYPE_TRANSITION ; 
 int /*<<< orphan*/  stub1 (scalar_t__) ; 

__attribute__((used)) static uint32_t get_base_width(const obs_source_t *source)
{
	bool is_filter = !!source->filter_parent;
	bool func_valid = source->context.data && source->info.get_width;

	if (source->info.type == OBS_SOURCE_TYPE_TRANSITION) {
		return source->enabled ? source->transition_actual_cx : 0;

	} else if (func_valid && (!is_filter || source->enabled)) {
		return source->info.get_width(source->context.data);

	} else if (is_filter) {
		return get_base_width(source->filter_target);
	}

	return source->async_active ? source->async_width : 0;
}