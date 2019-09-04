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
struct snd_tscm {scalar_t__ substreams_counter; int /*<<< orphan*/  rx_stream; int /*<<< orphan*/  tx_stream; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdtp_stream_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  finish_session (struct snd_tscm*) ; 
 int /*<<< orphan*/  release_resources (struct snd_tscm*) ; 

void snd_tscm_stream_stop_duplex(struct snd_tscm *tscm)
{
	if (tscm->substreams_counter > 0)
		return;

	amdtp_stream_stop(&tscm->tx_stream);
	amdtp_stream_stop(&tscm->rx_stream);

	finish_session(tscm);
	release_resources(tscm);
}