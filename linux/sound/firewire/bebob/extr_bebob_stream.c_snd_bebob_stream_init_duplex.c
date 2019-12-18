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
struct snd_bebob {int /*<<< orphan*/  rx_stream; int /*<<< orphan*/  tx_stream; int /*<<< orphan*/  domain; } ;

/* Variables and functions */
 int amdtp_domain_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_stream (struct snd_bebob*,int /*<<< orphan*/ *) ; 
 int init_stream (struct snd_bebob*,int /*<<< orphan*/ *) ; 

int snd_bebob_stream_init_duplex(struct snd_bebob *bebob)
{
	int err;

	err = init_stream(bebob, &bebob->tx_stream);
	if (err < 0)
		return err;

	err = init_stream(bebob, &bebob->rx_stream);
	if (err < 0) {
		destroy_stream(bebob, &bebob->tx_stream);
		return err;
	}

	err = amdtp_domain_init(&bebob->domain);
	if (err < 0) {
		destroy_stream(bebob, &bebob->tx_stream);
		destroy_stream(bebob, &bebob->rx_stream);
	}

	return err;
}