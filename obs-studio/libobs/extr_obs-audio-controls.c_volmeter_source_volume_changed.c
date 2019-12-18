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
struct obs_volmeter {int /*<<< orphan*/  mutex; int /*<<< orphan*/  cur_db; } ;
typedef  int /*<<< orphan*/  calldata_t ;

/* Variables and functions */
 scalar_t__ calldata_float (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mul_to_db (float) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void volmeter_source_volume_changed(void *vptr, calldata_t *calldata)
{
	struct obs_volmeter *volmeter = (struct obs_volmeter *)vptr;

	pthread_mutex_lock(&volmeter->mutex);

	float mul = (float)calldata_float(calldata, "volume");
	volmeter->cur_db = mul_to_db(mul);

	pthread_mutex_unlock(&volmeter->mutex);
}