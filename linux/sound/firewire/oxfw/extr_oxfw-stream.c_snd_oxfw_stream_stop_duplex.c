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
struct snd_oxfw {scalar_t__ substreams_count; int /*<<< orphan*/  out_conn; scalar_t__ has_output; int /*<<< orphan*/  in_conn; int /*<<< orphan*/  domain; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdtp_domain_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmp_connection_break (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmp_connection_release (int /*<<< orphan*/ *) ; 

void snd_oxfw_stream_stop_duplex(struct snd_oxfw *oxfw)
{
	if (oxfw->substreams_count == 0) {
		amdtp_domain_stop(&oxfw->domain);

		cmp_connection_break(&oxfw->in_conn);
		cmp_connection_release(&oxfw->in_conn);

		if (oxfw->has_output) {
			cmp_connection_break(&oxfw->out_conn);
			cmp_connection_release(&oxfw->out_conn);
		}
	}
}