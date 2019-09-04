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
struct snd_ff {int /*<<< orphan*/  rx_resources; int /*<<< orphan*/  tx_resources; int /*<<< orphan*/  rx_stream; int /*<<< orphan*/  tx_stream; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdtp_stream_pcm_abort (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  amdtp_stream_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fw_iso_resources_update (int /*<<< orphan*/ *) ; 

void snd_ff_stream_update_duplex(struct snd_ff *ff)
{
	/* The device discontinue to transfer packets.  */
	amdtp_stream_pcm_abort(&ff->tx_stream);
	amdtp_stream_stop(&ff->tx_stream);

	amdtp_stream_pcm_abort(&ff->rx_stream);
	amdtp_stream_stop(&ff->rx_stream);

	fw_iso_resources_update(&ff->tx_resources);
	fw_iso_resources_update(&ff->rx_resources);
}