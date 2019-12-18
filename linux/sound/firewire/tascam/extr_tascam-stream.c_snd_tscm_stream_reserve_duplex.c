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
struct snd_tscm {scalar_t__ substreams_counter; int /*<<< orphan*/  tx_resources; int /*<<< orphan*/  rx_stream; int /*<<< orphan*/  tx_stream; int /*<<< orphan*/  rx_resources; int /*<<< orphan*/  domain; } ;

/* Variables and functions */
 int /*<<< orphan*/  INT_MAX ; 
 int /*<<< orphan*/  amdtp_domain_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  finish_session (struct snd_tscm*) ; 
 int /*<<< orphan*/  fw_iso_resources_free (int /*<<< orphan*/ *) ; 
 int keep_resources (struct snd_tscm*,unsigned int,int /*<<< orphan*/ *) ; 
 int set_clock (struct snd_tscm*,unsigned int,int /*<<< orphan*/ ) ; 
 int snd_tscm_stream_get_rate (struct snd_tscm*,unsigned int*) ; 

int snd_tscm_stream_reserve_duplex(struct snd_tscm *tscm, unsigned int rate)
{
	unsigned int curr_rate;
	int err;

	err = snd_tscm_stream_get_rate(tscm, &curr_rate);
	if (err < 0)
		return err;

	if (tscm->substreams_counter == 0 || rate != curr_rate) {
		amdtp_domain_stop(&tscm->domain);

		finish_session(tscm);

		fw_iso_resources_free(&tscm->tx_resources);
		fw_iso_resources_free(&tscm->rx_resources);

		err = set_clock(tscm, rate, INT_MAX);
		if (err < 0)
			return err;

		err = keep_resources(tscm, rate, &tscm->tx_stream);
		if (err < 0)
			return err;

		err = keep_resources(tscm, rate, &tscm->rx_stream);
		if (err < 0) {
			fw_iso_resources_free(&tscm->tx_resources);
			return err;
		}
	}

	return 0;
}