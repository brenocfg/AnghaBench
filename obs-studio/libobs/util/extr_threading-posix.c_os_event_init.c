#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct os_event_data {int manual; int signalled; int /*<<< orphan*/  mutex; int /*<<< orphan*/  cond; } ;
typedef  struct os_event_data os_event_t ;
typedef  enum os_event_type { ____Placeholder_os_event_type } os_event_type ;

/* Variables and functions */
 int OS_EVENT_TYPE_MANUAL ; 
 int /*<<< orphan*/  bfree (struct os_event_data*) ; 
 struct os_event_data* bzalloc (int) ; 
 int pthread_cond_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 
 int pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int os_event_init(os_event_t **event, enum os_event_type type)
{
	int code = 0;

	struct os_event_data *data = bzalloc(sizeof(struct os_event_data));

	if ((code = pthread_mutex_init(&data->mutex, NULL)) < 0) {
		bfree(data);
		return code;
	}

	if ((code = pthread_cond_init(&data->cond, NULL)) < 0) {
		pthread_mutex_destroy(&data->mutex);
		bfree(data);
		return code;
	}

	data->manual = (type == OS_EVENT_TYPE_MANUAL);
	data->signalled = false;
	*event = data;

	return 0;
}