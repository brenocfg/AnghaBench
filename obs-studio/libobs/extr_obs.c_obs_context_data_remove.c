#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct obs_context_data {int /*<<< orphan*/ * mutex; TYPE_1__** prev_next; TYPE_1__* next; } ;
struct TYPE_2__ {struct TYPE_2__** prev_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

void obs_context_data_remove(struct obs_context_data *context)
{
	if (context && context->mutex) {
		pthread_mutex_lock(context->mutex);
		if (context->prev_next)
			*context->prev_next = context->next;
		if (context->next)
			context->next->prev_next = context->prev_next;
		pthread_mutex_unlock(context->mutex);

		context->mutex = NULL;
	}
}