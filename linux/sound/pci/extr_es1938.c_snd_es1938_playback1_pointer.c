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
struct es1938 {size_t dma2_size; size_t dma2_start; size_t dma2_shift; } ;
typedef  size_t snd_pcm_uframes_t ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIO2DMAADDR ; 
 int /*<<< orphan*/  AUDIO2DMACOUNT ; 
 int /*<<< orphan*/  SLIO_REG (struct es1938*,int /*<<< orphan*/ ) ; 
 size_t inl (int /*<<< orphan*/ ) ; 
 size_t inw (int /*<<< orphan*/ ) ; 
 struct es1938* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static snd_pcm_uframes_t snd_es1938_playback1_pointer(struct snd_pcm_substream *substream)
{
	struct es1938 *chip = snd_pcm_substream_chip(substream);
	size_t ptr;
#if 1
	ptr = chip->dma2_size - inw(SLIO_REG(chip, AUDIO2DMACOUNT));
#else
	ptr = inl(SLIO_REG(chip, AUDIO2DMAADDR)) - chip->dma2_start;
#endif
	return ptr >> chip->dma2_shift;
}