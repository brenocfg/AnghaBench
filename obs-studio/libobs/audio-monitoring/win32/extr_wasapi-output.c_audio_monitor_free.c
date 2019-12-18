#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct audio_monitor {int /*<<< orphan*/  buf; int /*<<< orphan*/  delay_buffer; int /*<<< orphan*/  resampler; TYPE_2__* render; TYPE_2__* client; TYPE_2__* device; scalar_t__ source; scalar_t__ ignore; } ;
struct TYPE_5__ {TYPE_1__* lpVtbl; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* Stop ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  audio_resampler_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  circlebuf_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  da_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_source_remove_audio_capture_callback (scalar_t__,int /*<<< orphan*/ ,struct audio_monitor*) ; 
 int /*<<< orphan*/  on_audio_playback ; 
 int /*<<< orphan*/  safe_release (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

__attribute__((used)) static inline void audio_monitor_free(struct audio_monitor *monitor)
{
	if (monitor->ignore)
		return;

	if (monitor->source) {
		obs_source_remove_audio_capture_callback(
			monitor->source, on_audio_playback, monitor);
	}

	if (monitor->client)
		monitor->client->lpVtbl->Stop(monitor->client);

	safe_release(monitor->device);
	safe_release(monitor->client);
	safe_release(monitor->render);
	audio_resampler_destroy(monitor->resampler);
	circlebuf_free(&monitor->delay_buffer);
	da_free(monitor->buf);
}