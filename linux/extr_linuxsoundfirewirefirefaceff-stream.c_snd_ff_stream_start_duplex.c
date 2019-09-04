#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  channel; } ;
struct TYPE_6__ {int /*<<< orphan*/  channel; } ;
struct snd_ff {scalar_t__ substreams_counter; int /*<<< orphan*/  rx_stream; int /*<<< orphan*/  tx_stream; int /*<<< orphan*/  unit; TYPE_4__ tx_resources; TYPE_3__* spec; TYPE_1__ rx_resources; } ;
typedef  enum snd_ff_clock_src { ____Placeholder_snd_ff_clock_src } snd_ff_clock_src ;
struct TYPE_10__ {int /*<<< orphan*/  max_speed; } ;
struct TYPE_8__ {TYPE_2__* protocol; } ;
struct TYPE_7__ {int (* get_clock ) (struct snd_ff*,unsigned int*,int*) ;int (* begin_session ) (struct snd_ff*,unsigned int) ;int (* switch_fetching_mode ) (struct snd_ff*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CALLBACK_TIMEOUT_MS ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  amdtp_stream_running (int /*<<< orphan*/ *) ; 
 int amdtp_stream_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdtp_stream_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  amdtp_stream_wait_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ amdtp_streaming_error (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  finish_session (struct snd_ff*) ; 
 TYPE_5__* fw_parent_device (int /*<<< orphan*/ ) ; 
 int keep_resources (struct snd_ff*,unsigned int) ; 
 int /*<<< orphan*/  release_resources (struct snd_ff*) ; 
 int stub1 (struct snd_ff*,unsigned int*,int*) ; 
 int stub2 (struct snd_ff*,unsigned int) ; 
 int stub3 (struct snd_ff*,int) ; 

int snd_ff_stream_start_duplex(struct snd_ff *ff, unsigned int rate)
{
	unsigned int curr_rate;
	enum snd_ff_clock_src src;
	int err;

	if (ff->substreams_counter == 0)
		return 0;

	err = ff->spec->protocol->get_clock(ff, &curr_rate, &src);
	if (err < 0)
		return err;
	if (curr_rate != rate ||
	    amdtp_streaming_error(&ff->tx_stream) ||
	    amdtp_streaming_error(&ff->rx_stream)) {
		finish_session(ff);

		amdtp_stream_stop(&ff->tx_stream);
		amdtp_stream_stop(&ff->rx_stream);

		release_resources(ff);
	}

	/*
	 * Regardless of current source of clock signal, drivers transfer some
	 * packets. Then, the device transfers packets.
	 */
	if (!amdtp_stream_running(&ff->rx_stream)) {
		err = keep_resources(ff, rate);
		if (err < 0)
			goto error;

		err = ff->spec->protocol->begin_session(ff, rate);
		if (err < 0)
			goto error;

		err = amdtp_stream_start(&ff->rx_stream,
					 ff->rx_resources.channel,
					 fw_parent_device(ff->unit)->max_speed);
		if (err < 0)
			goto error;

		if (!amdtp_stream_wait_callback(&ff->rx_stream,
						CALLBACK_TIMEOUT_MS)) {
			err = -ETIMEDOUT;
			goto error;
		}

		err = ff->spec->protocol->switch_fetching_mode(ff, true);
		if (err < 0)
			goto error;
	}

	if (!amdtp_stream_running(&ff->tx_stream)) {
		err = amdtp_stream_start(&ff->tx_stream,
					 ff->tx_resources.channel,
					 fw_parent_device(ff->unit)->max_speed);
		if (err < 0)
			goto error;

		if (!amdtp_stream_wait_callback(&ff->tx_stream,
						CALLBACK_TIMEOUT_MS)) {
			err = -ETIMEDOUT;
			goto error;
		}
	}

	return 0;
error:
	amdtp_stream_stop(&ff->tx_stream);
	amdtp_stream_stop(&ff->rx_stream);

	finish_session(ff);
	release_resources(ff);

	return err;
}