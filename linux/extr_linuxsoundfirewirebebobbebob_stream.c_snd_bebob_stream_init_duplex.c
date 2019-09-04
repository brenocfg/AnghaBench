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
struct TYPE_3__ {int flags; } ;
struct snd_bebob {int version; TYPE_1__ rx_stream; TYPE_1__ tx_stream; int /*<<< orphan*/  unit; scalar_t__ maudio_special_quirk; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDTP_IN_STREAM ; 
 int /*<<< orphan*/  AMDTP_OUT_STREAM ; 
 int /*<<< orphan*/  CIP_BLOCKING ; 
 int CIP_EMPTY_HAS_WRONG_DBC ; 
 int CIP_SKIP_DBC_ZERO_CHECK ; 
 int amdtp_am824_init (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdtp_stream_destroy (TYPE_1__*) ; 
 int /*<<< orphan*/  destroy_both_connections (struct snd_bebob*) ; 
 int init_both_connections (struct snd_bebob*) ; 

int snd_bebob_stream_init_duplex(struct snd_bebob *bebob)
{
	int err;

	err = init_both_connections(bebob);
	if (err < 0)
		goto end;

	err = amdtp_am824_init(&bebob->tx_stream, bebob->unit,
			       AMDTP_IN_STREAM, CIP_BLOCKING);
	if (err < 0) {
		amdtp_stream_destroy(&bebob->tx_stream);
		destroy_both_connections(bebob);
		goto end;
	}

	/*
	 * BeBoB v3 transfers packets with these qurks:
	 *  - In the beginning of streaming, the value of dbc is incremented
	 *    even if no data blocks are transferred.
	 *  - The value of dbc is reset suddenly.
	 */
	if (bebob->version > 2)
		bebob->tx_stream.flags |= CIP_EMPTY_HAS_WRONG_DBC |
					  CIP_SKIP_DBC_ZERO_CHECK;

	/*
	 * At high sampling rate, M-Audio special firmware transmits empty
	 * packet with the value of dbc incremented by 8 but the others are
	 * valid to IEC 61883-1.
	 */
	if (bebob->maudio_special_quirk)
		bebob->tx_stream.flags |= CIP_EMPTY_HAS_WRONG_DBC;

	err = amdtp_am824_init(&bebob->rx_stream, bebob->unit,
			       AMDTP_OUT_STREAM, CIP_BLOCKING);
	if (err < 0) {
		amdtp_stream_destroy(&bebob->tx_stream);
		amdtp_stream_destroy(&bebob->rx_stream);
		destroy_both_connections(bebob);
	}
end:
	return err;
}