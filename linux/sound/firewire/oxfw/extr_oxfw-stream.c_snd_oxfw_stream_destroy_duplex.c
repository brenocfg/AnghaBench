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
struct snd_oxfw {int /*<<< orphan*/  tx_stream; scalar_t__ has_output; int /*<<< orphan*/  rx_stream; int /*<<< orphan*/  domain; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdtp_domain_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_stream (struct snd_oxfw*,int /*<<< orphan*/ *) ; 

void snd_oxfw_stream_destroy_duplex(struct snd_oxfw *oxfw)
{
	amdtp_domain_destroy(&oxfw->domain);

	destroy_stream(oxfw, &oxfw->rx_stream);

	if (oxfw->has_output)
		destroy_stream(oxfw, &oxfw->tx_stream);
}