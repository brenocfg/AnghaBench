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
struct snd_motu_packet_format {unsigned int* fixed_part_pcm_chunks; unsigned int* differed_part_pcm_chunks; unsigned int msg_chunks; int /*<<< orphan*/  midi_byte_offset; int /*<<< orphan*/  midi_flag_offset; int /*<<< orphan*/  pcm_byte_offset; } ;
struct amdtp_stream {int syt_interval; size_t sfc; struct amdtp_motu* protocol; } ;
struct amdtp_motu {unsigned int pcm_chunks; unsigned int midi_ports; unsigned int midi_db_interval; unsigned int next_cycles; unsigned int quotient_ticks_per_event; unsigned int remainder_ticks_per_event; unsigned int next_ticks; scalar_t__ next_accumulated; scalar_t__ next_seconds; scalar_t__ midi_db_count; int /*<<< orphan*/  midi_byte_offset; int /*<<< orphan*/  midi_flag_offset; int /*<<< orphan*/  pcm_byte_offset; } ;

/* Variables and functions */
 int ARRAY_SIZE (unsigned int*) ; 
#define  CIP_SFC_176400 133 
#define  CIP_SFC_192000 132 
#define  CIP_SFC_44100 131 
#define  CIP_SFC_48000 130 
#define  CIP_SFC_88200 129 
#define  CIP_SFC_96000 128 
 int DIV_ROUND_UP (unsigned int,int) ; 
 int EBUSY ; 
 int EINVAL ; 
 unsigned int MIDI_BYTES_PER_SECOND ; 
 scalar_t__ amdtp_stream_running (struct amdtp_stream*) ; 
 int amdtp_stream_set_parameters (struct amdtp_stream*,unsigned int,unsigned int) ; 
 unsigned int* snd_motu_clock_rates ; 

int amdtp_motu_set_parameters(struct amdtp_stream *s, unsigned int rate,
			      unsigned int midi_ports,
			      struct snd_motu_packet_format *formats)
{
	static const struct {
		unsigned int quotient_ticks_per_event;
		unsigned int remainder_ticks_per_event;
	} params[] = {
		[CIP_SFC_44100]  = { 557, 123 },
		[CIP_SFC_48000]  = { 512,   0 },
		[CIP_SFC_88200]  = { 278, 282 },
		[CIP_SFC_96000]  = { 256,   0 },
		[CIP_SFC_176400] = { 139, 141 },
		[CIP_SFC_192000] = { 128,   0 },
	};
	struct amdtp_motu *p = s->protocol;
	unsigned int pcm_chunks, data_chunks, data_block_quadlets;
	unsigned int delay;
	unsigned int mode;
	int i, err;

	if (amdtp_stream_running(s))
		return -EBUSY;

	for (i = 0; i < ARRAY_SIZE(snd_motu_clock_rates); ++i) {
		if (snd_motu_clock_rates[i] == rate) {
			mode = i >> 1;
			break;
		}
	}
	if (i == ARRAY_SIZE(snd_motu_clock_rates))
		return -EINVAL;

	pcm_chunks = formats->fixed_part_pcm_chunks[mode] +
		     formats->differed_part_pcm_chunks[mode];
	data_chunks = formats->msg_chunks + pcm_chunks;

	/*
	 * Each data block includes SPH in its head. Data chunks follow with
	 * 3 byte alignment. Padding follows with zero to conform to quadlet
	 * alignment.
	 */
	data_block_quadlets = 1 + DIV_ROUND_UP(data_chunks * 3, 4);

	err = amdtp_stream_set_parameters(s, rate, data_block_quadlets);
	if (err < 0)
		return err;

	p->pcm_chunks = pcm_chunks;
	p->pcm_byte_offset = formats->pcm_byte_offset;

	p->midi_ports = midi_ports;
	p->midi_flag_offset = formats->midi_flag_offset;
	p->midi_byte_offset = formats->midi_byte_offset;

	p->midi_db_count = 0;
	p->midi_db_interval = rate / MIDI_BYTES_PER_SECOND;

	/* IEEE 1394 bus requires. */
	delay = 0x2e00;

	/* For no-data or empty packets to adjust PCM sampling frequency. */
	delay += 8000 * 3072 * s->syt_interval / rate;

	p->next_seconds = 0;
	p->next_cycles = delay / 3072;
	p->quotient_ticks_per_event = params[s->sfc].quotient_ticks_per_event;
	p->remainder_ticks_per_event = params[s->sfc].remainder_ticks_per_event;
	p->next_ticks = delay % 3072;
	p->next_accumulated = 0;

	return 0;
}