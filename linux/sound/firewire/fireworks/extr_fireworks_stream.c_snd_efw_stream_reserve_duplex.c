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
struct snd_efw {scalar_t__ substreams_counter; int /*<<< orphan*/  in_conn; int /*<<< orphan*/  rx_stream; int /*<<< orphan*/  tx_stream; int /*<<< orphan*/  out_conn; int /*<<< orphan*/  domain; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdtp_domain_stop (int /*<<< orphan*/ *) ; 
 int check_connection_used_by_others (struct snd_efw*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmp_connection_break (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmp_connection_release (int /*<<< orphan*/ *) ; 
 int keep_resources (struct snd_efw*,int /*<<< orphan*/ *,unsigned int,unsigned int) ; 
 int snd_efw_command_get_sampling_rate (struct snd_efw*,unsigned int*) ; 
 int snd_efw_command_set_sampling_rate (struct snd_efw*,unsigned int) ; 
 int snd_efw_get_multiplier_mode (unsigned int,unsigned int*) ; 

int snd_efw_stream_reserve_duplex(struct snd_efw *efw, unsigned int rate)
{
	unsigned int curr_rate;
	int err;

	// Considering JACK/FFADO streaming:
	// TODO: This can be removed hwdep functionality becomes popular.
	err = check_connection_used_by_others(efw, &efw->rx_stream);
	if (err < 0)
		return err;

	// stop streams if rate is different.
	err = snd_efw_command_get_sampling_rate(efw, &curr_rate);
	if (err < 0)
		return err;
	if (rate == 0)
		rate = curr_rate;
	if (rate != curr_rate) {
		amdtp_domain_stop(&efw->domain);

		cmp_connection_break(&efw->out_conn);
		cmp_connection_break(&efw->in_conn);

		cmp_connection_release(&efw->out_conn);
		cmp_connection_release(&efw->in_conn);
	}

	if (efw->substreams_counter == 0 || rate != curr_rate) {
		unsigned int mode;

		err = snd_efw_command_set_sampling_rate(efw, rate);
		if (err < 0)
			return err;

		err = snd_efw_get_multiplier_mode(rate, &mode);
		if (err < 0)
			return err;

		err = keep_resources(efw, &efw->tx_stream, rate, mode);
		if (err < 0)
			return err;

		err = keep_resources(efw, &efw->rx_stream, rate, mode);
		if (err < 0) {
			cmp_connection_release(&efw->in_conn);
			return err;
		}
	}

	return 0;
}