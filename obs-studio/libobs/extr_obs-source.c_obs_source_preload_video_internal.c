#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct obs_source_frame {int /*<<< orphan*/  timestamp; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  format; } ;
struct TYPE_7__ {int /*<<< orphan*/  last_frame_ts; int /*<<< orphan*/  async_texrender; int /*<<< orphan*/  async_textures; int /*<<< orphan*/  async_preload_frame; } ;
typedef  TYPE_1__ obs_source_t ;

/* Variables and functions */
 int /*<<< orphan*/  copy_frame_data (int /*<<< orphan*/ ,struct obs_source_frame const*) ; 
 int /*<<< orphan*/  obs_enter_graphics () ; 
 int /*<<< orphan*/  obs_leave_graphics () ; 
 int /*<<< orphan*/  obs_source_frame_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_source_frame_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_source_valid (TYPE_1__*,char*) ; 
 scalar_t__ preload_frame_changed (TYPE_1__*,struct obs_source_frame const*) ; 
 int /*<<< orphan*/  set_async_texture_size (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_async_textures (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
obs_source_preload_video_internal(obs_source_t *source,
				  const struct obs_source_frame *frame)
{
	if (!obs_source_valid(source, "obs_source_preload_video"))
		return;
	if (!frame)
		return;

	obs_enter_graphics();

	if (preload_frame_changed(source, frame)) {
		obs_source_frame_destroy(source->async_preload_frame);
		source->async_preload_frame = obs_source_frame_create(
			frame->format, frame->width, frame->height);
	}

	copy_frame_data(source->async_preload_frame, frame);
	set_async_texture_size(source, source->async_preload_frame);
	update_async_textures(source, source->async_preload_frame,
			      source->async_textures, source->async_texrender);

	source->last_frame_ts = frame->timestamp;

	obs_leave_graphics();
}