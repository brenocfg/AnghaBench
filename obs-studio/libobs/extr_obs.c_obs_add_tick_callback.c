#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tick_callback {void (* member_0 ) (void*,float) ;void* member_1; } ;
struct TYPE_3__ {int /*<<< orphan*/  draw_callbacks_mutex; int /*<<< orphan*/  tick_callbacks; } ;
struct TYPE_4__ {TYPE_1__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  da_insert (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tick_callback*) ; 
 TYPE_2__* obs ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

void obs_add_tick_callback(void (*tick)(void *param, float seconds),
			   void *param)
{
	if (!obs)
		return;

	struct tick_callback data = {tick, param};

	pthread_mutex_lock(&obs->data.draw_callbacks_mutex);
	da_insert(obs->data.tick_callbacks, 0, &data);
	pthread_mutex_unlock(&obs->data.draw_callbacks_mutex);
}