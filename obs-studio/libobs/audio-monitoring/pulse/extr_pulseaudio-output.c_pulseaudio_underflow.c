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
typedef  int /*<<< orphan*/  pa_stream ;
struct TYPE_3__ {int tlength; } ;
struct TYPE_4__ {int /*<<< orphan*/  playback_mutex; TYPE_1__ attr; int /*<<< orphan*/  stream; int /*<<< orphan*/  source; } ;

/* Variables and functions */
 int /*<<< orphan*/  PULSE_DATA (void*) ; 
 int /*<<< orphan*/  UNUSED_PARAMETER (int /*<<< orphan*/ *) ; 
 TYPE_2__* data ; 
 scalar_t__ obs_source_active (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pa_stream_set_buffer_attr (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pulseaudio_signal (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pulseaudio_underflow(pa_stream *p, void *userdata)
{
	UNUSED_PARAMETER(p);
	PULSE_DATA(userdata);

	pthread_mutex_lock(&data->playback_mutex);
	if (obs_source_active(data->source))
		data->attr.tlength = (data->attr.tlength * 3) / 2;

	pa_stream_set_buffer_attr(data->stream, &data->attr, NULL, NULL);
	pthread_mutex_unlock(&data->playback_mutex);

	pulseaudio_signal(0);
}