#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ num; scalar_t__ array; } ;
struct TYPE_6__ {int /*<<< orphan*/  input_mutex; int /*<<< orphan*/  gpu_refs; int /*<<< orphan*/  raw_active; TYPE_5__ inputs; } ;
typedef  TYPE_1__ video_t ;

/* Variables and functions */
 size_t DARRAY_INVALID ; 
 int /*<<< orphan*/  da_erase (TYPE_5__,size_t) ; 
 int /*<<< orphan*/  log_skipped (TYPE_1__*) ; 
 int /*<<< orphan*/  os_atomic_load_long (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_atomic_set_bool (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 size_t video_get_input_idx (TYPE_1__*,void (*) (void*,struct video_data*),void*) ; 
 int /*<<< orphan*/  video_input_free (scalar_t__) ; 

void video_output_disconnect(video_t *video,
			     void (*callback)(void *param,
					      struct video_data *frame),
			     void *param)
{
	if (!video || !callback)
		return;

	pthread_mutex_lock(&video->input_mutex);

	size_t idx = video_get_input_idx(video, callback, param);
	if (idx != DARRAY_INVALID) {
		video_input_free(video->inputs.array + idx);
		da_erase(video->inputs, idx);

		if (video->inputs.num == 0) {
			os_atomic_set_bool(&video->raw_active, false);
			if (!os_atomic_load_long(&video->gpu_refs)) {
				log_skipped(video);
			}
		}
	}

	pthread_mutex_unlock(&video->input_mutex);
}