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
struct snd_tscm {scalar_t__ substreams_counter; int /*<<< orphan*/  rx_resources; int /*<<< orphan*/  tx_resources; int /*<<< orphan*/  domain; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdtp_domain_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  finish_session (struct snd_tscm*) ; 
 int /*<<< orphan*/  fw_iso_resources_free (int /*<<< orphan*/ *) ; 

void snd_tscm_stream_stop_duplex(struct snd_tscm *tscm)
{
	if (tscm->substreams_counter == 0) {
		amdtp_domain_stop(&tscm->domain);
		finish_session(tscm);

		fw_iso_resources_free(&tscm->tx_resources);
		fw_iso_resources_free(&tscm->rx_resources);
	}
}