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
struct snd_bebob {scalar_t__ substreams_counter; int /*<<< orphan*/  in_conn; int /*<<< orphan*/  out_conn; int /*<<< orphan*/  domain; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdtp_domain_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  break_both_connections (struct snd_bebob*) ; 
 int /*<<< orphan*/  cmp_connection_release (int /*<<< orphan*/ *) ; 

void snd_bebob_stream_stop_duplex(struct snd_bebob *bebob)
{
	if (bebob->substreams_counter == 0) {
		amdtp_domain_stop(&bebob->domain);
		break_both_connections(bebob);

		cmp_connection_release(&bebob->out_conn);
		cmp_connection_release(&bebob->in_conn);
	}
}