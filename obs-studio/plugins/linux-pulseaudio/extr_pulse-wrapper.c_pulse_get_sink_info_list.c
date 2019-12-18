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
typedef  int /*<<< orphan*/  pa_sink_info_cb_t ;
typedef  int /*<<< orphan*/  pa_operation ;
typedef  int int_fast32_t ;

/* Variables and functions */
 scalar_t__ PA_OPERATION_RUNNING ; 
 int /*<<< orphan*/ * pa_context_get_sink_info_list (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 scalar_t__ pa_operation_get_state (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pa_operation_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pulse_context ; 
 scalar_t__ pulse_context_ready () ; 
 int /*<<< orphan*/  pulse_lock () ; 
 int /*<<< orphan*/  pulse_unlock () ; 
 int /*<<< orphan*/  pulse_wait () ; 

int_fast32_t pulse_get_sink_info_list(pa_sink_info_cb_t cb, void *userdata)
{
	if (pulse_context_ready() < 0)
		return -1;

	pulse_lock();

	pa_operation *op =
		pa_context_get_sink_info_list(pulse_context, cb, userdata);
	if (!op) {
		pulse_unlock();
		return -1;
	}
	while (pa_operation_get_state(op) == PA_OPERATION_RUNNING)
		pulse_wait();
	pa_operation_unref(op);

	pulse_unlock();

	return 0;
}