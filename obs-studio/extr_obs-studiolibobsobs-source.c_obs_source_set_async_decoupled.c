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
struct TYPE_5__ {int async_decoupled; int timing_set; int /*<<< orphan*/  audio_buf_mutex; } ;
typedef  TYPE_1__ obs_source_t ;

/* Variables and functions */
 int /*<<< orphan*/  obs_ptr_valid (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reset_audio_data (TYPE_1__*,int /*<<< orphan*/ ) ; 

void obs_source_set_async_decoupled(obs_source_t *source, bool decouple)
{
	if (!obs_ptr_valid(source, "obs_source_set_async_decoupled"))
		return;

	source->async_decoupled = decouple;
	if (decouple) {
		pthread_mutex_lock(&source->audio_buf_mutex);
		source->timing_set = false;
		reset_audio_data(source, 0);
		pthread_mutex_unlock(&source->audio_buf_mutex);
	}
}