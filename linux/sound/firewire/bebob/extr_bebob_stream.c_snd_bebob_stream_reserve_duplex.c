#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct snd_bebob {scalar_t__ substreams_counter; int /*<<< orphan*/  out_conn; int /*<<< orphan*/  rx_stream; int /*<<< orphan*/  tx_stream; TYPE_3__* unit; TYPE_2__* spec; int /*<<< orphan*/  in_conn; int /*<<< orphan*/  domain; } ;
struct TYPE_6__ {int /*<<< orphan*/  device; } ;
struct TYPE_5__ {TYPE_1__* rate; } ;
struct TYPE_4__ {int (* get ) (struct snd_bebob*,unsigned int*) ;int (* set ) (struct snd_bebob*,unsigned int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  amdtp_domain_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  break_both_connections (struct snd_bebob*) ; 
 int check_connection_used_by_others (struct snd_bebob*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmp_connection_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int get_formation_index (unsigned int,unsigned int*) ; 
 int keep_resources (struct snd_bebob*,int /*<<< orphan*/ *,unsigned int,unsigned int) ; 
 int stub1 (struct snd_bebob*,unsigned int*) ; 
 int stub2 (struct snd_bebob*,unsigned int) ; 

int snd_bebob_stream_reserve_duplex(struct snd_bebob *bebob, unsigned int rate)
{
	unsigned int curr_rate;
	int err;

	// Considering JACK/FFADO streaming:
	// TODO: This can be removed hwdep functionality becomes popular.
	err = check_connection_used_by_others(bebob, &bebob->rx_stream);
	if (err < 0)
		return err;

	err = bebob->spec->rate->get(bebob, &curr_rate);
	if (err < 0)
		return err;
	if (rate == 0)
		rate = curr_rate;
	if (curr_rate != rate) {
		amdtp_domain_stop(&bebob->domain);
		break_both_connections(bebob);

		cmp_connection_release(&bebob->out_conn);
		cmp_connection_release(&bebob->in_conn);
	}

	if (bebob->substreams_counter == 0 || curr_rate != rate) {
		unsigned int index;

		// NOTE:
		// If establishing connections at first, Yamaha GO46
		// (and maybe Terratec X24) don't generate sound.
		//
		// For firmware customized by M-Audio, refer to next NOTE.
		err = bebob->spec->rate->set(bebob, rate);
		if (err < 0) {
			dev_err(&bebob->unit->device,
				"fail to set sampling rate: %d\n",
				err);
			return err;
		}

		err = get_formation_index(rate, &index);
		if (err < 0)
			return err;

		err = keep_resources(bebob, &bebob->tx_stream, rate, index);
		if (err < 0)
			return err;

		err = keep_resources(bebob, &bebob->rx_stream, rate, index);
		if (err < 0) {
			cmp_connection_release(&bebob->out_conn);
			return err;
		}
	}

	return 0;
}