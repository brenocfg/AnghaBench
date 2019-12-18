#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pa_stream ;
struct TYPE_2__ {size_t bytesRemaining; int /*<<< orphan*/  playback_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  PULSE_DATA (void*) ; 
 int /*<<< orphan*/  UNUSED_PARAMETER (int /*<<< orphan*/ *) ; 
 TYPE_1__* data ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pulseaudio_signal (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pulseaudio_stream_write(pa_stream *p, size_t nbytes, void *userdata)
{
	UNUSED_PARAMETER(p);
	PULSE_DATA(userdata);

	pthread_mutex_lock(&data->playback_mutex);
	data->bytesRemaining += nbytes;
	pthread_mutex_unlock(&data->playback_mutex);

	pulseaudio_signal(0);
}