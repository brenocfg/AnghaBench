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
struct snd_dice {int /*<<< orphan*/ * rx_stream; int /*<<< orphan*/ * tx_stream; TYPE_1__* unit; } ;
struct reg_params {int count; } ;
struct TYPE_2__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDTP_IN_STREAM ; 
 int /*<<< orphan*/  AMDTP_OUT_STREAM ; 
 int /*<<< orphan*/  CALLBACK_TIMEOUT ; 
 int ETIMEDOUT ; 
 int MAX_STREAMS ; 
 int /*<<< orphan*/  amdtp_stream_wait_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int ensure_phase_lock (struct snd_dice*,unsigned int) ; 
 int get_register_params (struct snd_dice*,struct reg_params*,struct reg_params*) ; 
 int /*<<< orphan*/  release_resources (struct snd_dice*) ; 
 int /*<<< orphan*/  snd_dice_transaction_clear_enable (struct snd_dice*) ; 
 int snd_dice_transaction_set_enable (struct snd_dice*) ; 
 int start_streams (struct snd_dice*,int /*<<< orphan*/ ,unsigned int,struct reg_params*) ; 
 int /*<<< orphan*/  stop_streams (struct snd_dice*,int /*<<< orphan*/ ,struct reg_params*) ; 

__attribute__((used)) static int start_duplex_streams(struct snd_dice *dice, unsigned int rate)
{
	struct reg_params tx_params, rx_params;
	int i;
	int err;

	err = get_register_params(dice, &tx_params, &rx_params);
	if (err < 0)
		return err;

	/* Stop transmission. */
	stop_streams(dice, AMDTP_IN_STREAM, &tx_params);
	stop_streams(dice, AMDTP_OUT_STREAM, &rx_params);
	snd_dice_transaction_clear_enable(dice);
	release_resources(dice);

	err = ensure_phase_lock(dice, rate);
	if (err < 0) {
		dev_err(&dice->unit->device, "fail to ensure phase lock\n");
		return err;
	}

	/* Likely to have changed stream formats. */
	err = get_register_params(dice, &tx_params, &rx_params);
	if (err < 0)
		return err;

	/* Start both streams. */
	err = start_streams(dice, AMDTP_IN_STREAM, rate, &tx_params);
	if (err < 0)
		goto error;
	err = start_streams(dice, AMDTP_OUT_STREAM, rate, &rx_params);
	if (err < 0)
		goto error;

	err = snd_dice_transaction_set_enable(dice);
	if (err < 0) {
		dev_err(&dice->unit->device, "fail to enable interface\n");
		goto error;
	}

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

	return 0;
error:
	stop_streams(dice, AMDTP_IN_STREAM, &tx_params);
	stop_streams(dice, AMDTP_OUT_STREAM, &rx_params);
	snd_dice_transaction_clear_enable(dice);
	release_resources(dice);
	return err;
}