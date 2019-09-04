#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_motu_protocol {int (* get_clock_rate ) (struct snd_motu*,unsigned int*) ;int (* set_clock_rate ) (struct snd_motu*,unsigned int) ;int (* switch_fetching_mode ) (struct snd_motu*,int) ;} ;
struct snd_motu {scalar_t__ capture_substreams; scalar_t__ playback_substreams; int /*<<< orphan*/  rx_stream; TYPE_2__* unit; int /*<<< orphan*/  tx_stream; TYPE_1__* spec; } ;
struct TYPE_4__ {int /*<<< orphan*/  device; } ;
struct TYPE_3__ {struct snd_motu_protocol* protocol; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdtp_stream_running (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  amdtp_stream_stop (int /*<<< orphan*/ *) ; 
 scalar_t__ amdtp_streaming_error (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int ensure_packet_formats (struct snd_motu*) ; 
 int snd_motu_stream_cache_packet_formats (struct snd_motu*) ; 
 int start_both_streams (struct snd_motu*,unsigned int) ; 
 int start_isoc_ctx (struct snd_motu*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stop_both_streams (struct snd_motu*) ; 
 int stub1 (struct snd_motu*,unsigned int*) ; 
 int stub2 (struct snd_motu*,unsigned int) ; 
 int stub3 (struct snd_motu*,int) ; 

int snd_motu_stream_start_duplex(struct snd_motu *motu, unsigned int rate)
{
	const struct snd_motu_protocol *protocol = motu->spec->protocol;
	unsigned int curr_rate;
	int err = 0;

	if (motu->capture_substreams == 0 && motu->playback_substreams == 0)
		return 0;

	/* Some packet queueing errors. */
	if (amdtp_streaming_error(&motu->rx_stream) ||
	    amdtp_streaming_error(&motu->tx_stream)) {
		amdtp_stream_stop(&motu->rx_stream);
		amdtp_stream_stop(&motu->tx_stream);
		stop_both_streams(motu);
	}

	err = snd_motu_stream_cache_packet_formats(motu);
	if (err < 0)
		return err;

	/* Stop stream if rate is different. */
	err = protocol->get_clock_rate(motu, &curr_rate);
	if (err < 0) {
		dev_err(&motu->unit->device,
			"fail to get sampling rate: %d\n", err);
		return err;
	}
	if (rate == 0)
		rate = curr_rate;
	if (rate != curr_rate) {
		amdtp_stream_stop(&motu->rx_stream);
		amdtp_stream_stop(&motu->tx_stream);
		stop_both_streams(motu);
	}

	if (!amdtp_stream_running(&motu->rx_stream)) {
		err = protocol->set_clock_rate(motu, rate);
		if (err < 0) {
			dev_err(&motu->unit->device,
				"fail to set sampling rate: %d\n", err);
			return err;
		}

		err = ensure_packet_formats(motu);
		if (err < 0)
			return err;

		err = start_both_streams(motu, rate);
		if (err < 0) {
			dev_err(&motu->unit->device,
				"fail to start isochronous comm: %d\n", err);
			goto stop_streams;
		}

		err = start_isoc_ctx(motu, &motu->rx_stream);
		if (err < 0) {
			dev_err(&motu->unit->device,
				"fail to start IT context: %d\n", err);
			goto stop_streams;
		}

		err = protocol->switch_fetching_mode(motu, true);
		if (err < 0) {
			dev_err(&motu->unit->device,
				"fail to enable frame fetching: %d\n", err);
			goto stop_streams;
		}
	}

	if (!amdtp_stream_running(&motu->tx_stream) &&
	    motu->capture_substreams > 0) {
		err = start_isoc_ctx(motu, &motu->tx_stream);
		if (err < 0) {
			dev_err(&motu->unit->device,
				"fail to start IR context: %d", err);
			amdtp_stream_stop(&motu->rx_stream);
			goto stop_streams;
		}
	}

	return 0;

stop_streams:
	stop_both_streams(motu);
	return err;
}