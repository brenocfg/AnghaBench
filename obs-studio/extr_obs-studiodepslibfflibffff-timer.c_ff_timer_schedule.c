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
typedef  scalar_t__ uint64_t ;
struct ff_timer {int needs_wake; scalar_t__ next_wake; int /*<<< orphan*/  mutex; int /*<<< orphan*/  cond; } ;

/* Variables and functions */
 scalar_t__ av_gettime () ; 
 int /*<<< orphan*/  pthread_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

void ff_timer_schedule(struct ff_timer *timer, uint64_t microseconds)
{
	uint64_t cur_time = av_gettime();
	uint64_t new_wake_time = cur_time + microseconds;

	pthread_mutex_lock(&timer->mutex);

	timer->needs_wake = true;
	if (new_wake_time < timer->next_wake || cur_time > timer->next_wake)
		timer->next_wake = new_wake_time;

	pthread_cond_signal(&timer->cond);

	pthread_mutex_unlock(&timer->mutex);
}