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
struct snd_dice {int /*<<< orphan*/ * rx_resources; int /*<<< orphan*/ * tx_resources; int /*<<< orphan*/ * rx_stream; int /*<<< orphan*/ * tx_stream; } ;

/* Variables and functions */
 unsigned int MAX_STREAMS ; 
 int /*<<< orphan*/  amdtp_stream_pcm_abort (int /*<<< orphan*/ *) ; 
 scalar_t__ amdtp_stream_running (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  amdtp_stream_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fw_iso_resources_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void release_resources(struct snd_dice *dice)
{
	unsigned int i;

	for (i = 0; i < MAX_STREAMS; i++) {
		if (amdtp_stream_running(&dice->tx_stream[i])) {
			amdtp_stream_pcm_abort(&dice->tx_stream[i]);
			amdtp_stream_stop(&dice->tx_stream[i]);
		}
		if (amdtp_stream_running(&dice->rx_stream[i])) {
			amdtp_stream_pcm_abort(&dice->rx_stream[i]);
			amdtp_stream_stop(&dice->rx_stream[i]);
		}

		fw_iso_resources_free(&dice->tx_resources[i]);
		fw_iso_resources_free(&dice->rx_resources[i]);
	}
}