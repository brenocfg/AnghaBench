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
struct snd_efw {int /*<<< orphan*/  tx_stream; int /*<<< orphan*/  rx_stream; int /*<<< orphan*/  in_conn; int /*<<< orphan*/  out_conn; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdtp_stream_update (int /*<<< orphan*/ *) ; 
 scalar_t__ cmp_connection_update (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stop_stream (struct snd_efw*,int /*<<< orphan*/ *) ; 

void snd_efw_stream_update_duplex(struct snd_efw *efw)
{
	if (cmp_connection_update(&efw->out_conn) < 0 ||
	    cmp_connection_update(&efw->in_conn) < 0) {
		stop_stream(efw, &efw->rx_stream);
		stop_stream(efw, &efw->tx_stream);
	} else {
		amdtp_stream_update(&efw->rx_stream);
		amdtp_stream_update(&efw->tx_stream);
	}
}