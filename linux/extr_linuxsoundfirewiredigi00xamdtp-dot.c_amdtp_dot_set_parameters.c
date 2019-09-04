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
struct amdtp_stream {int fdf; int sfc; unsigned int syt_interval; struct amdtp_dot* protocol; } ;
struct amdtp_dot {unsigned int pcm_channels; unsigned int midi_fifo_limit; } ;

/* Variables and functions */
 int AMDTP_FDF_AM824 ; 
 int EBUSY ; 
 unsigned int MIDI_BYTES_PER_SECOND ; 
 scalar_t__ amdtp_stream_running (struct amdtp_stream*) ; 
 int amdtp_stream_set_parameters (struct amdtp_stream*,unsigned int,unsigned int) ; 

int amdtp_dot_set_parameters(struct amdtp_stream *s, unsigned int rate,
			     unsigned int pcm_channels)
{
	struct amdtp_dot *p = s->protocol;
	int err;

	if (amdtp_stream_running(s))
		return -EBUSY;

	/*
	 * A first data channel is for MIDI messages, the rest is Multi Bit
	 * Linear Audio data channel.
	 */
	err = amdtp_stream_set_parameters(s, rate, pcm_channels + 1);
	if (err < 0)
		return err;

	s->fdf = AMDTP_FDF_AM824 | s->sfc;

	p->pcm_channels = pcm_channels;

	/*
	 * We do not know the actual MIDI FIFO size of most devices.  Just
	 * assume two bytes, i.e., one byte can be received over the bus while
	 * the previous one is transmitted over MIDI.
	 * (The value here is adjusted for midi_ratelimit_per_packet().)
	 */
	p->midi_fifo_limit = rate - MIDI_BYTES_PER_SECOND * s->syt_interval + 1;

	return 0;
}