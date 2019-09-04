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
struct TYPE_5__ {int /*<<< orphan*/  channel; } ;
struct TYPE_4__ {int /*<<< orphan*/  channel; } ;
struct snd_tscm {scalar_t__ substreams_counter; int /*<<< orphan*/  tx_stream; int /*<<< orphan*/  rx_stream; int /*<<< orphan*/  unit; TYPE_2__ tx_resources; TYPE_1__ rx_resources; } ;
struct TYPE_6__ {int /*<<< orphan*/  max_speed; } ;

/* Variables and functions */
 int /*<<< orphan*/  CALLBACK_TIMEOUT ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  amdtp_stream_running (int /*<<< orphan*/ *) ; 
 int amdtp_stream_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdtp_stream_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  amdtp_stream_wait_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ amdtp_streaming_error (int /*<<< orphan*/ *) ; 
 int begin_session (struct snd_tscm*) ; 
 int /*<<< orphan*/  finish_session (struct snd_tscm*) ; 
 TYPE_3__* fw_parent_device (int /*<<< orphan*/ ) ; 
 int keep_resources (struct snd_tscm*,unsigned int) ; 
 int /*<<< orphan*/  release_resources (struct snd_tscm*) ; 
 int set_stream_formats (struct snd_tscm*,unsigned int) ; 
 int snd_tscm_stream_get_rate (struct snd_tscm*,unsigned int*) ; 

int snd_tscm_stream_start_duplex(struct snd_tscm *tscm, unsigned int rate)
{
	unsigned int curr_rate;
	int err;

	if (tscm->substreams_counter == 0)
		return 0;

	err = snd_tscm_stream_get_rate(tscm, &curr_rate);
	if (err < 0)
		return err;
	if (curr_rate != rate ||
	    amdtp_streaming_error(&tscm->rx_stream) ||
	    amdtp_streaming_error(&tscm->tx_stream)) {
		finish_session(tscm);

		amdtp_stream_stop(&tscm->rx_stream);
		amdtp_stream_stop(&tscm->tx_stream);

		release_resources(tscm);
	}

	if (!amdtp_stream_running(&tscm->rx_stream)) {
		err = keep_resources(tscm, rate);
		if (err < 0)
			goto error;

		err = set_stream_formats(tscm, rate);
		if (err < 0)
			goto error;

		err = begin_session(tscm);
		if (err < 0)
			goto error;

		err = amdtp_stream_start(&tscm->rx_stream,
				tscm->rx_resources.channel,
				fw_parent_device(tscm->unit)->max_speed);
		if (err < 0)
			goto error;

		if (!amdtp_stream_wait_callback(&tscm->rx_stream,
						CALLBACK_TIMEOUT)) {
			err = -ETIMEDOUT;
			goto error;
		}
	}

	if (!amdtp_stream_running(&tscm->tx_stream)) {
		err = amdtp_stream_start(&tscm->tx_stream,
				tscm->tx_resources.channel,
				fw_parent_device(tscm->unit)->max_speed);
		if (err < 0)
			goto error;

		if (!amdtp_stream_wait_callback(&tscm->tx_stream,
						CALLBACK_TIMEOUT)) {
			err = -ETIMEDOUT;
			goto error;
		}
	}

	return 0;
error:
	amdtp_stream_stop(&tscm->rx_stream);
	amdtp_stream_stop(&tscm->tx_stream);

	finish_session(tscm);
	release_resources(tscm);

	return err;
}