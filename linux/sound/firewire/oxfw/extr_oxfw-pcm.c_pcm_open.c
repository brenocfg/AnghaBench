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
struct snd_pcm_substream {struct snd_oxfw* private_data; } ;
struct snd_oxfw {int /*<<< orphan*/  rx_stream; int /*<<< orphan*/  tx_stream; } ;

/* Variables and functions */
 scalar_t__ amdtp_stream_pcm_running (int /*<<< orphan*/ *) ; 
 int init_hw_params (struct snd_oxfw*,struct snd_pcm_substream*) ; 
 int limit_to_current_params (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_oxfw_stream_lock_release (struct snd_oxfw*) ; 
 int snd_oxfw_stream_lock_try (struct snd_oxfw*) ; 
 int /*<<< orphan*/  snd_pcm_set_sync (struct snd_pcm_substream*) ; 

__attribute__((used)) static int pcm_open(struct snd_pcm_substream *substream)
{
	struct snd_oxfw *oxfw = substream->private_data;
	int err;

	err = snd_oxfw_stream_lock_try(oxfw);
	if (err < 0)
		goto end;

	err = init_hw_params(oxfw, substream);
	if (err < 0)
		goto err_locked;

	/*
	 * When any PCM streams are already running, the available sampling
	 * rate is limited at current value.
	 */
	if (amdtp_stream_pcm_running(&oxfw->tx_stream) ||
	    amdtp_stream_pcm_running(&oxfw->rx_stream)) {
		err = limit_to_current_params(substream);
		if (err < 0)
			goto end;
	}

	snd_pcm_set_sync(substream);
end:
	return err;
err_locked:
	snd_oxfw_stream_lock_release(oxfw);
	return err;
}