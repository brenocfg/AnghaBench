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
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct TYPE_2__ {int /*<<< orphan*/  period_bytes_max; int /*<<< orphan*/  buffer_bytes_max; } ;
struct snd_pcm_runtime {TYPE_1__ hw; } ;
struct snd_ad1816a {struct snd_pcm_substream* capture_substream; int /*<<< orphan*/  dma2; } ;

/* Variables and functions */
 int /*<<< orphan*/  AD1816A_MODE_CAPTURE ; 
 TYPE_1__ snd_ad1816a_capture ; 
 int snd_ad1816a_open (struct snd_ad1816a*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_limit_isa_dma_size (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct snd_ad1816a* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_ad1816a_capture_open(struct snd_pcm_substream *substream)
{
	struct snd_ad1816a *chip = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;
	int error;

	if ((error = snd_ad1816a_open(chip, AD1816A_MODE_CAPTURE)) < 0)
		return error;
	runtime->hw = snd_ad1816a_capture;
	snd_pcm_limit_isa_dma_size(chip->dma2, &runtime->hw.buffer_bytes_max);
	snd_pcm_limit_isa_dma_size(chip->dma2, &runtime->hw.period_bytes_max);
	chip->capture_substream = substream;
	return 0;
}