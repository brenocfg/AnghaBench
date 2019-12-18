#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_motu_packet_format {int dummy; } ;
struct fw_iso_resources {int dummy; } ;
struct amdtp_stream {int dummy; } ;
struct snd_motu {int /*<<< orphan*/  unit; TYPE_1__* spec; struct snd_motu_packet_format tx_packet_formats; struct fw_iso_resources tx_resources; struct snd_motu_packet_format rx_packet_formats; struct fw_iso_resources rx_resources; struct amdtp_stream rx_stream; } ;
struct TYPE_4__ {int /*<<< orphan*/  max_speed; } ;
struct TYPE_3__ {int flags; } ;

/* Variables and functions */
 int SND_MOTU_SPEC_RX_MIDI_2ND_Q ; 
 int SND_MOTU_SPEC_RX_MIDI_3RD_Q ; 
 int SND_MOTU_SPEC_TX_MIDI_2ND_Q ; 
 int SND_MOTU_SPEC_TX_MIDI_3RD_Q ; 
 int amdtp_motu_set_parameters (struct amdtp_stream*,unsigned int,unsigned int,struct snd_motu_packet_format*) ; 
 int /*<<< orphan*/  amdtp_stream_get_max_payload (struct amdtp_stream*) ; 
 int fw_iso_resources_allocate (struct fw_iso_resources*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* fw_parent_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int keep_resources(struct snd_motu *motu, unsigned int rate,
			  struct amdtp_stream *stream)
{
	struct fw_iso_resources *resources;
	struct snd_motu_packet_format *packet_format;
	unsigned int midi_ports = 0;
	int err;

	if (stream == &motu->rx_stream) {
		resources = &motu->rx_resources;
		packet_format = &motu->rx_packet_formats;

		if ((motu->spec->flags & SND_MOTU_SPEC_RX_MIDI_2ND_Q) ||
		    (motu->spec->flags & SND_MOTU_SPEC_RX_MIDI_3RD_Q))
			midi_ports = 1;
	} else {
		resources = &motu->tx_resources;
		packet_format = &motu->tx_packet_formats;

		if ((motu->spec->flags & SND_MOTU_SPEC_TX_MIDI_2ND_Q) ||
		    (motu->spec->flags & SND_MOTU_SPEC_TX_MIDI_3RD_Q))
			midi_ports = 1;
	}

	err = amdtp_motu_set_parameters(stream, rate, midi_ports,
					packet_format);
	if (err < 0)
		return err;

	return fw_iso_resources_allocate(resources,
				amdtp_stream_get_max_payload(stream),
				fw_parent_device(motu->unit)->max_speed);
}