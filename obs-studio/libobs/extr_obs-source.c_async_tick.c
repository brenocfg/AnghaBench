#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_11__ {int /*<<< orphan*/ * cur_async_frame; int /*<<< orphan*/  async_update_texture; int /*<<< orphan*/  async_mutex; int /*<<< orphan*/  last_sys_timestamp; } ;
typedef  TYPE_2__ obs_source_t ;
struct TYPE_10__ {int /*<<< orphan*/  video_time; } ;
struct TYPE_12__ {TYPE_1__ video; } ;

/* Variables and functions */
 int /*<<< orphan*/  deinterlace_process_last_frame (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ deinterlacing_enabled (TYPE_2__*) ; 
 int /*<<< orphan*/ * get_closest_frame (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_5__* obs ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remove_async_frame (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_async_texture_size (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void async_tick(obs_source_t *source)
{
	uint64_t sys_time = obs->video.video_time;

	pthread_mutex_lock(&source->async_mutex);

	if (deinterlacing_enabled(source)) {
		deinterlace_process_last_frame(source, sys_time);
	} else {
		if (source->cur_async_frame) {
			remove_async_frame(source, source->cur_async_frame);
			source->cur_async_frame = NULL;
		}

		source->cur_async_frame = get_closest_frame(source, sys_time);
	}

	source->last_sys_timestamp = sys_time;
	pthread_mutex_unlock(&source->async_mutex);

	if (source->cur_async_frame)
		source->async_update_texture =
			set_async_texture_size(source, source->cur_async_frame);
}