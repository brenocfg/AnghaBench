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
struct TYPE_3__ {int peak_meter_type; int /*<<< orphan*/  mutex; } ;
typedef  TYPE_1__ obs_volmeter_t ;
typedef  enum obs_peak_meter_type { ____Placeholder_obs_peak_meter_type } obs_peak_meter_type ;

/* Variables and functions */
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

void obs_volmeter_set_peak_meter_type(obs_volmeter_t *volmeter,
				      enum obs_peak_meter_type peak_meter_type)
{
	pthread_mutex_lock(&volmeter->mutex);
	volmeter->peak_meter_type = peak_meter_type;
	pthread_mutex_unlock(&volmeter->mutex);
}