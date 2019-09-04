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
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {scalar_t__ dma_area; int /*<<< orphan*/  format; struct gus_pcm_private* private_data; } ;
struct snd_gus_card {int dummy; } ;
struct gus_pcm_private {scalar_t__ memory; struct snd_gus_card* gus; } ;

/* Variables and functions */
 int snd_gf1_pcm_block_change (struct snd_pcm_substream*,unsigned int,scalar_t__,unsigned int) ; 
 int snd_gf1_pcm_poke_block (struct snd_gus_card*,scalar_t__,scalar_t__,unsigned int,int,int) ; 
 int snd_pcm_format_unsigned (int /*<<< orphan*/ ) ; 
 int snd_pcm_format_width (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int playback_copy_ack(struct snd_pcm_substream *substream,
			     unsigned int bpos, unsigned int len)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct gus_pcm_private *pcmp = runtime->private_data;
	struct snd_gus_card *gus = pcmp->gus;
	int w16, invert;

	if (len > 32)
		return snd_gf1_pcm_block_change(substream, bpos,
						pcmp->memory + bpos, len);

	w16 = (snd_pcm_format_width(runtime->format) == 16);
	invert = snd_pcm_format_unsigned(runtime->format);
	return snd_gf1_pcm_poke_block(gus, runtime->dma_area + bpos,
				      pcmp->memory + bpos, len, w16, invert);
}