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
struct TYPE_4__ {int /*<<< orphan*/  async_mutex; } ;
typedef  TYPE_1__ obs_source_t ;

/* Variables and functions */
 int /*<<< orphan*/  obs_source_frame_destroy (struct obs_source_frame*) ; 
 scalar_t__ os_atomic_dec_long (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remove_async_frame (TYPE_1__*,struct obs_source_frame*) ; 

void obs_source_release_frame(obs_source_t *source,
			      struct obs_source_frame *frame)
{
	if (!frame)
		return;

	if (!source) {
		obs_source_frame_destroy(frame);
	} else {
		pthread_mutex_lock(&source->async_mutex);

		if (os_atomic_dec_long(&frame->refs) == 0)
			obs_source_frame_destroy(frame);
		else
			remove_async_frame(source, frame);

		pthread_mutex_unlock(&source->async_mutex);
	}
}