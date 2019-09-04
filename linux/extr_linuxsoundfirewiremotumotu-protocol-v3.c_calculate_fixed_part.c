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
struct snd_motu_packet_format {int msg_chunks; void** fixed_part_pcm_chunks; } ;
typedef  enum snd_motu_spec_flags { ____Placeholder_snd_motu_spec_flags } snd_motu_spec_flags ;
typedef  enum amdtp_stream_direction { ____Placeholder_amdtp_stream_direction } amdtp_stream_direction ;

/* Variables and functions */
 int AMDTP_IN_STREAM ; 
 int SND_MOTU_SPEC_HAS_AESEBU_IFACE ; 
 int SND_MOTU_SPEC_RX_SEPARETED_MAIN ; 
 int SND_MOTU_SPEC_SUPPORT_CLOCK_X4 ; 
 int SND_MOTU_SPEC_TX_MICINST_CHUNK ; 
 int SND_MOTU_SPEC_TX_RETURN_CHUNK ; 
 int SND_MOTU_SPEC_TX_REVERB_CHUNK ; 
 void* round_up (int,int) ; 

__attribute__((used)) static void calculate_fixed_part(struct snd_motu_packet_format *formats,
				 enum amdtp_stream_direction dir,
				 enum snd_motu_spec_flags flags,
				 unsigned char analog_ports)
{
	unsigned char pcm_chunks[3] = {0, 0, 0};

	formats->msg_chunks = 2;

	pcm_chunks[0] = analog_ports;
	pcm_chunks[1] = analog_ports;
	if (flags & SND_MOTU_SPEC_SUPPORT_CLOCK_X4)
		pcm_chunks[2] = analog_ports;

	if (dir == AMDTP_IN_STREAM) {
		if (flags & SND_MOTU_SPEC_TX_MICINST_CHUNK) {
			pcm_chunks[0] += 2;
			pcm_chunks[1] += 2;
			if (flags & SND_MOTU_SPEC_SUPPORT_CLOCK_X4)
				pcm_chunks[2] += 2;
		}

		if (flags & SND_MOTU_SPEC_TX_RETURN_CHUNK) {
			pcm_chunks[0] += 2;
			pcm_chunks[1] += 2;
			if (flags & SND_MOTU_SPEC_SUPPORT_CLOCK_X4)
				pcm_chunks[2] += 2;
		}

		if (flags & SND_MOTU_SPEC_TX_REVERB_CHUNK) {
			pcm_chunks[0] += 2;
			pcm_chunks[1] += 2;
		}
	} else {
		if (flags & SND_MOTU_SPEC_RX_SEPARETED_MAIN) {
			pcm_chunks[0] += 2;
			pcm_chunks[1] += 2;
		}

		// Packets to v3 units include 2 chunks for phone 1/2, except
		// for 176.4/192.0 kHz.
		pcm_chunks[0] += 2;
		pcm_chunks[1] += 2;
	}

	if (flags & SND_MOTU_SPEC_HAS_AESEBU_IFACE) {
		pcm_chunks[0] += 2;
		pcm_chunks[1] += 2;
	}

	/*
	 * At least, packets have two data chunks for S/PDIF on coaxial
	 * interface.
	 */
	pcm_chunks[0] += 2;
	pcm_chunks[1] += 2;

	/*
	 * Fixed part consists of PCM chunks multiple of 4, with msg chunks. As
	 * a result, this part can includes empty data chunks.
	 */
	formats->fixed_part_pcm_chunks[0] = round_up(2 + pcm_chunks[0], 4) - 2;
	formats->fixed_part_pcm_chunks[1] = round_up(2 + pcm_chunks[1], 4) - 2;
	if (flags & SND_MOTU_SPEC_SUPPORT_CLOCK_X4)
		formats->fixed_part_pcm_chunks[2] =
					round_up(2 + pcm_chunks[2], 4) - 2;
}