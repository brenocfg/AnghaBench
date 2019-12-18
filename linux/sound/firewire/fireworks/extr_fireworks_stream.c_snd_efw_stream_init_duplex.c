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
struct snd_efw {int /*<<< orphan*/  rx_stream; int /*<<< orphan*/  tx_stream; int /*<<< orphan*/  domain; } ;

/* Variables and functions */
 int /*<<< orphan*/  SND_EFW_TRANSPORT_MODE_IEC61883 ; 
 int amdtp_domain_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_stream (struct snd_efw*,int /*<<< orphan*/ *) ; 
 int init_stream (struct snd_efw*,int /*<<< orphan*/ *) ; 
 int snd_efw_command_set_tx_mode (struct snd_efw*,int /*<<< orphan*/ ) ; 

int snd_efw_stream_init_duplex(struct snd_efw *efw)
{
	int err;

	err = init_stream(efw, &efw->tx_stream);
	if (err < 0)
		return err;

	err = init_stream(efw, &efw->rx_stream);
	if (err < 0) {
		destroy_stream(efw, &efw->tx_stream);
		return err;
	}

	err = amdtp_domain_init(&efw->domain);
	if (err < 0) {
		destroy_stream(efw, &efw->tx_stream);
		destroy_stream(efw, &efw->rx_stream);
		return err;
	}

	// set IEC61883 compliant mode (actually not fully compliant...).
	err = snd_efw_command_set_tx_mode(efw, SND_EFW_TRANSPORT_MODE_IEC61883);
	if (err < 0) {
		destroy_stream(efw, &efw->tx_stream);
		destroy_stream(efw, &efw->rx_stream);
	}

	return err;
}