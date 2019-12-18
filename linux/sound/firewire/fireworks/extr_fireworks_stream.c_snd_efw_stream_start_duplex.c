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
struct snd_efw {scalar_t__ substreams_counter; int /*<<< orphan*/  in_conn; int /*<<< orphan*/  out_conn; int /*<<< orphan*/  domain; int /*<<< orphan*/  tx_stream; int /*<<< orphan*/  rx_stream; } ;

/* Variables and functions */
 int /*<<< orphan*/  CALLBACK_TIMEOUT ; 
 int EIO ; 
 int ETIMEDOUT ; 
 int amdtp_domain_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  amdtp_domain_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  amdtp_stream_running (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  amdtp_stream_wait_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ amdtp_streaming_error (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmp_connection_break (int /*<<< orphan*/ *) ; 
 int snd_efw_command_get_sampling_rate (struct snd_efw*,unsigned int*) ; 
 int start_stream (struct snd_efw*,int /*<<< orphan*/ *,unsigned int) ; 

int snd_efw_stream_start_duplex(struct snd_efw *efw)
{
	unsigned int rate;
	int err = 0;

	// Need no substreams.
	if (efw->substreams_counter == 0)
		return -EIO;

	if (amdtp_streaming_error(&efw->rx_stream) ||
	    amdtp_streaming_error(&efw->tx_stream)) {
		amdtp_domain_stop(&efw->domain);
		cmp_connection_break(&efw->out_conn);
		cmp_connection_break(&efw->in_conn);
	}

	err = snd_efw_command_get_sampling_rate(efw, &rate);
	if (err < 0)
		return err;

	if (!amdtp_stream_running(&efw->rx_stream)) {
		err = start_stream(efw, &efw->rx_stream, rate);
		if (err < 0)
			goto error;

		err = start_stream(efw, &efw->tx_stream, rate);
		if (err < 0)
			goto error;

		err = amdtp_domain_start(&efw->domain);
		if (err < 0)
			goto error;

		// Wait first callback.
		if (!amdtp_stream_wait_callback(&efw->rx_stream,
						CALLBACK_TIMEOUT) ||
		    !amdtp_stream_wait_callback(&efw->tx_stream,
						CALLBACK_TIMEOUT)) {
			err = -ETIMEDOUT;
			goto error;
		}
	}

	return 0;
error:
	amdtp_domain_stop(&efw->domain);

	cmp_connection_break(&efw->out_conn);
	cmp_connection_break(&efw->in_conn);

	return err;
}