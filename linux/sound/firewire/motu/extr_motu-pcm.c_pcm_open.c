#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct snd_pcm_substream {TYPE_3__* runtime; struct snd_motu* private_data; } ;
struct snd_motu_protocol {int (* get_clock_source ) (struct snd_motu*,int*) ;int (* get_clock_rate ) (struct snd_motu*,unsigned int*) ;} ;
struct snd_motu {int /*<<< orphan*/  mutex; int /*<<< orphan*/  rx_stream; int /*<<< orphan*/  tx_stream; TYPE_1__* spec; } ;
typedef  enum snd_motu_clock_source { ____Placeholder_snd_motu_clock_source } snd_motu_clock_source ;
struct TYPE_5__ {unsigned int rate_min; unsigned int rate_max; } ;
struct TYPE_6__ {TYPE_2__ hw; } ;
struct TYPE_4__ {struct snd_motu_protocol* protocol; } ;

/* Variables and functions */
 int SND_MOTU_CLOCK_SOURCE_INTERNAL ; 
 scalar_t__ amdtp_stream_pcm_running (int /*<<< orphan*/ *) ; 
 int init_hw_info (struct snd_motu*,struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int snd_motu_stream_cache_packet_formats (struct snd_motu*) ; 
 int /*<<< orphan*/  snd_motu_stream_lock_release (struct snd_motu*) ; 
 int snd_motu_stream_lock_try (struct snd_motu*) ; 
 int /*<<< orphan*/  snd_pcm_set_sync (struct snd_pcm_substream*) ; 
 int stub1 (struct snd_motu*,int*) ; 
 int stub2 (struct snd_motu*,unsigned int*) ; 

__attribute__((used)) static int pcm_open(struct snd_pcm_substream *substream)
{
	struct snd_motu *motu = substream->private_data;
	const struct snd_motu_protocol *const protocol = motu->spec->protocol;
	enum snd_motu_clock_source src;
	unsigned int rate;
	int err;

	err = snd_motu_stream_lock_try(motu);
	if (err < 0)
		return err;

	mutex_lock(&motu->mutex);

	err = snd_motu_stream_cache_packet_formats(motu);
	if (err < 0)
		goto err_locked;

	err = init_hw_info(motu, substream);
	if (err < 0)
		goto err_locked;

	/*
	 * When source of clock is not internal or any PCM streams are running,
	 * available sampling rate is limited at current sampling rate.
	 */
	err = protocol->get_clock_source(motu, &src);
	if (err < 0)
		goto err_locked;
	if (src != SND_MOTU_CLOCK_SOURCE_INTERNAL ||
	    amdtp_stream_pcm_running(&motu->tx_stream) ||
	    amdtp_stream_pcm_running(&motu->rx_stream)) {
		err = protocol->get_clock_rate(motu, &rate);
		if (err < 0)
			goto err_locked;
		substream->runtime->hw.rate_min = rate;
		substream->runtime->hw.rate_max = rate;
	}

	snd_pcm_set_sync(substream);

	mutex_unlock(&motu->mutex);

	return err;
err_locked:
	mutex_unlock(&motu->mutex);
	snd_motu_stream_lock_release(motu);
	return err;
}