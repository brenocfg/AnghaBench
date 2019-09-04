#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct snd_pcm_substream {TYPE_4__* runtime; struct snd_ff* private_data; } ;
struct TYPE_10__ {size_t sfc; } ;
struct snd_ff {TYPE_5__ rx_stream; TYPE_5__ tx_stream; TYPE_2__* spec; } ;
typedef  enum snd_ff_clock_src { ____Placeholder_snd_ff_clock_src } snd_ff_clock_src ;
struct TYPE_8__ {unsigned int rate_min; unsigned int rate_max; } ;
struct TYPE_9__ {TYPE_3__ hw; } ;
struct TYPE_7__ {TYPE_1__* protocol; } ;
struct TYPE_6__ {int (* get_clock ) (struct snd_ff*,unsigned int*,int*) ;} ;

/* Variables and functions */
 int CIP_SFC_COUNT ; 
 int EIO ; 
 int SND_FF_CLOCK_SRC_INTERNAL ; 
 unsigned int* amdtp_rate_table ; 
 scalar_t__ amdtp_stream_pcm_running (TYPE_5__*) ; 
 int pcm_init_hw_params (struct snd_ff*,struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_ff_stream_lock_release (struct snd_ff*) ; 
 int snd_ff_stream_lock_try (struct snd_ff*) ; 
 int /*<<< orphan*/  snd_pcm_set_sync (struct snd_pcm_substream*) ; 
 int stub1 (struct snd_ff*,unsigned int*,int*) ; 

__attribute__((used)) static int pcm_open(struct snd_pcm_substream *substream)
{
	struct snd_ff *ff = substream->private_data;
	unsigned int rate;
	enum snd_ff_clock_src src;
	int i, err;

	err = snd_ff_stream_lock_try(ff);
	if (err < 0)
		return err;

	err = pcm_init_hw_params(ff, substream);
	if (err < 0)
		goto release_lock;

	err = ff->spec->protocol->get_clock(ff, &rate, &src);
	if (err < 0)
		goto release_lock;

	if (src != SND_FF_CLOCK_SRC_INTERNAL) {
		for (i = 0; i < CIP_SFC_COUNT; ++i) {
			if (amdtp_rate_table[i] == rate)
				break;
		}
		/*
		 * The unit is configured at sampling frequency which packet
		 * streaming engine can't support.
		 */
		if (i >= CIP_SFC_COUNT) {
			err = -EIO;
			goto release_lock;
		}

		substream->runtime->hw.rate_min = rate;
		substream->runtime->hw.rate_max = rate;
	} else {
		if (amdtp_stream_pcm_running(&ff->rx_stream) ||
		    amdtp_stream_pcm_running(&ff->tx_stream)) {
			rate = amdtp_rate_table[ff->rx_stream.sfc];
			substream->runtime->hw.rate_min = rate;
			substream->runtime->hw.rate_max = rate;
		}
	}

	snd_pcm_set_sync(substream);

	return 0;

release_lock:
	snd_ff_stream_lock_release(ff);
	return err;
}