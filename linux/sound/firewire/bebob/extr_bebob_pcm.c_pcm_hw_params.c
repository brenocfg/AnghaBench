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
struct snd_pcm_substream {TYPE_2__* runtime; struct snd_bebob* private_data; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct snd_bebob {int /*<<< orphan*/  mutex; int /*<<< orphan*/  substreams_counter; } ;
struct TYPE_4__ {TYPE_1__* status; } ;
struct TYPE_3__ {scalar_t__ state; } ;

/* Variables and functions */
 scalar_t__ SNDRV_PCM_STATE_OPEN ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  params_buffer_bytes (struct snd_pcm_hw_params*) ; 
 unsigned int params_rate (struct snd_pcm_hw_params*) ; 
 int snd_bebob_stream_reserve_duplex (struct snd_bebob*,unsigned int) ; 
 int snd_pcm_lib_alloc_vmalloc_buffer (struct snd_pcm_substream*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pcm_hw_params(struct snd_pcm_substream *substream,
			 struct snd_pcm_hw_params *hw_params)
{
	struct snd_bebob *bebob = substream->private_data;
	int err;

	err = snd_pcm_lib_alloc_vmalloc_buffer(substream,
					       params_buffer_bytes(hw_params));
	if (err < 0)
		return err;

	if (substream->runtime->status->state == SNDRV_PCM_STATE_OPEN) {
		unsigned int rate = params_rate(hw_params);

		mutex_lock(&bebob->mutex);
		err = snd_bebob_stream_reserve_duplex(bebob, rate);
		if (err >= 0)
			++bebob->substreams_counter;
		mutex_unlock(&bebob->mutex);
	}

	return err;
}