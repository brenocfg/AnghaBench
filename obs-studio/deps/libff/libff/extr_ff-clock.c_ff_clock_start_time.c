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
struct ff_clock {int /*<<< orphan*/  mutex; int /*<<< orphan*/  start_time; scalar_t__ started; } ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  AV_NOPTS_VALUE ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

int64_t ff_clock_start_time(struct ff_clock *clock)
{
	int64_t start_time = AV_NOPTS_VALUE;

	pthread_mutex_lock(&clock->mutex);
	if (clock->started)
		start_time = clock->start_time;
	pthread_mutex_unlock(&clock->mutex);

	return start_time;
}