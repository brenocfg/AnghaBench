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
struct pkt_desc {int dummy; } ;
struct amdtp_stream {unsigned int (* process_ctx_payloads ) (struct amdtp_stream*,struct pkt_desc const*,unsigned int,struct snd_pcm_substream*) ;int /*<<< orphan*/  pcm; } ;

/* Variables and functions */
 struct snd_pcm_substream* READ_ONCE (int /*<<< orphan*/ ) ; 
 unsigned int stub1 (struct amdtp_stream*,struct pkt_desc const*,unsigned int,struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  update_pcm_pointers (struct amdtp_stream*,struct snd_pcm_substream*,unsigned int) ; 

__attribute__((used)) static void process_ctx_payloads(struct amdtp_stream *s,
				 const struct pkt_desc *descs,
				 unsigned int packets)
{
	struct snd_pcm_substream *pcm;
	unsigned int pcm_frames;

	pcm = READ_ONCE(s->pcm);
	pcm_frames = s->process_ctx_payloads(s, descs, packets, pcm);
	if (pcm)
		update_pcm_pointers(s, pcm, pcm_frames);
}