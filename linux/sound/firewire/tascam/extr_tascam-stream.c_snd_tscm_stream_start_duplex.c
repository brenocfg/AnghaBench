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
struct TYPE_6__ {unsigned int generation; int /*<<< orphan*/  channel; } ;
struct snd_tscm {scalar_t__ substreams_counter; int /*<<< orphan*/  domain; int /*<<< orphan*/  tx_stream; int /*<<< orphan*/  rx_stream; TYPE_3__ tx_resources; TYPE_3__ rx_resources; int /*<<< orphan*/  unit; } ;
struct TYPE_5__ {int max_speed; TYPE_1__* card; } ;
struct TYPE_4__ {unsigned int generation; } ;

/* Variables and functions */
 int /*<<< orphan*/  CALLBACK_TIMEOUT ; 
 int ETIMEDOUT ; 
 int amdtp_domain_add_stream (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int amdtp_domain_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  amdtp_domain_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  amdtp_stream_running (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  amdtp_stream_wait_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ amdtp_streaming_error (int /*<<< orphan*/ *) ; 
 int begin_session (struct snd_tscm*) ; 
 int /*<<< orphan*/  finish_session (struct snd_tscm*) ; 
 int fw_iso_resources_update (TYPE_3__*) ; 
 TYPE_2__* fw_parent_device (int /*<<< orphan*/ ) ; 
 int set_stream_formats (struct snd_tscm*,unsigned int) ; 

int snd_tscm_stream_start_duplex(struct snd_tscm *tscm, unsigned int rate)
{
	unsigned int generation = tscm->rx_resources.generation;
	int err;

	if (tscm->substreams_counter == 0)
		return 0;

	if (amdtp_streaming_error(&tscm->rx_stream) ||
	    amdtp_streaming_error(&tscm->tx_stream)) {
		amdtp_domain_stop(&tscm->domain);
		finish_session(tscm);
	}

	if (generation != fw_parent_device(tscm->unit)->card->generation) {
		err = fw_iso_resources_update(&tscm->tx_resources);
		if (err < 0)
			goto error;

		err = fw_iso_resources_update(&tscm->rx_resources);
		if (err < 0)
			goto error;
	}

	if (!amdtp_stream_running(&tscm->rx_stream)) {
		int spd = fw_parent_device(tscm->unit)->max_speed;

		err = set_stream_formats(tscm, rate);
		if (err < 0)
			goto error;

		err = begin_session(tscm);
		if (err < 0)
			goto error;

		err = amdtp_domain_add_stream(&tscm->domain, &tscm->rx_stream,
					      tscm->rx_resources.channel, spd);
		if (err < 0)
			goto error;

		err = amdtp_domain_add_stream(&tscm->domain, &tscm->tx_stream,
					      tscm->tx_resources.channel, spd);
		if (err < 0)
			goto error;

		err = amdtp_domain_start(&tscm->domain);
		if (err < 0)
			return err;

		if (!amdtp_stream_wait_callback(&tscm->rx_stream,
						CALLBACK_TIMEOUT) ||
		    !amdtp_stream_wait_callback(&tscm->tx_stream,
						CALLBACK_TIMEOUT)) {
			err = -ETIMEDOUT;
			goto error;
		}
	}

	return 0;
error:
	amdtp_domain_stop(&tscm->domain);
	finish_session(tscm);

	return err;
}