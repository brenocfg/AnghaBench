#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_6__ {int channel; } ;
struct snd_motu {TYPE_3__ tx_resources; TYPE_3__ rx_resources; int /*<<< orphan*/  unit; int /*<<< orphan*/  tx_stream; int /*<<< orphan*/  rx_stream; int /*<<< orphan*/  tx_packet_formats; TYPE_1__* spec; int /*<<< orphan*/  rx_packet_formats; } ;
typedef  int /*<<< orphan*/  reg ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_5__ {int /*<<< orphan*/  max_speed; } ;
struct TYPE_4__ {int flags; } ;

/* Variables and functions */
 int CHANGE_RX_ISOC_COMM_STATE ; 
 int CHANGE_TX_ISOC_COMM_STATE ; 
 int ISOC_COMM_CONTROL_MASK ; 
 int /*<<< orphan*/  ISOC_COMM_CONTROL_OFFSET ; 
 int RX_ISOC_COMM_CHANNEL_SHIFT ; 
 int RX_ISOC_COMM_IS_ACTIVATED ; 
 int SND_MOTU_SPEC_RX_MIDI_2ND_Q ; 
 int SND_MOTU_SPEC_RX_MIDI_3RD_Q ; 
 int SND_MOTU_SPEC_TX_MIDI_2ND_Q ; 
 int SND_MOTU_SPEC_TX_MIDI_3RD_Q ; 
 int TX_ISOC_COMM_CHANNEL_SHIFT ; 
 int TX_ISOC_COMM_IS_ACTIVATED ; 
 int amdtp_motu_set_parameters (int /*<<< orphan*/ *,unsigned int,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  amdtp_stream_get_max_payload (int /*<<< orphan*/ *) ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 int fw_iso_resources_allocate (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* fw_parent_device (int /*<<< orphan*/ ) ; 
 int snd_motu_transaction_read (struct snd_motu*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int snd_motu_transaction_write (struct snd_motu*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int start_both_streams(struct snd_motu *motu, unsigned int rate)
{
	unsigned int midi_ports = 0;
	__be32 reg;
	u32 data;
	int err;

	if ((motu->spec->flags & SND_MOTU_SPEC_RX_MIDI_2ND_Q) ||
	    (motu->spec->flags & SND_MOTU_SPEC_RX_MIDI_3RD_Q))
		midi_ports = 1;

	/* Set packet formation to our packet streaming engine. */
	err = amdtp_motu_set_parameters(&motu->rx_stream, rate, midi_ports,
					&motu->rx_packet_formats);
	if (err < 0)
		return err;

	if ((motu->spec->flags & SND_MOTU_SPEC_TX_MIDI_2ND_Q) ||
	    (motu->spec->flags & SND_MOTU_SPEC_TX_MIDI_3RD_Q))
		midi_ports = 1;
	else
		midi_ports = 0;

	err = amdtp_motu_set_parameters(&motu->tx_stream, rate, midi_ports,
					&motu->tx_packet_formats);
	if (err < 0)
		return err;

	/* Get isochronous resources on the bus. */
	err = fw_iso_resources_allocate(&motu->rx_resources,
				amdtp_stream_get_max_payload(&motu->rx_stream),
				fw_parent_device(motu->unit)->max_speed);
	if (err < 0)
		return err;

	err = fw_iso_resources_allocate(&motu->tx_resources,
				amdtp_stream_get_max_payload(&motu->tx_stream),
				fw_parent_device(motu->unit)->max_speed);
	if (err < 0)
		return err;

	/* Configure the unit to start isochronous communication. */
	err = snd_motu_transaction_read(motu, ISOC_COMM_CONTROL_OFFSET, &reg,
					sizeof(reg));
	if (err < 0)
		return err;
	data = be32_to_cpu(reg) & ~ISOC_COMM_CONTROL_MASK;

	data |= CHANGE_RX_ISOC_COMM_STATE | RX_ISOC_COMM_IS_ACTIVATED |
		(motu->rx_resources.channel << RX_ISOC_COMM_CHANNEL_SHIFT) |
		CHANGE_TX_ISOC_COMM_STATE | TX_ISOC_COMM_IS_ACTIVATED |
		(motu->tx_resources.channel << TX_ISOC_COMM_CHANNEL_SHIFT);

	reg = cpu_to_be32(data);
	return snd_motu_transaction_write(motu, ISOC_COMM_CONTROL_OFFSET, &reg,
					  sizeof(reg));
}