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
struct obs_core_audio {int /*<<< orphan*/  monitoring_mutex; int /*<<< orphan*/  monitoring_device_id; int /*<<< orphan*/  monitoring_device_name; int /*<<< orphan*/  monitors; int /*<<< orphan*/  root_nodes; int /*<<< orphan*/  render_order; int /*<<< orphan*/  buffered_timestamps; scalar_t__ audio; } ;
struct TYPE_2__ {struct obs_core_audio audio; } ;

/* Variables and functions */
 int /*<<< orphan*/  audio_output_close (scalar_t__) ; 
 int /*<<< orphan*/  bfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  circlebuf_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  da_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct obs_core_audio*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* obs ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void obs_free_audio(void)
{
	struct obs_core_audio *audio = &obs->audio;
	if (audio->audio)
		audio_output_close(audio->audio);

	circlebuf_free(&audio->buffered_timestamps);
	da_free(audio->render_order);
	da_free(audio->root_nodes);

	da_free(audio->monitors);
	bfree(audio->monitoring_device_name);
	bfree(audio->monitoring_device_id);
	pthread_mutex_destroy(&audio->monitoring_mutex);

	memset(audio, 0, sizeof(struct obs_core_audio));
}