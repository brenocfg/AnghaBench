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
struct snd_es18xx {int active; int dma1_shift; int /*<<< orphan*/  dma1; } ;
typedef  int snd_pcm_uframes_t ;

/* Variables and functions */
 int ADC1 ; 
 int snd_dma_pointer (int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int snd_pcm_lib_buffer_bytes (struct snd_pcm_substream*) ; 
 struct snd_es18xx* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static snd_pcm_uframes_t snd_es18xx_capture_pointer(struct snd_pcm_substream *substream)
{
        struct snd_es18xx *chip = snd_pcm_substream_chip(substream);
	unsigned int size = snd_pcm_lib_buffer_bytes(substream);
	int pos;

        if (!(chip->active & ADC1))
                return 0;
	pos = snd_dma_pointer(chip->dma1, size);
	return pos >> chip->dma1_shift;
}