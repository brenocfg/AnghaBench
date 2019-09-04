#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int tx_first_dbc; int tx_dbc_interval; int /*<<< orphan*/  flags; } ;
struct snd_efw {int firmware_version; TYPE_1__ rx_stream; TYPE_1__ tx_stream; scalar_t__ is_af9; scalar_t__ is_fireworks3; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIP_DBC_IS_END_EVENT ; 
 int /*<<< orphan*/  CIP_EMPTY_WITH_TAG0 ; 
 int /*<<< orphan*/  CIP_SKIP_DBC_ZERO_CHECK ; 
 int /*<<< orphan*/  CIP_WRONG_DBS ; 
 int /*<<< orphan*/  SND_EFW_TRANSPORT_MODE_IEC61883 ; 
 int /*<<< orphan*/  destroy_stream (struct snd_efw*,TYPE_1__*) ; 
 int init_stream (struct snd_efw*,TYPE_1__*) ; 
 int snd_efw_command_set_tx_mode (struct snd_efw*,int /*<<< orphan*/ ) ; 

int snd_efw_stream_init_duplex(struct snd_efw *efw)
{
	int err;

	err = init_stream(efw, &efw->tx_stream);
	if (err < 0)
		goto end;
	/* Fireworks transmits NODATA packets with TAG0. */
	efw->tx_stream.flags |= CIP_EMPTY_WITH_TAG0;
	/* Fireworks has its own meaning for dbc. */
	efw->tx_stream.flags |= CIP_DBC_IS_END_EVENT;
	/* Fireworks reset dbc at bus reset. */
	efw->tx_stream.flags |= CIP_SKIP_DBC_ZERO_CHECK;
	/*
	 * But Recent firmwares starts packets with non-zero dbc.
	 * Driver version 5.7.6 installs firmware version 5.7.3.
	 */
	if (efw->is_fireworks3 &&
	    (efw->firmware_version == 0x5070000 ||
	     efw->firmware_version == 0x5070300 ||
	     efw->firmware_version == 0x5080000))
		efw->tx_stream.tx_first_dbc = 0x02;
	/* AudioFire9 always reports wrong dbs. */
	if (efw->is_af9)
		efw->tx_stream.flags |= CIP_WRONG_DBS;
	/* Firmware version 5.5 reports fixed interval for dbc. */
	if (efw->firmware_version == 0x5050000)
		efw->tx_stream.tx_dbc_interval = 8;

	err = init_stream(efw, &efw->rx_stream);
	if (err < 0) {
		destroy_stream(efw, &efw->tx_stream);
		goto end;
	}

	/* set IEC61883 compliant mode (actually not fully compliant...) */
	err = snd_efw_command_set_tx_mode(efw, SND_EFW_TRANSPORT_MODE_IEC61883);
	if (err < 0) {
		destroy_stream(efw, &efw->tx_stream);
		destroy_stream(efw, &efw->rx_stream);
	}
end:
	return err;
}