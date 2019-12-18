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
typedef  int /*<<< orphan*/  pa_proplist ;

/* Variables and functions */
 int /*<<< orphan*/  PA_CONTEXT_NOAUTOSPAWN ; 
 int /*<<< orphan*/  pa_context_connect (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pa_context_new_with_proplist (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pa_context_set_state_callback (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pa_proplist_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pa_threaded_mainloop_get_api (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pulseaudio_context ; 
 int /*<<< orphan*/  pulseaudio_context_state_changed ; 
 int /*<<< orphan*/  pulseaudio_lock () ; 
 int /*<<< orphan*/  pulseaudio_mainloop ; 
 int /*<<< orphan*/ * pulseaudio_properties () ; 
 int /*<<< orphan*/  pulseaudio_unlock () ; 

__attribute__((used)) static void pulseaudio_init_context()
{
	pulseaudio_lock();

	pa_proplist *p = pulseaudio_properties();
	pulseaudio_context = pa_context_new_with_proplist(
		pa_threaded_mainloop_get_api(pulseaudio_mainloop),
		"OBS-Monitor", p);

	pa_context_set_state_callback(pulseaudio_context,
				      pulseaudio_context_state_changed, NULL);

	pa_context_connect(pulseaudio_context, NULL, PA_CONTEXT_NOAUTOSPAWN,
			   NULL);
	pa_proplist_free(p);

	pulseaudio_unlock();
}