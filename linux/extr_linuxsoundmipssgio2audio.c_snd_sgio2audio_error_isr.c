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
struct snd_sgio2audio_chan {struct snd_pcm_substream* substream; } ;
struct snd_pcm_substream {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  snd_sgio2audio_dma_start (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_sgio2audio_dma_stop (struct snd_pcm_substream*) ; 

__attribute__((used)) static irqreturn_t snd_sgio2audio_error_isr(int irq, void *dev_id)
{
	struct snd_sgio2audio_chan *chan = dev_id;
	struct snd_pcm_substream *substream;

	substream = chan->substream;
	snd_sgio2audio_dma_stop(substream);
	snd_sgio2audio_dma_start(substream);
	return IRQ_HANDLED;
}