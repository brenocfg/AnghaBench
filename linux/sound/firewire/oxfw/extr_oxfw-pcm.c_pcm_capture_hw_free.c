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
struct snd_pcm_substream {TYPE_2__* runtime; struct snd_oxfw* private_data; } ;
struct snd_oxfw {int /*<<< orphan*/  mutex; int /*<<< orphan*/  substreams_count; } ;
struct TYPE_4__ {TYPE_1__* status; } ;
struct TYPE_3__ {scalar_t__ state; } ;

/* Variables and functions */
 scalar_t__ SNDRV_PCM_STATE_OPEN ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_oxfw_stream_stop_duplex (struct snd_oxfw*) ; 
 int snd_pcm_lib_free_vmalloc_buffer (struct snd_pcm_substream*) ; 

__attribute__((used)) static int pcm_capture_hw_free(struct snd_pcm_substream *substream)
{
	struct snd_oxfw *oxfw = substream->private_data;

	mutex_lock(&oxfw->mutex);

	if (substream->runtime->status->state != SNDRV_PCM_STATE_OPEN)
		--oxfw->substreams_count;

	snd_oxfw_stream_stop_duplex(oxfw);

	mutex_unlock(&oxfw->mutex);

	return snd_pcm_lib_free_vmalloc_buffer(substream);
}