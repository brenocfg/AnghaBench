#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct global_callback_info {void* member_1; int member_2; int remove; scalar_t__ signaling; int /*<<< orphan*/  member_0; } ;
struct TYPE_6__ {struct global_callback_info* array; } ;
struct TYPE_5__ {int /*<<< orphan*/  global_callbacks_mutex; TYPE_3__ global_callbacks; } ;
typedef  TYPE_1__ signal_handler_t ;
typedef  int /*<<< orphan*/  global_signal_callback_t ;

/* Variables and functions */
 size_t DARRAY_INVALID ; 
 int /*<<< orphan*/  da_erase (TYPE_3__,size_t) ; 
 size_t da_find (TYPE_3__,struct global_callback_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

void signal_handler_disconnect_global(signal_handler_t *handler,
				      global_signal_callback_t callback,
				      void *data)
{
	struct global_callback_info cb_data = {callback, data, false};
	size_t idx;

	if (!handler || !callback)
		return;

	pthread_mutex_lock(&handler->global_callbacks_mutex);

	idx = da_find(handler->global_callbacks, &cb_data, 0);
	if (idx != DARRAY_INVALID) {
		struct global_callback_info *cb =
			handler->global_callbacks.array + idx;

		if (cb->signaling)
			cb->remove = true;
		else
			da_erase(handler->global_callbacks, idx);
	}

	pthread_mutex_unlock(&handler->global_callbacks_mutex);
}