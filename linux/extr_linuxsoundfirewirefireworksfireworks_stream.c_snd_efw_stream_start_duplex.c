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
struct snd_efw {scalar_t__ playback_substreams; scalar_t__ capture_substreams; int /*<<< orphan*/  rx_stream; TYPE_1__* unit; int /*<<< orphan*/  tx_stream; } ;
struct TYPE_2__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdtp_stream_running (int /*<<< orphan*/ *) ; 
 scalar_t__ amdtp_streaming_error (int /*<<< orphan*/ *) ; 
 int check_connection_used_by_others (struct snd_efw*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int snd_efw_command_get_sampling_rate (struct snd_efw*,unsigned int*) ; 
 int snd_efw_command_set_sampling_rate (struct snd_efw*,unsigned int) ; 
 int start_stream (struct snd_efw*,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  stop_stream (struct snd_efw*,int /*<<< orphan*/ *) ; 

int snd_efw_stream_start_duplex(struct snd_efw *efw, unsigned int rate)
{
	unsigned int curr_rate;
	int err = 0;

	/* Need no substreams */
	if (efw->playback_substreams == 0 && efw->capture_substreams  == 0)
		goto end;

	/*
	 * Considering JACK/FFADO streaming:
	 * TODO: This can be removed hwdep functionality becomes popular.
	 */
	err = check_connection_used_by_others(efw, &efw->rx_stream);
	if (err < 0)
		goto end;

	/* packet queueing error */
	if (amdtp_streaming_error(&efw->tx_stream))
		stop_stream(efw, &efw->tx_stream);
	if (amdtp_streaming_error(&efw->rx_stream))
		stop_stream(efw, &efw->rx_stream);

	/* stop streams if rate is different */
	err = snd_efw_command_get_sampling_rate(efw, &curr_rate);
	if (err < 0)
		goto end;
	if (rate == 0)
		rate = curr_rate;
	if (rate != curr_rate) {
		stop_stream(efw, &efw->tx_stream);
		stop_stream(efw, &efw->rx_stream);
	}

	/* master should be always running */
	if (!amdtp_stream_running(&efw->rx_stream)) {
		err = snd_efw_command_set_sampling_rate(efw, rate);
		if (err < 0)
			goto end;

		err = start_stream(efw, &efw->rx_stream, rate);
		if (err < 0) {
			dev_err(&efw->unit->device,
				"fail to start AMDTP master stream:%d\n", err);
			goto end;
		}
	}

	/* start slave if needed */
	if (efw->capture_substreams > 0 &&
	    !amdtp_stream_running(&efw->tx_stream)) {
		err = start_stream(efw, &efw->tx_stream, rate);
		if (err < 0) {
			dev_err(&efw->unit->device,
				"fail to start AMDTP slave stream:%d\n", err);
			stop_stream(efw, &efw->rx_stream);
		}
	}
end:
	return err;
}