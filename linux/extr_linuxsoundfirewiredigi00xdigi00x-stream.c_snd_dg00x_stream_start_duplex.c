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
struct snd_dg00x {scalar_t__ substreams_counter; int /*<<< orphan*/  rx_stream; int /*<<< orphan*/  tx_stream; int /*<<< orphan*/  unit; TYPE_2__ tx_resources; TYPE_1__ rx_resources; } ;
struct TYPE_6__ {int /*<<< orphan*/  max_speed; } ;

/* Variables and functions */
 int /*<<< orphan*/  CALLBACK_TIMEOUT ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  amdtp_stream_running (int /*<<< orphan*/ *) ; 
 int amdtp_stream_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdtp_stream_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  amdtp_stream_wait_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ amdtp_streaming_error (int /*<<< orphan*/ *) ; 
 int begin_session (struct snd_dg00x*) ; 
 int /*<<< orphan*/  finish_session (struct snd_dg00x*) ; 
 TYPE_3__* fw_parent_device (int /*<<< orphan*/ ) ; 
 int keep_resources (struct snd_dg00x*,unsigned int) ; 
 int /*<<< orphan*/  release_resources (struct snd_dg00x*) ; 
 int snd_dg00x_stream_get_local_rate (struct snd_dg00x*,unsigned int*) ; 
 int snd_dg00x_stream_set_local_rate (struct snd_dg00x*,unsigned int) ; 

int snd_dg00x_stream_start_duplex(struct snd_dg00x *dg00x, unsigned int rate)
{
	unsigned int curr_rate;
	int err = 0;

	if (dg00x->substreams_counter == 0)
		goto end;

	/* Check current sampling rate. */
	err = snd_dg00x_stream_get_local_rate(dg00x, &curr_rate);
	if (err < 0)
		goto error;
	if (rate == 0)
		rate = curr_rate;
	if (curr_rate != rate ||
	    amdtp_streaming_error(&dg00x->tx_stream) ||
	    amdtp_streaming_error(&dg00x->rx_stream)) {
		finish_session(dg00x);

		amdtp_stream_stop(&dg00x->tx_stream);
		amdtp_stream_stop(&dg00x->rx_stream);
		release_resources(dg00x);
	}

	/*
	 * No packets are transmitted without receiving packets, reagardless of
	 * which source of clock is used.
	 */
	if (!amdtp_stream_running(&dg00x->rx_stream)) {
		err = snd_dg00x_stream_set_local_rate(dg00x, rate);
		if (err < 0)
			goto error;

		err = keep_resources(dg00x, rate);
		if (err < 0)
			goto error;

		err = begin_session(dg00x);
		if (err < 0)
			goto error;

		err = amdtp_stream_start(&dg00x->rx_stream,
				dg00x->rx_resources.channel,
				fw_parent_device(dg00x->unit)->max_speed);
		if (err < 0)
			goto error;

		if (!amdtp_stream_wait_callback(&dg00x->rx_stream,
					      CALLBACK_TIMEOUT)) {
			err = -ETIMEDOUT;
			goto error;
		}
	}

	/*
	 * The value of SYT field in transmitted packets is always 0x0000. Thus,
	 * duplex streams with timestamp synchronization cannot be built.
	 */
	if (!amdtp_stream_running(&dg00x->tx_stream)) {
		err = amdtp_stream_start(&dg00x->tx_stream,
				dg00x->tx_resources.channel,
				fw_parent_device(dg00x->unit)->max_speed);
		if (err < 0)
			goto error;

		if (!amdtp_stream_wait_callback(&dg00x->tx_stream,
					      CALLBACK_TIMEOUT)) {
			err = -ETIMEDOUT;
			goto error;
		}
	}
end:
	return err;
error:
	finish_session(dg00x);

	amdtp_stream_stop(&dg00x->tx_stream);
	amdtp_stream_stop(&dg00x->rx_stream);
	release_resources(dg00x);

	return err;
}