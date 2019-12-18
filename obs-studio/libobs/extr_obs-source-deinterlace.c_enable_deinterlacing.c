#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ async_format; scalar_t__ async_width; scalar_t__ async_height; int deinterlace_mode; int /*<<< orphan*/  async_mutex; int /*<<< orphan*/ * prev_async_frame; int /*<<< orphan*/  deinterlace_effect; } ;
typedef  TYPE_1__ obs_source_t ;
typedef  enum obs_deinterlace_mode { ____Placeholder_obs_deinterlace_mode } obs_deinterlace_mode ;

/* Variables and functions */
 scalar_t__ VIDEO_FORMAT_NONE ; 
 int /*<<< orphan*/  get_effect (int) ; 
 int /*<<< orphan*/  obs_enter_graphics () ; 
 int /*<<< orphan*/  obs_leave_graphics () ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remove_async_frame (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_deinterlace_texture_size (TYPE_1__*) ; 

__attribute__((used)) static void enable_deinterlacing(obs_source_t *source,
				 enum obs_deinterlace_mode mode)
{
	obs_enter_graphics();

	if (source->async_format != VIDEO_FORMAT_NONE &&
	    source->async_width != 0 && source->async_height != 0)
		set_deinterlace_texture_size(source);

	source->deinterlace_mode = mode;
	source->deinterlace_effect = get_effect(mode);

	pthread_mutex_lock(&source->async_mutex);
	if (source->prev_async_frame) {
		remove_async_frame(source, source->prev_async_frame);
		source->prev_async_frame = NULL;
	}
	pthread_mutex_unlock(&source->async_mutex);

	obs_leave_graphics();
}