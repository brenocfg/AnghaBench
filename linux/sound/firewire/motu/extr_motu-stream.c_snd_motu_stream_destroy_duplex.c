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
struct snd_motu {scalar_t__ substreams_counter; int /*<<< orphan*/  tx_stream; int /*<<< orphan*/  rx_stream; int /*<<< orphan*/  domain; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdtp_domain_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_stream (struct snd_motu*,int /*<<< orphan*/ *) ; 

void snd_motu_stream_destroy_duplex(struct snd_motu *motu)
{
	amdtp_domain_destroy(&motu->domain);

	destroy_stream(motu, &motu->rx_stream);
	destroy_stream(motu, &motu->tx_stream);

	motu->substreams_counter = 0;
}