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
struct snd_bebob {int /*<<< orphan*/  tx_stream; int /*<<< orphan*/  rx_stream; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdtp_stream_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_both_connections (struct snd_bebob*) ; 

void snd_bebob_stream_destroy_duplex(struct snd_bebob *bebob)
{
	amdtp_stream_destroy(&bebob->rx_stream);
	amdtp_stream_destroy(&bebob->tx_stream);

	destroy_both_connections(bebob);
}