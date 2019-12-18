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
struct snd_sb {int mode; int dma8; int dma16; int /*<<< orphan*/  p_dma_size; } ;
struct snd_pcm_substream {int /*<<< orphan*/  runtime; } ;
typedef  int /*<<< orphan*/  snd_pcm_uframes_t ;

/* Variables and functions */
 int SB_MODE_PLAYBACK_16 ; 
 int SB_MODE_PLAYBACK_8 ; 
 int /*<<< orphan*/  bytes_to_frames (int /*<<< orphan*/ ,size_t) ; 
 size_t snd_dma_pointer (int,int /*<<< orphan*/ ) ; 
 struct snd_sb* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static snd_pcm_uframes_t snd_sb8_playback_pointer(struct snd_pcm_substream *substream)
{
	struct snd_sb *chip = snd_pcm_substream_chip(substream);
	size_t ptr;
	int dma;

	if (chip->mode & SB_MODE_PLAYBACK_8)
		dma = chip->dma8;
	else if (chip->mode & SB_MODE_PLAYBACK_16)
		dma = chip->dma16;
	else
		return 0;
	ptr = snd_dma_pointer(dma, chip->p_dma_size);
	return bytes_to_frames(substream->runtime, ptr);
}