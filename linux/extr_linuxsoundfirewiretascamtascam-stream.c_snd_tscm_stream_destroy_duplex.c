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
struct snd_tscm {int /*<<< orphan*/  tx_resources; int /*<<< orphan*/  rx_resources; int /*<<< orphan*/  tx_stream; int /*<<< orphan*/  rx_stream; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdtp_stream_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fw_iso_resources_destroy (int /*<<< orphan*/ *) ; 

void snd_tscm_stream_destroy_duplex(struct snd_tscm *tscm)
{
	amdtp_stream_destroy(&tscm->rx_stream);
	amdtp_stream_destroy(&tscm->tx_stream);

	fw_iso_resources_destroy(&tscm->rx_resources);
	fw_iso_resources_destroy(&tscm->tx_resources);
}