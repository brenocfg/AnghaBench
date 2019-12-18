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

/* Variables and functions */
 int /*<<< orphan*/  pa_context_disconnect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pa_context_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pa_threaded_mainloop_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pa_threaded_mainloop_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pulse_context ; 
 int /*<<< orphan*/  pulse_lock () ; 
 int /*<<< orphan*/ * pulse_mainloop ; 
 int /*<<< orphan*/  pulse_mutex ; 
 scalar_t__ pulse_refs ; 
 int /*<<< orphan*/  pulse_unlock () ; 

void pulse_unref()
{
	pthread_mutex_lock(&pulse_mutex);

	if (--pulse_refs == 0) {
		pulse_lock();
		if (pulse_context != NULL) {
			pa_context_disconnect(pulse_context);
			pa_context_unref(pulse_context);
			pulse_context = NULL;
		}
		pulse_unlock();

		if (pulse_mainloop != NULL) {
			pa_threaded_mainloop_stop(pulse_mainloop);
			pa_threaded_mainloop_free(pulse_mainloop);
			pulse_mainloop = NULL;
		}
	}

	pthread_mutex_unlock(&pulse_mutex);
}