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
struct audio_monitor {int /*<<< orphan*/  device; scalar_t__ stream; int /*<<< orphan*/  new_data; int /*<<< orphan*/  resampler; scalar_t__ source; scalar_t__ ignore; } ;

/* Variables and functions */
 int /*<<< orphan*/  audio_resampler_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  circlebuf_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_source_remove_audio_capture_callback (scalar_t__,int /*<<< orphan*/ ,struct audio_monitor*) ; 
 int /*<<< orphan*/  on_audio_playback ; 
 int /*<<< orphan*/  pulseaudio_stop_playback (struct audio_monitor*) ; 
 int /*<<< orphan*/  pulseaudio_unref () ; 

__attribute__((used)) static inline void audio_monitor_free(struct audio_monitor *monitor)
{
	if (monitor->ignore)
		return;

	if (monitor->source)
		obs_source_remove_audio_capture_callback(
			monitor->source, on_audio_playback, monitor);

	audio_resampler_destroy(monitor->resampler);
	circlebuf_free(&monitor->new_data);

	if (monitor->stream)
		pulseaudio_stop_playback(monitor);
	pulseaudio_unref();

	bfree(monitor->device);
}