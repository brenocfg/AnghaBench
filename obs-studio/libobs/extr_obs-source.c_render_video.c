#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {scalar_t__ type; int output_flags; scalar_t__ video_render; } ;
struct TYPE_16__ {scalar_t__ num; } ;
struct TYPE_15__ {int /*<<< orphan*/  data; } ;
struct TYPE_18__ {scalar_t__ filter_target; TYPE_3__ info; int /*<<< orphan*/  rendering_filter; TYPE_2__ filters; scalar_t__ filter_parent; int /*<<< orphan*/  enabled; TYPE_1__ context; } ;
typedef  TYPE_4__ obs_source_t ;

/* Variables and functions */
 int /*<<< orphan*/  GS_DEBUG_COLOR_SOURCE ; 
 int /*<<< orphan*/  GS_DEBUG_MARKER_BEGIN_FORMAT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GS_DEBUG_MARKER_END () ; 
 int OBS_SOURCE_ASYNC ; 
 scalar_t__ OBS_SOURCE_TYPE_FILTER ; 
 scalar_t__ OBS_SOURCE_TYPE_INPUT ; 
 int OBS_SOURCE_VIDEO ; 
 int /*<<< orphan*/  deinterlace_render (TYPE_4__*) ; 
 int /*<<< orphan*/  deinterlace_update_async_video (TYPE_4__*) ; 
 scalar_t__ deinterlacing_enabled (TYPE_4__*) ; 
 int /*<<< orphan*/  get_type_format (scalar_t__) ; 
 int /*<<< orphan*/  obs_source_get_name (TYPE_4__*) ; 
 int /*<<< orphan*/  obs_source_main_render (TYPE_4__*) ; 
 int /*<<< orphan*/  obs_source_render_async_video (TYPE_4__*) ; 
 int /*<<< orphan*/  obs_source_render_filters (TYPE_4__*) ; 
 int /*<<< orphan*/  obs_source_skip_video_filter (TYPE_4__*) ; 
 int /*<<< orphan*/  obs_source_update_async_video (TYPE_4__*) ; 
 int /*<<< orphan*/  obs_source_video_render (scalar_t__) ; 

__attribute__((used)) static inline void render_video(obs_source_t *source)
{
	if (source->info.type != OBS_SOURCE_TYPE_FILTER &&
	    (source->info.output_flags & OBS_SOURCE_VIDEO) == 0) {
		if (source->filter_parent)
			obs_source_skip_video_filter(source);
		return;
	}

	if (source->info.type == OBS_SOURCE_TYPE_INPUT &&
	    (source->info.output_flags & OBS_SOURCE_ASYNC) != 0 &&
	    !source->rendering_filter) {
		if (deinterlacing_enabled(source))
			deinterlace_update_async_video(source);
		obs_source_update_async_video(source);
	}

	if (!source->context.data || !source->enabled) {
		if (source->filter_parent)
			obs_source_skip_video_filter(source);
		return;
	}

	GS_DEBUG_MARKER_BEGIN_FORMAT(GS_DEBUG_COLOR_SOURCE,
				     get_type_format(source->info.type),
				     obs_source_get_name(source));

	if (source->filters.num && !source->rendering_filter)
		obs_source_render_filters(source);

	else if (source->info.video_render)
		obs_source_main_render(source);

	else if (source->filter_target)
		obs_source_video_render(source->filter_target);

	else if (deinterlacing_enabled(source))
		deinterlace_render(source);

	else
		obs_source_render_async_video(source);

	GS_DEBUG_MARKER_END();
}