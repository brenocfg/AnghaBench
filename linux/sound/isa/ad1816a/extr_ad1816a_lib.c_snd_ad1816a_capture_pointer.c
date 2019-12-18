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
struct snd_pcm_substream {int /*<<< orphan*/  runtime; } ;
struct snd_ad1816a {int mode; int /*<<< orphan*/  c_dma_size; int /*<<< orphan*/  dma2; } ;
typedef  int /*<<< orphan*/  snd_pcm_uframes_t ;

/* Variables and functions */
 int AD1816A_MODE_CAPTURE ; 
 int /*<<< orphan*/  bytes_to_frames (int /*<<< orphan*/ ,size_t) ; 
 size_t snd_dma_pointer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct snd_ad1816a* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static snd_pcm_uframes_t snd_ad1816a_capture_pointer(struct snd_pcm_substream *substream)
{
	struct snd_ad1816a *chip = snd_pcm_substream_chip(substream);
	size_t ptr;
	if (!(chip->mode & AD1816A_MODE_CAPTURE))
		return 0;
	ptr = snd_dma_pointer(chip->dma2, chip->c_dma_size);
	return bytes_to_frames(substream->runtime, ptr);
}