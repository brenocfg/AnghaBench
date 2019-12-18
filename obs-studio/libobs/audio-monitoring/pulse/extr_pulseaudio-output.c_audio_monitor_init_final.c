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
struct audio_monitor {int /*<<< orphan*/  stream; int /*<<< orphan*/  source; scalar_t__ ignore; } ;

/* Variables and functions */
 int /*<<< orphan*/  obs_source_add_audio_capture_callback (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct audio_monitor*) ; 
 int /*<<< orphan*/  on_audio_playback ; 
 int /*<<< orphan*/  pulseaudio_set_underflow_callback (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  pulseaudio_stream_write ; 
 int /*<<< orphan*/  pulseaudio_underflow ; 
 int /*<<< orphan*/  pulseaudio_write_callback (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static void audio_monitor_init_final(struct audio_monitor *monitor)
{
	if (monitor->ignore)
		return;

	obs_source_add_audio_capture_callback(monitor->source,
					      on_audio_playback, monitor);

	pulseaudio_write_callback(monitor->stream, pulseaudio_stream_write,
				  (void *)monitor);

	pulseaudio_set_underflow_callback(monitor->stream, pulseaudio_underflow,
					  (void *)monitor);
}