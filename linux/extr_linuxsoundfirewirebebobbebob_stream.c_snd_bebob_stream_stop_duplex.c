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
struct snd_bebob {scalar_t__ substreams_counter; int /*<<< orphan*/  tx_stream; int /*<<< orphan*/  rx_stream; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdtp_stream_pcm_abort (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  amdtp_stream_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  break_both_connections (struct snd_bebob*) ; 

void snd_bebob_stream_stop_duplex(struct snd_bebob *bebob)
{
	if (bebob->substreams_counter == 0) {
		amdtp_stream_pcm_abort(&bebob->rx_stream);
		amdtp_stream_stop(&bebob->rx_stream);

		amdtp_stream_pcm_abort(&bebob->tx_stream);
		amdtp_stream_stop(&bebob->tx_stream);

		break_both_connections(bebob);
	}
}