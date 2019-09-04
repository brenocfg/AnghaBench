#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snd_pcm_substream {TYPE_1__* runtime; } ;
struct esschan {unsigned int wav_shift; unsigned int dma_size; } ;
struct es1968 {int dummy; } ;
typedef  int /*<<< orphan*/  snd_pcm_uframes_t ;
struct TYPE_2__ {struct esschan* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  bytes_to_frames (TYPE_1__*,unsigned int) ; 
 unsigned int snd_es1968_get_dma_ptr (struct es1968*,struct esschan*) ; 
 struct es1968* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static snd_pcm_uframes_t snd_es1968_pcm_pointer(struct snd_pcm_substream *substream)
{
	struct es1968 *chip = snd_pcm_substream_chip(substream);
	struct esschan *es = substream->runtime->private_data;
	unsigned int ptr;

	ptr = snd_es1968_get_dma_ptr(chip, es) << es->wav_shift;
	
	return bytes_to_frames(substream->runtime, ptr % es->dma_size);
}