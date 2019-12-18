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
struct snd_tscm {int /*<<< orphan*/  tx_stream; int /*<<< orphan*/  rx_stream; } ;
struct snd_pcm_substream {TYPE_2__* runtime; struct snd_tscm* private_data; } ;
typedef  enum snd_tscm_clock { ____Placeholder_snd_tscm_clock } snd_tscm_clock ;
struct TYPE_3__ {unsigned int rate_min; unsigned int rate_max; } ;
struct TYPE_4__ {TYPE_1__ hw; } ;

/* Variables and functions */
 int SND_TSCM_CLOCK_INTERNAL ; 
 scalar_t__ amdtp_stream_pcm_running (int /*<<< orphan*/ *) ; 
 int pcm_init_hw_params (struct snd_tscm*,struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_pcm_set_sync (struct snd_pcm_substream*) ; 
 int snd_tscm_stream_get_clock (struct snd_tscm*,int*) ; 
 int snd_tscm_stream_get_rate (struct snd_tscm*,unsigned int*) ; 
 int /*<<< orphan*/  snd_tscm_stream_lock_release (struct snd_tscm*) ; 
 int snd_tscm_stream_lock_try (struct snd_tscm*) ; 

__attribute__((used)) static int pcm_open(struct snd_pcm_substream *substream)
{
	struct snd_tscm *tscm = substream->private_data;
	enum snd_tscm_clock clock;
	unsigned int rate;
	int err;

	err = snd_tscm_stream_lock_try(tscm);
	if (err < 0)
		goto end;

	err = pcm_init_hw_params(tscm, substream);
	if (err < 0)
		goto err_locked;

	err = snd_tscm_stream_get_clock(tscm, &clock);
	if (err < 0)
		goto err_locked;

	if (clock != SND_TSCM_CLOCK_INTERNAL ||
	    amdtp_stream_pcm_running(&tscm->rx_stream) ||
	    amdtp_stream_pcm_running(&tscm->tx_stream)) {
		err = snd_tscm_stream_get_rate(tscm, &rate);
		if (err < 0)
			goto err_locked;
		substream->runtime->hw.rate_min = rate;
		substream->runtime->hw.rate_max = rate;
	}

	snd_pcm_set_sync(substream);
end:
	return err;
err_locked:
	snd_tscm_stream_lock_release(tscm);
	return err;
}