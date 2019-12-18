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
 int amdtp_domain_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_stream (struct snd_oxfw*,int /*<<< orphan*/ *) ; 
 int init_stream (struct snd_oxfw*,int /*<<< orphan*/ *) ; 

int snd_oxfw_stream_init_duplex(struct snd_oxfw *oxfw)
{
	int err;

	err = init_stream(oxfw, &oxfw->rx_stream);
	if (err < 0)
		return err;

	if (oxfw->has_output) {
		err = init_stream(oxfw, &oxfw->tx_stream);
		if (err < 0) {
			destroy_stream(oxfw, &oxfw->rx_stream);
			return err;
		}
	}

	err = amdtp_domain_init(&oxfw->domain);
	if (err < 0) {
		destroy_stream(oxfw, &oxfw->rx_stream);
		if (oxfw->has_output)
			destroy_stream(oxfw, &oxfw->tx_stream);
	}

	return err;
}