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
struct amdtp_stream {int /*<<< orphan*/  pcm; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 struct snd_pcm_substream* READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_midi_messages (struct amdtp_stream*,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  read_pcm_s32 (struct amdtp_stream*,struct snd_pcm_substream*,int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static unsigned int process_tx_data_blocks(struct amdtp_stream *s,
					   __be32 *buffer,
					   unsigned int data_blocks,
					   unsigned int *syt)
{
	struct snd_pcm_substream *pcm;
	unsigned int pcm_frames;

	pcm = READ_ONCE(s->pcm);
	if (pcm) {
		read_pcm_s32(s, pcm, buffer, data_blocks);
		pcm_frames = data_blocks;
	} else {
		pcm_frames = 0;
	}

	read_midi_messages(s, buffer, data_blocks);

	return pcm_frames;
}