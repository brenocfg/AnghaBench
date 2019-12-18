#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct global_callback_info {void* member_1; int member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_0; } ;
struct TYPE_3__ {int /*<<< orphan*/  global_callbacks_mutex; int /*<<< orphan*/  global_callbacks; } ;
typedef  TYPE_1__ signal_handler_t ;
typedef  int /*<<< orphan*/  global_signal_callback_t ;

/* Variables and functions */
 size_t DARRAY_INVALID ; 
 size_t da_find (int /*<<< orphan*/ ,struct global_callback_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  da_push_back (int /*<<< orphan*/ ,struct global_callback_info*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

void signal_handler_connect_global(signal_handler_t *handler,
				   global_signal_callback_t callback,
				   void *data)
{
	struct global_callback_info cb_data = {callback, data, 0, false};
	size_t idx;

	if (!handler || !callback)
		return;

	pthread_mutex_lock(&handler->global_callbacks_mutex);

	idx = da_find(handler->global_callbacks, &cb_data, 0);
	if (idx == DARRAY_INVALID)
		da_push_back(handler->global_callbacks, &cb_data);

	pthread_mutex_unlock(&handler->global_callbacks_mutex);
}