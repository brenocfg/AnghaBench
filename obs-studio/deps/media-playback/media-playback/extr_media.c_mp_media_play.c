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
struct TYPE_3__ {int active; int reset; int looping; int /*<<< orphan*/  sem; int /*<<< orphan*/  mutex; } ;
typedef  TYPE_1__ mp_media_t ;

/* Variables and functions */
 int /*<<< orphan*/  os_sem_post (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

void mp_media_play(mp_media_t *m, bool loop)
{
	pthread_mutex_lock(&m->mutex);

	if (m->active)
		m->reset = true;

	m->looping = loop;
	m->active = true;

	pthread_mutex_unlock(&m->mutex);

	os_sem_post(m->sem);
}