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
struct snd_dice {scalar_t__ substreams_counter; scalar_t__** tx_pcm_chs; scalar_t__** rx_pcm_chs; int /*<<< orphan*/  domain; int /*<<< orphan*/ * rx_stream; int /*<<< orphan*/ * tx_stream; TYPE_3__* unit; TYPE_4__* rx_resources; TYPE_4__* tx_resources; } ;
struct reg_params {unsigned int count; } ;
typedef  enum snd_dice_rate_mode { ____Placeholder_snd_dice_rate_mode } snd_dice_rate_mode ;
struct TYPE_8__ {unsigned int generation; } ;
struct TYPE_7__ {int /*<<< orphan*/  device; } ;
struct TYPE_6__ {TYPE_1__* card; } ;
struct TYPE_5__ {unsigned int generation; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDTP_IN_STREAM ; 
 int /*<<< orphan*/  AMDTP_OUT_STREAM ; 
 int /*<<< orphan*/  CALLBACK_TIMEOUT ; 
 int EIO ; 
 int ETIMEDOUT ; 
 unsigned int MAX_STREAMS ; 
 int amdtp_domain_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  amdtp_domain_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  amdtp_stream_running (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  amdtp_stream_wait_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ amdtp_streaming_error (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  finish_session (struct snd_dice*,struct reg_params*,struct reg_params*) ; 
 int /*<<< orphan*/  fw_iso_resources_update (TYPE_4__*) ; 
 TYPE_2__* fw_parent_device (TYPE_3__*) ; 
 int get_register_params (struct snd_dice*,struct reg_params*,struct reg_params*) ; 
 int snd_dice_stream_get_rate_mode (struct snd_dice*,unsigned int,int*) ; 
 int snd_dice_transaction_get_rate (struct snd_dice*,unsigned int*) ; 
 int snd_dice_transaction_set_enable (struct snd_dice*) ; 
 int start_streams (struct snd_dice*,int /*<<< orphan*/ ,unsigned int,struct reg_params*) ; 

int snd_dice_stream_start_duplex(struct snd_dice *dice)
{
	unsigned int generation = dice->rx_resources[0].generation;
	struct reg_params tx_params, rx_params;
	unsigned int i;
	unsigned int rate;
	enum snd_dice_rate_mode mode;
	int err;

	if (dice->substreams_counter == 0)
		return -EIO;

	err = get_register_params(dice, &tx_params, &rx_params);
	if (err < 0)
		return err;

	// Check error of packet streaming.
	for (i = 0; i < MAX_STREAMS; ++i) {
		if (amdtp_streaming_error(&dice->tx_stream[i]) ||
		    amdtp_streaming_error(&dice->rx_stream[i])) {
			amdtp_domain_stop(&dice->domain);
			finish_session(dice, &tx_params, &rx_params);
			break;
		}
	}

	if (generation != fw_parent_device(dice->unit)->card->generation) {
		for (i = 0; i < MAX_STREAMS; ++i) {
			if (i < tx_params.count)
				fw_iso_resources_update(dice->tx_resources + i);
			if (i < rx_params.count)
				fw_iso_resources_update(dice->rx_resources + i);
		}
	}

	// Check required streams are running or not.
	err = snd_dice_transaction_get_rate(dice, &rate);
	if (err < 0)
		return err;
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
	if (i < MAX_STREAMS) {
		// Start both streams.
		err = start_streams(dice, AMDTP_IN_STREAM, rate, &tx_params);
		if (err < 0)
			goto error;

		err = start_streams(dice, AMDTP_OUT_STREAM, rate, &rx_params);
		if (err < 0)
			goto error;

		err = snd_dice_transaction_set_enable(dice);
		if (err < 0) {
			dev_err(&dice->unit->device,
				"fail to enable interface\n");
			goto error;
		}

		err = amdtp_domain_start(&dice->domain);
		if (err < 0)
			goto error;

		for (i = 0; i < MAX_STREAMS; i++) {
			if ((i < tx_params.count &&
			    !amdtp_stream_wait_callback(&dice->tx_stream[i],
							CALLBACK_TIMEOUT)) ||
			    (i < rx_params.count &&
			     !amdtp_stream_wait_callback(&dice->rx_stream[i],
							 CALLBACK_TIMEOUT))) {
				err = -ETIMEDOUT;
				goto error;
			}
		}
	}

	return 0;
error:
	amdtp_domain_stop(&dice->domain);
	finish_session(dice, &tx_params, &rx_params);
	return err;
}