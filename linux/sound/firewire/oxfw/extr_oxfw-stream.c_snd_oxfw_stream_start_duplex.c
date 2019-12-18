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
struct snd_oxfw {scalar_t__ substreams_count; int /*<<< orphan*/  out_conn; scalar_t__ has_output; int /*<<< orphan*/  in_conn; int /*<<< orphan*/  domain; int /*<<< orphan*/  tx_stream; int /*<<< orphan*/  rx_stream; TYPE_1__* unit; } ;
struct TYPE_2__ {int /*<<< orphan*/  device; } ;

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
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int start_stream (struct snd_oxfw*,int /*<<< orphan*/ *) ; 

int snd_oxfw_stream_start_duplex(struct snd_oxfw *oxfw)
{
	int err;

	if (oxfw->substreams_count == 0)
		return -EIO;

	if (amdtp_streaming_error(&oxfw->rx_stream) ||
	    amdtp_streaming_error(&oxfw->tx_stream)) {
		amdtp_domain_stop(&oxfw->domain);

		cmp_connection_break(&oxfw->in_conn);
		if (oxfw->has_output)
			cmp_connection_break(&oxfw->out_conn);
	}

	if (!amdtp_stream_running(&oxfw->rx_stream)) {
		err = start_stream(oxfw, &oxfw->rx_stream);
		if (err < 0) {
			dev_err(&oxfw->unit->device,
				"fail to prepare rx stream: %d\n", err);
			goto error;
		}

		if (oxfw->has_output &&
		    !amdtp_stream_running(&oxfw->tx_stream)) {
			err = start_stream(oxfw, &oxfw->tx_stream);
			if (err < 0) {
				dev_err(&oxfw->unit->device,
					"fail to prepare tx stream: %d\n", err);
				goto error;
			}
		}

		err = amdtp_domain_start(&oxfw->domain);
		if (err < 0)
			goto error;

		// Wait first packet.
		if (!amdtp_stream_wait_callback(&oxfw->rx_stream,
						CALLBACK_TIMEOUT)) {
			err = -ETIMEDOUT;
			goto error;
		}

		if (oxfw->has_output) {
			if (!amdtp_stream_wait_callback(&oxfw->tx_stream,
							CALLBACK_TIMEOUT)) {
				err = -ETIMEDOUT;
				goto error;
			}
		}
	}

	return 0;
error:
	amdtp_domain_stop(&oxfw->domain);

	cmp_connection_break(&oxfw->in_conn);
	if (oxfw->has_output)
		cmp_connection_break(&oxfw->out_conn);

	return err;
}