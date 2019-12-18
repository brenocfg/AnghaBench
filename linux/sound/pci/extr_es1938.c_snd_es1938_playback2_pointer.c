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
struct es1938 {int dma1_size; size_t dma1_start; size_t dma1_shift; } ;
typedef  size_t snd_pcm_uframes_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMAADDR ; 
 int /*<<< orphan*/  DMACOUNT ; 
 int /*<<< orphan*/  SLDM_REG (struct es1938*,int /*<<< orphan*/ ) ; 
 size_t inl (int /*<<< orphan*/ ) ; 
 size_t inw (int /*<<< orphan*/ ) ; 
 struct es1938* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static snd_pcm_uframes_t snd_es1938_playback2_pointer(struct snd_pcm_substream *substream)
{
	struct es1938 *chip = snd_pcm_substream_chip(substream);
	size_t ptr;
	size_t old, new;
#if 1
	/* This stuff is *needed*, don't ask why - AB */
	old = inw(SLDM_REG(chip, DMACOUNT));
	while ((new = inw(SLDM_REG(chip, DMACOUNT))) != old)
		old = new;
	ptr = chip->dma1_size - 1 - new;
#else
	ptr = inl(SLDM_REG(chip, DMAADDR)) - chip->dma1_start;
#endif
	return ptr >> chip->dma1_shift;
}