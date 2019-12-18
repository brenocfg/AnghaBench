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
struct snd_ff {int /*<<< orphan*/  tx_stream; int /*<<< orphan*/  rx_stream; int /*<<< orphan*/  domain; } ;

/* Variables and functions */
 int amdtp_domain_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_stream (struct snd_ff*,int /*<<< orphan*/ *) ; 
 int init_stream (struct snd_ff*,int /*<<< orphan*/ *) ; 

int snd_ff_stream_init_duplex(struct snd_ff *ff)
{
	int err;

	err = init_stream(ff, &ff->rx_stream);
	if (err < 0)
		return err;

	err = init_stream(ff, &ff->tx_stream);
	if (err < 0) {
		destroy_stream(ff, &ff->rx_stream);
		return err;
	}

	err = amdtp_domain_init(&ff->domain);
	if (err < 0) {
		destroy_stream(ff, &ff->rx_stream);
		destroy_stream(ff, &ff->tx_stream);
	}

	return err;
}