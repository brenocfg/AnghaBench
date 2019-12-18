#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct meter_cb {void* member_1; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  obs_volmeter_updated_t ;
struct TYPE_4__ {int /*<<< orphan*/  callback_mutex; int /*<<< orphan*/  callbacks; } ;
typedef  TYPE_1__ obs_volmeter_t ;

/* Variables and functions */
 int /*<<< orphan*/  da_erase_item (int /*<<< orphan*/ ,struct meter_cb*) ; 
 int /*<<< orphan*/  obs_ptr_valid (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

void obs_volmeter_remove_callback(obs_volmeter_t *volmeter,
				  obs_volmeter_updated_t callback, void *param)
{
	struct meter_cb cb = {callback, param};

	if (!obs_ptr_valid(volmeter, "obs_volmeter_remove_callback"))
		return;

	pthread_mutex_lock(&volmeter->callback_mutex);
	da_erase_item(volmeter->callbacks, &cb);
	pthread_mutex_unlock(&volmeter->callback_mutex);
}