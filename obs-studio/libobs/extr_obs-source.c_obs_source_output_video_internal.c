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
struct obs_source_frame {int /*<<< orphan*/  refs; } ;
struct TYPE_5__ {int async_active; int /*<<< orphan*/  async_mutex; int /*<<< orphan*/  async_frames; } ;
typedef  TYPE_1__ obs_source_t ;

/* Variables and functions */
 struct obs_source_frame* cache_video (TYPE_1__*,struct obs_source_frame const*) ; 
 int /*<<< orphan*/  da_push_back (int /*<<< orphan*/ ,struct obs_source_frame**) ; 
 int /*<<< orphan*/  obs_source_frame_destroy (struct obs_source_frame*) ; 
 int /*<<< orphan*/  obs_source_valid (TYPE_1__*,char*) ; 
 scalar_t__ os_atomic_dec_long (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
obs_source_output_video_internal(obs_source_t *source,
				 const struct obs_source_frame *frame)
{
	if (!obs_source_valid(source, "obs_source_output_video"))
		return;

	if (!frame) {
		source->async_active = false;
		return;
	}

	struct obs_source_frame *output = !!frame ? cache_video(source, frame)
						  : NULL;

	/* ------------------------------------------- */
	pthread_mutex_lock(&source->async_mutex);
	if (output) {
		if (os_atomic_dec_long(&output->refs) == 0) {
			obs_source_frame_destroy(output);
			output = NULL;
		} else {
			da_push_back(source->async_frames, &output);
			source->async_active = true;
		}
	}
	pthread_mutex_unlock(&source->async_mutex);
}