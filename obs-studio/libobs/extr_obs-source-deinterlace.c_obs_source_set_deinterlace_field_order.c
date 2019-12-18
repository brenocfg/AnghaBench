#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int deinterlace_top_first; } ;
typedef  TYPE_1__ obs_source_t ;
typedef  enum obs_deinterlace_field_order { ____Placeholder_obs_deinterlace_field_order } obs_deinterlace_field_order ;

/* Variables and functions */
 int OBS_DEINTERLACE_FIELD_ORDER_TOP ; 
 int /*<<< orphan*/  obs_source_valid (TYPE_1__*,char*) ; 

void obs_source_set_deinterlace_field_order(
	obs_source_t *source, enum obs_deinterlace_field_order field_order)
{
	if (!obs_source_valid(source, "obs_source_set_deinterlace_field_order"))
		return;

	source->deinterlace_top_first = field_order ==
					OBS_DEINTERLACE_FIELD_ORDER_TOP;
}