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
struct obs_output {int reconnect_retry_cur_sec; int reconnect_thread_active; int /*<<< orphan*/  reconnecting; int /*<<< orphan*/  reconnect_thread; int /*<<< orphan*/  reconnect_stop_event; } ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 scalar_t__ ETIMEDOUT ; 
 int /*<<< orphan*/  obs_output_actual_start (struct obs_output*) ; 
 int /*<<< orphan*/  os_atomic_set_bool (int /*<<< orphan*/ *,int) ; 
 scalar_t__ os_event_timedwait (int /*<<< orphan*/ ,unsigned long) ; 
 scalar_t__ os_event_try (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_detach (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *reconnect_thread(void *param)
{
	struct obs_output *output = param;
	unsigned long ms = output->reconnect_retry_cur_sec * 1000;

	output->reconnect_thread_active = true;

	if (os_event_timedwait(output->reconnect_stop_event, ms) == ETIMEDOUT)
		obs_output_actual_start(output);

	if (os_event_try(output->reconnect_stop_event) == EAGAIN)
		pthread_detach(output->reconnect_thread);
	else
		os_atomic_set_bool(&output->reconnecting, false);

	output->reconnect_thread_active = false;
	return NULL;
}