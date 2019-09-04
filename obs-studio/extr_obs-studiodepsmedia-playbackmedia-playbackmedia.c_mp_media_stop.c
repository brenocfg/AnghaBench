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
struct TYPE_3__ {int active; int reset; int stopping; int /*<<< orphan*/  mutex; int /*<<< orphan*/  sem; } ;
typedef  TYPE_1__ mp_media_t ;

/* Variables and functions */
 int /*<<< orphan*/  os_sem_post (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

void mp_media_stop(mp_media_t *m)
{
	pthread_mutex_lock(&m->mutex);
	if (m->active) {
		m->reset = true;
		m->active = false;
		m->stopping = true;
		os_sem_post(m->sem);
	}
	pthread_mutex_unlock(&m->mutex);
}