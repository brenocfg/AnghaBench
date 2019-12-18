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
struct pkt_desc {unsigned int data_blocks; scalar_t__ ctx_payload; } ;
struct amdtp_stream {int dummy; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  write_pcm_s32 (struct amdtp_stream*,struct snd_pcm_substream*,int /*<<< orphan*/ *,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  write_pcm_silence (struct amdtp_stream*,int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static unsigned int process_it_ctx_payloads(struct amdtp_stream *s,
					   const struct pkt_desc *descs,
					   unsigned int packets,
					   struct snd_pcm_substream *pcm)
{
	unsigned int pcm_frames = 0;
	int i;

	for (i = 0; i < packets; ++i) {
		const struct pkt_desc *desc = descs + i;
		__le32 *buf = (__le32 *)desc->ctx_payload;
		unsigned int data_blocks = desc->data_blocks;

		if (pcm) {
			write_pcm_s32(s, pcm, buf, data_blocks, pcm_frames);
			pcm_frames += data_blocks;
		} else {
			write_pcm_silence(s, buf, data_blocks);
		}
	}

	return pcm_frames;
}