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
struct snd_pcm_substream {TYPE_2__* runtime; struct snd_dg00x* private_data; } ;
struct snd_dg00x {int /*<<< orphan*/  tx_stream; int /*<<< orphan*/  rx_stream; } ;
typedef  enum snd_dg00x_clock { ____Placeholder_snd_dg00x_clock } snd_dg00x_clock ;
struct TYPE_3__ {unsigned int rate_min; unsigned int rate_max; } ;
struct TYPE_4__ {TYPE_1__ hw; } ;

/* Variables and functions */
 int EBUSY ; 
 int SND_DG00X_CLOCK_INTERNAL ; 
 scalar_t__ amdtp_stream_pcm_running (int /*<<< orphan*/ *) ; 
 int pcm_init_hw_params (struct snd_dg00x*,struct snd_pcm_substream*) ; 
 int snd_dg00x_stream_check_external_clock (struct snd_dg00x*,int*) ; 
 int snd_dg00x_stream_get_clock (struct snd_dg00x*,int*) ; 
 int snd_dg00x_stream_get_external_rate (struct snd_dg00x*,unsigned int*) ; 
 int /*<<< orphan*/  snd_dg00x_stream_lock_release (struct snd_dg00x*) ; 
 int snd_dg00x_stream_lock_try (struct snd_dg00x*) ; 
 int /*<<< orphan*/  snd_pcm_set_sync (struct snd_pcm_substream*) ; 

__attribute__((used)) static int pcm_open(struct snd_pcm_substream *substream)
{
	struct snd_dg00x *dg00x = substream->private_data;
	enum snd_dg00x_clock clock;
	bool detect;
	unsigned int rate;
	int err;

	err = snd_dg00x_stream_lock_try(dg00x);
	if (err < 0)
		goto end;

	err = pcm_init_hw_params(dg00x, substream);
	if (err < 0)
		goto err_locked;

	/* Check current clock source. */
	err = snd_dg00x_stream_get_clock(dg00x, &clock);
	if (err < 0)
		goto err_locked;
	if (clock != SND_DG00X_CLOCK_INTERNAL) {
		err = snd_dg00x_stream_check_external_clock(dg00x, &detect);
		if (err < 0)
			goto err_locked;
		if (!detect) {
			err = -EBUSY;
			goto err_locked;
		}
	}

	if ((clock != SND_DG00X_CLOCK_INTERNAL) ||
	    amdtp_stream_pcm_running(&dg00x->rx_stream) ||
	    amdtp_stream_pcm_running(&dg00x->tx_stream)) {
		err = snd_dg00x_stream_get_external_rate(dg00x, &rate);
		if (err < 0)
			goto err_locked;
		substream->runtime->hw.rate_min = rate;
		substream->runtime->hw.rate_max = rate;
	}

	snd_pcm_set_sync(substream);
end:
	return err;
err_locked:
	snd_dg00x_stream_lock_release(dg00x);
	return err;
}