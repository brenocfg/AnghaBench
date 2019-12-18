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
struct snd_pcm_runtime {scalar_t__ buffer_size; struct cs4281_dma* private_data; } ;
struct cs4281_dma {int /*<<< orphan*/  regDCC; } ;
struct cs4281 {int dummy; } ;
typedef  scalar_t__ snd_pcm_uframes_t ;

/* Variables and functions */
 scalar_t__ snd_cs4281_peekBA0 (struct cs4281*,int /*<<< orphan*/ ) ; 
 struct cs4281* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static snd_pcm_uframes_t snd_cs4281_pointer(struct snd_pcm_substream *substream)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct cs4281_dma *dma = runtime->private_data;
	struct cs4281 *chip = snd_pcm_substream_chip(substream);

	/*
	dev_dbg(chip->card->dev,
		"DCC = 0x%x, buffer_size = 0x%x, jiffies = %li\n",
		snd_cs4281_peekBA0(chip, dma->regDCC), runtime->buffer_size,
	       jiffies);
	*/
	return runtime->buffer_size -
	       snd_cs4281_peekBA0(chip, dma->regDCC) - 1;
}