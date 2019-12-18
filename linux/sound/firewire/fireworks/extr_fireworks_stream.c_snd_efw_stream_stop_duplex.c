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
struct snd_efw {scalar_t__ substreams_counter; int /*<<< orphan*/  in_conn; int /*<<< orphan*/  out_conn; int /*<<< orphan*/  domain; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdtp_domain_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmp_connection_break (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmp_connection_release (int /*<<< orphan*/ *) ; 

void snd_efw_stream_stop_duplex(struct snd_efw *efw)
{
	if (efw->substreams_counter == 0) {
		amdtp_domain_stop(&efw->domain);

		cmp_connection_break(&efw->out_conn);
		cmp_connection_break(&efw->in_conn);

		cmp_connection_release(&efw->out_conn);
		cmp_connection_release(&efw->in_conn);
	}
}