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
typedef  int /*<<< orphan*/  int_fast32_t ;

/* Variables and functions */
 int /*<<< orphan*/  pa_threaded_mainloop_new () ; 
 int /*<<< orphan*/  pa_threaded_mainloop_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pulseaudio_init_context () ; 
 int /*<<< orphan*/  pulseaudio_mainloop ; 
 int /*<<< orphan*/  pulseaudio_mutex ; 
 scalar_t__ pulseaudio_refs ; 

int_fast32_t pulseaudio_init()
{
	pthread_mutex_lock(&pulseaudio_mutex);

	if (pulseaudio_refs == 0) {
		pulseaudio_mainloop = pa_threaded_mainloop_new();
		pa_threaded_mainloop_start(pulseaudio_mainloop);

		pulseaudio_init_context();
	}

	pulseaudio_refs++;

	pthread_mutex_unlock(&pulseaudio_mutex);

	return 0;
}