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
struct snd_motu {int /*<<< orphan*/  rx_stream; int /*<<< orphan*/  tx_stream; int /*<<< orphan*/  domain; } ;

/* Variables and functions */
 int amdtp_domain_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_stream (struct snd_motu*,int /*<<< orphan*/ *) ; 
 int init_stream (struct snd_motu*,int /*<<< orphan*/ *) ; 

int snd_motu_stream_init_duplex(struct snd_motu *motu)
{
	int err;

	err = init_stream(motu, &motu->tx_stream);
	if (err < 0)
		return err;

	err = init_stream(motu, &motu->rx_stream);
	if (err < 0) {
		destroy_stream(motu, &motu->tx_stream);
		return err;
	}

	err = amdtp_domain_init(&motu->domain);
	if (err < 0) {
		destroy_stream(motu, &motu->tx_stream);
		destroy_stream(motu, &motu->rx_stream);
	}

	return err;
}