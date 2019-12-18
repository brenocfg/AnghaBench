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
struct snd_tscm {int /*<<< orphan*/  rx_stream; int /*<<< orphan*/  tx_stream; int /*<<< orphan*/  domain; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdtp_domain_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  amdtp_stream_pcm_abort (int /*<<< orphan*/ *) ; 

void snd_tscm_stream_update_duplex(struct snd_tscm *tscm)
{
	amdtp_domain_stop(&tscm->domain);

	amdtp_stream_pcm_abort(&tscm->tx_stream);
	amdtp_stream_pcm_abort(&tscm->rx_stream);
}