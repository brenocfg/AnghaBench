#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snd_dice {scalar_t__ substreams_counter; scalar_t__** tx_pcm_chs; scalar_t__** rx_pcm_chs; int /*<<< orphan*/ * rx_stream; int /*<<< orphan*/ * tx_stream; TYPE_1__* unit; } ;
typedef  enum snd_dice_rate_mode { ____Placeholder_snd_dice_rate_mode } snd_dice_rate_mode ;
struct TYPE_2__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int EIO ; 
 unsigned int MAX_STREAMS ; 
 int /*<<< orphan*/  amdtp_stream_running (int /*<<< orphan*/ *) ; 
 scalar_t__ amdtp_streaming_error (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int snd_dice_stream_get_rate_mode (struct snd_dice*,unsigned int,int*) ; 
 int snd_dice_transaction_get_rate (struct snd_dice*,unsigned int*) ; 
 int start_duplex_streams (struct snd_dice*,unsigned int) ; 

int snd_dice_stream_start_duplex(struct snd_dice *dice, unsigned int rate)
{
	unsigned int curr_rate;
	unsigned int i;
	enum snd_dice_rate_mode mode;
	int err;

	if (dice->substreams_counter == 0)
		return -EIO;

	/* Check sampling transmission frequency. */
	err = snd_dice_transaction_get_rate(dice, &curr_rate);
	if (err < 0) {
		dev_err(&dice->unit->device,
			"fail to get sampling rate\n");
		return err;
	}
	if (rate == 0)
		rate = curr_rate;
	if (rate != curr_rate)
		goto restart;

	/* Check error of packet streaming. */
	for (i = 0; i < MAX_STREAMS; ++i) {
		if (amdtp_streaming_error(&dice->tx_stream[i]))
			break;
		if (amdtp_streaming_error(&dice->rx_stream[i]))
			break;
	}
	if (i < MAX_STREAMS)
		goto restart;

	/* Check required streams are running or not. */
	err = snd_dice_stream_get_rate_mode(dice, rate, &mode);
	if (err < 0)
		return err;
	for (i = 0; i < MAX_STREAMS; ++i) {
		if (dice->tx_pcm_chs[i][mode] > 0 &&
		    !amdtp_stream_running(&dice->tx_stream[i]))
			break;
		if (dice->rx_pcm_chs[i][mode] > 0 &&
		    !amdtp_stream_running(&dice->rx_stream[i]))
			break;
	}
	if (i < MAX_STREAMS)
		goto restart;

	return 0;
restart:
	return start_duplex_streams(dice, rate);
}