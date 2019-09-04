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
struct amdtp_stream {int dummy; } ;
struct snd_oxfw {scalar_t__ capture_substreams; scalar_t__ playback_substreams; struct amdtp_stream rx_stream; struct amdtp_stream tx_stream; } ;

/* Variables and functions */
 int /*<<< orphan*/  stop_stream (struct snd_oxfw*,struct amdtp_stream*) ; 

void snd_oxfw_stream_stop_simplex(struct snd_oxfw *oxfw,
				  struct amdtp_stream *stream)
{
	if (((stream == &oxfw->tx_stream) && (oxfw->capture_substreams > 0)) ||
	    ((stream == &oxfw->rx_stream) && (oxfw->playback_substreams > 0)))
		return;

	stop_stream(oxfw, stream);
}