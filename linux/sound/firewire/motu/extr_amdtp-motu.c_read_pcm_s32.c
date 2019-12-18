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
typedef  int u8 ;
typedef  int u32 ;
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {unsigned int buffer_size; scalar_t__ dma_area; } ;
struct amdtp_stream {unsigned int pcm_buffer_pointer; int /*<<< orphan*/  data_block_quadlets; struct amdtp_motu* protocol; } ;
struct amdtp_motu {unsigned int pcm_chunks; int pcm_byte_offset; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int frames_to_bytes (struct snd_pcm_runtime*,unsigned int) ; 

__attribute__((used)) static void read_pcm_s32(struct amdtp_stream *s, struct snd_pcm_substream *pcm,
			 __be32 *buffer, unsigned int data_blocks,
			 unsigned int pcm_frames)
{
	struct amdtp_motu *p = s->protocol;
	unsigned int channels = p->pcm_chunks;
	struct snd_pcm_runtime *runtime = pcm->runtime;
	unsigned int pcm_buffer_pointer;
	int remaining_frames;
	u8 *byte;
	u32 *dst;
	int i, c;

	pcm_buffer_pointer = s->pcm_buffer_pointer + pcm_frames;
	pcm_buffer_pointer %= runtime->buffer_size;

	dst = (void *)runtime->dma_area +
				frames_to_bytes(runtime, pcm_buffer_pointer);
	remaining_frames = runtime->buffer_size - pcm_buffer_pointer;

	for (i = 0; i < data_blocks; ++i) {
		byte = (u8 *)buffer + p->pcm_byte_offset;

		for (c = 0; c < channels; ++c) {
			*dst = (byte[0] << 24) |
			       (byte[1] << 16) |
			       (byte[2] << 8);
			byte += 3;
			dst++;
		}
		buffer += s->data_block_quadlets;
		if (--remaining_frames == 0)
			dst = (void *)runtime->dma_area;
	}
}