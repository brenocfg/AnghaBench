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
struct snd_pcm_substream {TYPE_1__* runtime; struct snd_oxfw* private_data; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct snd_oxfw {int /*<<< orphan*/  mutex; int /*<<< orphan*/  substreams_count; int /*<<< orphan*/  rx_stream; } ;
struct TYPE_4__ {scalar_t__ state; } ;
struct TYPE_3__ {TYPE_2__* status; } ;

/* Variables and functions */
 scalar_t__ SNDRV_PCM_STATE_OPEN ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  params_buffer_bytes (struct snd_pcm_hw_params*) ; 
 unsigned int params_channels (struct snd_pcm_hw_params*) ; 
 unsigned int params_rate (struct snd_pcm_hw_params*) ; 
 int snd_oxfw_stream_reserve_duplex (struct snd_oxfw*,int /*<<< orphan*/ *,unsigned int,unsigned int) ; 
 int snd_pcm_lib_alloc_vmalloc_buffer (struct snd_pcm_substream*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pcm_playback_hw_params(struct snd_pcm_substream *substream,
				  struct snd_pcm_hw_params *hw_params)
{
	struct snd_oxfw *oxfw = substream->private_data;
	int err;

	err = snd_pcm_lib_alloc_vmalloc_buffer(substream,
					       params_buffer_bytes(hw_params));
	if (err < 0)
		return err;

	if (substream->runtime->status->state == SNDRV_PCM_STATE_OPEN) {
		unsigned int rate = params_rate(hw_params);
		unsigned int channels = params_channels(hw_params);

		mutex_lock(&oxfw->mutex);
		err = snd_oxfw_stream_reserve_duplex(oxfw, &oxfw->rx_stream,
						     rate, channels);
		if (err >= 0)
			++oxfw->substreams_count;
		mutex_unlock(&oxfw->mutex);
	}

	return 0;
}