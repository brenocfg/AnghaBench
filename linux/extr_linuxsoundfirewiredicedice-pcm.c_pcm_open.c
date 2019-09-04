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
struct snd_pcm_substream {TYPE_2__* runtime; struct snd_dice* private_data; } ;
struct snd_dice {int /*<<< orphan*/ * rx_stream; int /*<<< orphan*/ * tx_stream; } ;
struct TYPE_3__ {unsigned int rate_min; unsigned int rate_max; } ;
struct TYPE_4__ {TYPE_1__ hw; } ;

/* Variables and functions */
#define  CLOCK_SOURCE_ADAT 135 
#define  CLOCK_SOURCE_AES1 134 
#define  CLOCK_SOURCE_AES2 133 
#define  CLOCK_SOURCE_AES3 132 
#define  CLOCK_SOURCE_AES4 131 
#define  CLOCK_SOURCE_AES_ANY 130 
#define  CLOCK_SOURCE_TDIF 129 
#define  CLOCK_SOURCE_WC 128 
 scalar_t__ amdtp_stream_pcm_running (int /*<<< orphan*/ *) ; 
 int init_hw_info (struct snd_dice*,struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_dice_stream_lock_release (struct snd_dice*) ; 
 int snd_dice_stream_lock_try (struct snd_dice*) ; 
 int snd_dice_transaction_get_clock_source (struct snd_dice*,unsigned int*) ; 
 int snd_dice_transaction_get_rate (struct snd_dice*,unsigned int*) ; 
 int /*<<< orphan*/  snd_pcm_set_sync (struct snd_pcm_substream*) ; 

__attribute__((used)) static int pcm_open(struct snd_pcm_substream *substream)
{
	struct snd_dice *dice = substream->private_data;
	unsigned int source;
	bool internal;
	int err;

	err = snd_dice_stream_lock_try(dice);
	if (err < 0)
		goto end;

	err = init_hw_info(dice, substream);
	if (err < 0)
		goto err_locked;

	err = snd_dice_transaction_get_clock_source(dice, &source);
	if (err < 0)
		goto err_locked;
	switch (source) {
	case CLOCK_SOURCE_AES1:
	case CLOCK_SOURCE_AES2:
	case CLOCK_SOURCE_AES3:
	case CLOCK_SOURCE_AES4:
	case CLOCK_SOURCE_AES_ANY:
	case CLOCK_SOURCE_ADAT:
	case CLOCK_SOURCE_TDIF:
	case CLOCK_SOURCE_WC:
		internal = false;
		break;
	default:
		internal = true;
		break;
	}

	/*
	 * When source of clock is not internal or any PCM streams are running,
	 * available sampling rate is limited at current sampling rate.
	 */
	if (!internal ||
	    amdtp_stream_pcm_running(&dice->tx_stream[0]) ||
	    amdtp_stream_pcm_running(&dice->tx_stream[1]) ||
	    amdtp_stream_pcm_running(&dice->rx_stream[0]) ||
	    amdtp_stream_pcm_running(&dice->rx_stream[1])) {
		unsigned int rate;

		err = snd_dice_transaction_get_rate(dice, &rate);
		if (err < 0)
			goto err_locked;
		substream->runtime->hw.rate_min = rate;
		substream->runtime->hw.rate_max = rate;
	}

	snd_pcm_set_sync(substream);
end:
	return err;
err_locked:
	snd_dice_stream_lock_release(dice);
	return err;
}