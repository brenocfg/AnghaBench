#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct obs_source_frame {int /*<<< orphan*/  refs; } ;
struct TYPE_4__ {int /*<<< orphan*/  async_mutex; struct obs_source_frame* cur_async_frame; } ;
typedef  TYPE_1__ obs_source_t ;

/* Variables and functions */
 int /*<<< orphan*/  obs_source_valid (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  os_atomic_inc_long (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

struct obs_source_frame *obs_source_get_frame(obs_source_t *source)
{
	struct obs_source_frame *frame = NULL;

	if (!obs_source_valid(source, "obs_source_get_frame"))
		return NULL;

	pthread_mutex_lock(&source->async_mutex);

	frame = source->cur_async_frame;
	source->cur_async_frame = NULL;

	if (frame) {
		os_atomic_inc_long(&frame->refs);
	}

	pthread_mutex_unlock(&source->async_mutex);

	return frame;
}