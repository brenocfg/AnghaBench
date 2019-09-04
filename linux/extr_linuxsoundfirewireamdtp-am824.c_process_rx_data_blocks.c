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
struct snd_pcm_substream {int dummy; } ;
struct amdtp_stream {int /*<<< orphan*/  pcm; struct amdtp_am824* protocol; } ;
struct amdtp_am824 {unsigned int frame_multiplier; scalar_t__ midi_ports; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 struct snd_pcm_substream* READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_midi_messages (struct amdtp_stream*,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  write_pcm_s32 (struct amdtp_stream*,struct snd_pcm_substream*,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  write_pcm_silence (struct amdtp_stream*,int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static unsigned int process_rx_data_blocks(struct amdtp_stream *s, __be32 *buffer,
					   unsigned int data_blocks, unsigned int *syt)
{
	struct amdtp_am824 *p = s->protocol;
	struct snd_pcm_substream *pcm = READ_ONCE(s->pcm);
	unsigned int pcm_frames;

	if (pcm) {
		write_pcm_s32(s, pcm, buffer, data_blocks);
		pcm_frames = data_blocks * p->frame_multiplier;
	} else {
		write_pcm_silence(s, buffer, data_blocks);
		pcm_frames = 0;
	}

	if (p->midi_ports)
		write_midi_messages(s, buffer, data_blocks);

	return pcm_frames;
}