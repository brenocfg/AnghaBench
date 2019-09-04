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
struct snd_motu {scalar_t__ capture_substreams; scalar_t__ playback_substreams; int /*<<< orphan*/  rx_stream; int /*<<< orphan*/  tx_stream; } ;

/* Variables and functions */
 scalar_t__ amdtp_stream_running (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stop_both_streams (struct snd_motu*) ; 
 int /*<<< orphan*/  stop_isoc_ctx (struct snd_motu*,int /*<<< orphan*/ *) ; 

void snd_motu_stream_stop_duplex(struct snd_motu *motu)
{
	if (motu->capture_substreams == 0) {
		if (amdtp_stream_running(&motu->tx_stream))
			stop_isoc_ctx(motu, &motu->tx_stream);

		if (motu->playback_substreams == 0) {
			if (amdtp_stream_running(&motu->rx_stream))
				stop_isoc_ctx(motu, &motu->rx_stream);
			stop_both_streams(motu);
		}
	}
}