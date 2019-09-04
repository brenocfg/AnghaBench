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
struct snd_sb {int mode; unsigned int dma8; unsigned int dma16; int /*<<< orphan*/  c_dma_size; } ;
struct snd_pcm_substream {int /*<<< orphan*/  runtime; } ;
typedef  int /*<<< orphan*/  snd_pcm_uframes_t ;

/* Variables and functions */
 int SB_MODE_CAPTURE_8 ; 
 int /*<<< orphan*/  bytes_to_frames (int /*<<< orphan*/ ,size_t) ; 
 size_t snd_dma_pointer (unsigned int,int /*<<< orphan*/ ) ; 
 struct snd_sb* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static snd_pcm_uframes_t snd_sb16_capture_pointer(struct snd_pcm_substream *substream)
{
	struct snd_sb *chip = snd_pcm_substream_chip(substream);
	unsigned int dma;
	size_t ptr;

	dma = (chip->mode & SB_MODE_CAPTURE_8) ? chip->dma8 : chip->dma16;
	ptr = snd_dma_pointer(dma, chip->c_dma_size);
	return bytes_to_frames(substream->runtime, ptr);
}