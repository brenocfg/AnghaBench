#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int midi_flag_offset; int midi_byte_offset; } ;
struct TYPE_6__ {int midi_flag_offset; int midi_byte_offset; } ;
struct snd_motu {TYPE_4__ rx_packet_formats; TYPE_3__* spec; TYPE_2__ tx_packet_formats; } ;
struct TYPE_7__ {int flags; TYPE_1__* protocol; } ;
struct TYPE_5__ {int (* cache_packet_formats ) (struct snd_motu*) ;} ;

/* Variables and functions */
 int SND_MOTU_SPEC_RX_MIDI_2ND_Q ; 
 int SND_MOTU_SPEC_RX_MIDI_3RD_Q ; 
 int SND_MOTU_SPEC_TX_MIDI_2ND_Q ; 
 int SND_MOTU_SPEC_TX_MIDI_3RD_Q ; 
 int stub1 (struct snd_motu*) ; 

int snd_motu_stream_cache_packet_formats(struct snd_motu *motu)
{
	int err;

	err = motu->spec->protocol->cache_packet_formats(motu);
	if (err < 0)
		return err;

	if (motu->spec->flags & SND_MOTU_SPEC_TX_MIDI_2ND_Q) {
		motu->tx_packet_formats.midi_flag_offset = 4;
		motu->tx_packet_formats.midi_byte_offset = 6;
	} else if (motu->spec->flags & SND_MOTU_SPEC_TX_MIDI_3RD_Q) {
		motu->tx_packet_formats.midi_flag_offset = 8;
		motu->tx_packet_formats.midi_byte_offset = 7;
	}

	if (motu->spec->flags & SND_MOTU_SPEC_RX_MIDI_2ND_Q) {
		motu->rx_packet_formats.midi_flag_offset = 4;
		motu->rx_packet_formats.midi_byte_offset = 6;
	} else if (motu->spec->flags & SND_MOTU_SPEC_RX_MIDI_3RD_Q) {
		motu->rx_packet_formats.midi_flag_offset = 8;
		motu->rx_packet_formats.midi_byte_offset = 7;
	}

	return 0;
}