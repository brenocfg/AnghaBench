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
 int /*<<< orphan*/ * pulseaudio_context ; 
 int /*<<< orphan*/  pulseaudio_lock () ; 
 int /*<<< orphan*/ * pulseaudio_mainloop ; 
 int /*<<< orphan*/  pulseaudio_mutex ; 
 scalar_t__ pulseaudio_refs ; 
 int /*<<< orphan*/  pulseaudio_unlock () ; 

void pulseaudio_unref()
{
	pthread_mutex_lock(&pulseaudio_mutex);

	if (--pulseaudio_refs == 0) {
		pulseaudio_lock();
		if (pulseaudio_context != NULL) {
			pa_context_disconnect(pulseaudio_context);
			pa_context_unref(pulseaudio_context);
			pulseaudio_context = NULL;
		}
		pulseaudio_unlock();

		if (pulseaudio_mainloop != NULL) {
			pa_threaded_mainloop_stop(pulseaudio_mainloop);
			pa_threaded_mainloop_free(pulseaudio_mainloop);
			pulseaudio_mainloop = NULL;
		}
	}

	pthread_mutex_unlock(&pulseaudio_mutex);
}