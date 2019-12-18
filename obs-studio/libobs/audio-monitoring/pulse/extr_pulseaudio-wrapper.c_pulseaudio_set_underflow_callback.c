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
typedef  int /*<<< orphan*/  pa_stream_notify_cb_t ;
typedef  int /*<<< orphan*/  pa_stream ;

/* Variables and functions */
 int /*<<< orphan*/  pa_stream_set_underflow_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 scalar_t__ pulseaudio_context_ready () ; 
 int /*<<< orphan*/  pulseaudio_lock () ; 
 int /*<<< orphan*/  pulseaudio_unlock () ; 

void pulseaudio_set_underflow_callback(pa_stream *p, pa_stream_notify_cb_t cb,
				       void *userdata)
{
	if (pulseaudio_context_ready() < 0)
		return;

	pulseaudio_lock();
	pa_stream_set_underflow_callback(p, cb, userdata);
	pulseaudio_unlock();
}