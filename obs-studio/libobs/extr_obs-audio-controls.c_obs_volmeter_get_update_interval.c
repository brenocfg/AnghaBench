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
struct TYPE_3__ {unsigned int update_ms; int /*<<< orphan*/  mutex; } ;
typedef  TYPE_1__ obs_volmeter_t ;

/* Variables and functions */
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

unsigned int obs_volmeter_get_update_interval(obs_volmeter_t *volmeter)
{
	if (!volmeter)
		return 0;

	pthread_mutex_lock(&volmeter->mutex);
	const unsigned int interval = volmeter->update_ms;
	pthread_mutex_unlock(&volmeter->mutex);

	return interval;
}