#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_7__ {scalar_t__ data; } ;
struct TYPE_8__ {int output_flags; int /*<<< orphan*/  (* video_render ) (scalar_t__,int /*<<< orphan*/ *) ;} ;
struct TYPE_9__ {scalar_t__ num; } ;
struct TYPE_10__ {TYPE_1__ context; TYPE_2__ info; TYPE_3__ filters; int /*<<< orphan*/  filter_parent; } ;
typedef  TYPE_4__ obs_source_t ;

/* Variables and functions */
 int OBS_SOURCE_CUSTOM_DRAW ; 
 int /*<<< orphan*/ * gs_get_effect () ; 
 int /*<<< orphan*/  obs_source_default_render (TYPE_4__*) ; 
 int /*<<< orphan*/  stub1 (scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void obs_source_main_render(obs_source_t *source)
{
	uint32_t flags = source->info.output_flags;
	bool custom_draw = (flags & OBS_SOURCE_CUSTOM_DRAW) != 0;
	bool default_effect = !source->filter_parent &&
			      source->filters.num == 0 && !custom_draw;

	if (default_effect)
		obs_source_default_render(source);
	else if (source->context.data)
		source->info.video_render(source->context.data,
					  custom_draw ? NULL : gs_get_effect());
}