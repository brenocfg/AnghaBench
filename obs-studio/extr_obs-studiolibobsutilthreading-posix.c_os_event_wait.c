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
struct TYPE_3__ {int signalled; int /*<<< orphan*/  mutex; int /*<<< orphan*/  manual; int /*<<< orphan*/  cond; } ;
typedef  TYPE_1__ os_event_t ;

/* Variables and functions */
 int pthread_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

int os_event_wait(os_event_t *event)
{
	int code = 0;
	pthread_mutex_lock(&event->mutex);
	if (!event->signalled)
		code = pthread_cond_wait(&event->cond, &event->mutex);

	if (code == 0) {
		if (!event->manual)
			event->signalled = false;
		pthread_mutex_unlock(&event->mutex);
	}

	return code;
}