#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {scalar_t__ data; } ;
struct TYPE_15__ {scalar_t__ type; int output_flags; int /*<<< orphan*/  (* video_tick ) (scalar_t__,float) ;} ;
struct TYPE_14__ {size_t num; TYPE_4__** array; } ;
struct TYPE_17__ {int showing; int active; int async_rendered; int deinterlace_rendered; TYPE_3__ context; TYPE_2__ info; TYPE_1__ filters; int /*<<< orphan*/  activate_refs; int /*<<< orphan*/  show_refs; scalar_t__ filter_texrender; scalar_t__ defer_update; } ;
typedef  TYPE_4__ obs_source_t ;

/* Variables and functions */
 int OBS_SOURCE_ASYNC ; 
 scalar_t__ OBS_SOURCE_TYPE_TRANSITION ; 
 int /*<<< orphan*/  activate_source (TYPE_4__*) ; 
 int /*<<< orphan*/  async_tick (TYPE_4__*) ; 
 int /*<<< orphan*/  deactivate_source (TYPE_4__*) ; 
 int /*<<< orphan*/  gs_texrender_reset (scalar_t__) ; 
 int /*<<< orphan*/  hide_source (TYPE_4__*) ; 
 int /*<<< orphan*/  obs_source_deferred_update (TYPE_4__*) ; 
 int /*<<< orphan*/  obs_source_valid (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  obs_transition_tick (TYPE_4__*) ; 
 int /*<<< orphan*/  show_source (TYPE_4__*) ; 
 int /*<<< orphan*/  stub1 (scalar_t__,float) ; 

void obs_source_video_tick(obs_source_t *source, float seconds)
{
	bool now_showing, now_active;

	if (!obs_source_valid(source, "obs_source_video_tick"))
		return;

	if (source->info.type == OBS_SOURCE_TYPE_TRANSITION)
		obs_transition_tick(source);

	if ((source->info.output_flags & OBS_SOURCE_ASYNC) != 0)
		async_tick(source);

	if (source->defer_update)
		obs_source_deferred_update(source);

	/* reset the filter render texture information once every frame */
	if (source->filter_texrender)
		gs_texrender_reset(source->filter_texrender);

	/* call show/hide if the reference changed */
	now_showing = !!source->show_refs;
	if (now_showing != source->showing) {
		if (now_showing) {
			show_source(source);
		} else {
			hide_source(source);
		}

		if (source->filters.num) {
			for (size_t i = source->filters.num; i > 0; i--) {
				obs_source_t *filter =
					source->filters.array[i - 1];
				if (now_showing) {
					show_source(filter);
				} else {
					hide_source(filter);
				}
			}
		}

		source->showing = now_showing;
	}

	/* call activate/deactivate if the reference changed */
	now_active = !!source->activate_refs;
	if (now_active != source->active) {
		if (now_active) {
			activate_source(source);
		} else {
			deactivate_source(source);
		}

		if (source->filters.num) {
			for (size_t i = source->filters.num; i > 0; i--) {
				obs_source_t *filter =
					source->filters.array[i - 1];
				if (now_active) {
					activate_source(filter);
				} else {
					deactivate_source(filter);
				}
			}
		}

		source->active = now_active;
	}

	if (source->context.data && source->info.video_tick)
		source->info.video_tick(source->context.data, seconds);

	source->async_rendered = false;
	source->deinterlace_rendered = false;
}