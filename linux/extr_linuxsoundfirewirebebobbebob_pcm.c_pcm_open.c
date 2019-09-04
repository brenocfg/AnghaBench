#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct snd_pcm_substream {TYPE_4__* runtime; struct snd_bebob* private_data; } ;
struct snd_bebob_rate_spec {int (* get ) (struct snd_bebob*,unsigned int*) ;} ;
struct snd_bebob {TYPE_2__* unit; int /*<<< orphan*/  rx_stream; int /*<<< orphan*/  tx_stream; TYPE_1__* spec; } ;
typedef  enum snd_bebob_clock_type { ____Placeholder_snd_bebob_clock_type } snd_bebob_clock_type ;
struct TYPE_7__ {unsigned int rate_min; unsigned int rate_max; } ;
struct TYPE_8__ {TYPE_3__ hw; } ;
struct TYPE_6__ {int /*<<< orphan*/  device; } ;
struct TYPE_5__ {struct snd_bebob_rate_spec* rate; } ;

/* Variables and functions */
 int SND_BEBOB_CLOCK_TYPE_EXTERNAL ; 
 scalar_t__ amdtp_stream_pcm_running (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int pcm_init_hw_params (struct snd_bebob*,struct snd_pcm_substream*) ; 
 int snd_bebob_stream_get_clock_src (struct snd_bebob*,int*) ; 
 int /*<<< orphan*/  snd_bebob_stream_lock_release (struct snd_bebob*) ; 
 int snd_bebob_stream_lock_try (struct snd_bebob*) ; 
 int /*<<< orphan*/  snd_pcm_set_sync (struct snd_pcm_substream*) ; 
 int stub1 (struct snd_bebob*,unsigned int*) ; 

__attribute__((used)) static int
pcm_open(struct snd_pcm_substream *substream)
{
	struct snd_bebob *bebob = substream->private_data;
	const struct snd_bebob_rate_spec *spec = bebob->spec->rate;
	unsigned int sampling_rate;
	enum snd_bebob_clock_type src;
	int err;

	err = snd_bebob_stream_lock_try(bebob);
	if (err < 0)
		goto end;

	err = pcm_init_hw_params(bebob, substream);
	if (err < 0)
		goto err_locked;

	err = snd_bebob_stream_get_clock_src(bebob, &src);
	if (err < 0)
		goto err_locked;

	/*
	 * When source of clock is internal or any PCM stream are running,
	 * the available sampling rate is limited at current sampling rate.
	 */
	if (src == SND_BEBOB_CLOCK_TYPE_EXTERNAL ||
	    amdtp_stream_pcm_running(&bebob->tx_stream) ||
	    amdtp_stream_pcm_running(&bebob->rx_stream)) {
		err = spec->get(bebob, &sampling_rate);
		if (err < 0) {
			dev_err(&bebob->unit->device,
				"fail to get sampling rate: %d\n", err);
			goto err_locked;
		}

		substream->runtime->hw.rate_min = sampling_rate;
		substream->runtime->hw.rate_max = sampling_rate;
	}

	snd_pcm_set_sync(substream);
end:
	return err;
err_locked:
	snd_bebob_stream_lock_release(bebob);
	return err;
}