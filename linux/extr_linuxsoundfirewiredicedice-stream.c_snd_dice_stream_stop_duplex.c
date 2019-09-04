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
struct snd_dice {scalar_t__ substreams_counter; } ;
struct reg_params {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDTP_IN_STREAM ; 
 int /*<<< orphan*/  AMDTP_OUT_STREAM ; 
 scalar_t__ get_register_params (struct snd_dice*,struct reg_params*,struct reg_params*) ; 
 int /*<<< orphan*/  release_resources (struct snd_dice*) ; 
 int /*<<< orphan*/  snd_dice_transaction_clear_enable (struct snd_dice*) ; 
 int /*<<< orphan*/  stop_streams (struct snd_dice*,int /*<<< orphan*/ ,struct reg_params*) ; 

void snd_dice_stream_stop_duplex(struct snd_dice *dice)
{
	struct reg_params tx_params, rx_params;

	if (dice->substreams_counter > 0)
		return;

	snd_dice_transaction_clear_enable(dice);

	if (get_register_params(dice, &tx_params, &rx_params) == 0) {
		stop_streams(dice, AMDTP_IN_STREAM, &tx_params);
		stop_streams(dice, AMDTP_OUT_STREAM, &rx_params);
	}

	release_resources(dice);
}