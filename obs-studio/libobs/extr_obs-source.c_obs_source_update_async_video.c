#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct obs_source_frame {scalar_t__ timestamp; } ;
struct TYPE_11__ {int async_rendered; int timing_set; int async_update_texture; int /*<<< orphan*/  async_texrender; int /*<<< orphan*/  async_textures; scalar_t__ timing_adjust; int /*<<< orphan*/  async_unbuffered; int /*<<< orphan*/  async_decoupled; } ;
typedef  TYPE_2__ obs_source_t ;
struct TYPE_10__ {scalar_t__ video_time; } ;
struct TYPE_12__ {TYPE_1__ video; } ;

/* Variables and functions */
 int /*<<< orphan*/  check_to_swap_bgrx_bgra (TYPE_2__*,struct obs_source_frame*) ; 
 struct obs_source_frame* filter_async_video (TYPE_2__*,struct obs_source_frame*) ; 
 TYPE_7__* obs ; 
 struct obs_source_frame* obs_source_get_frame (TYPE_2__*) ; 
 int /*<<< orphan*/  obs_source_release_frame (TYPE_2__*,struct obs_source_frame*) ; 
 int /*<<< orphan*/  update_async_textures (TYPE_2__*,struct obs_source_frame*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void obs_source_update_async_video(obs_source_t *source)
{
	if (!source->async_rendered) {
		struct obs_source_frame *frame = obs_source_get_frame(source);

		if (frame)
			frame = filter_async_video(source, frame);

		source->async_rendered = true;
		if (frame) {
			check_to_swap_bgrx_bgra(source, frame);

			if (!source->async_decoupled ||
			    !source->async_unbuffered) {
				source->timing_adjust = obs->video.video_time -
							frame->timestamp;
				source->timing_set = true;
			}

			if (source->async_update_texture) {
				update_async_textures(source, frame,
						      source->async_textures,
						      source->async_texrender);
				source->async_update_texture = false;
			}

			obs_source_release_frame(source, frame);
		}
	}
}