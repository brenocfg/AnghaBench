#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int /*<<< orphan*/  lock; TYPE_2__* card; } ;
typedef  TYPE_3__ vortex_t ;
struct snd_pcm_substream {int /*<<< orphan*/  pcm; TYPE_1__* runtime; } ;
struct TYPE_18__ {int dma; int fifo_enabled; } ;
typedef  TYPE_4__ stream_t ;
struct TYPE_16__ {int /*<<< orphan*/  dev; } ;
struct TYPE_15__ {scalar_t__ private_data; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SNDRV_PCM_TRIGGER_PAUSE_PUSH 131 
#define  SNDRV_PCM_TRIGGER_PAUSE_RELEASE 130 
#define  SNDRV_PCM_TRIGGER_START 129 
#define  SNDRV_PCM_TRIGGER_STOP 128 
 int /*<<< orphan*/  VORTEX_PCM_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VORTEX_PCM_WT ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int) ; 
 TYPE_3__* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vortex_adbdma_pausefifo (TYPE_3__*,int) ; 
 int /*<<< orphan*/  vortex_adbdma_resetup (TYPE_3__*,int) ; 
 int /*<<< orphan*/  vortex_adbdma_resumefifo (TYPE_3__*,int) ; 
 int /*<<< orphan*/  vortex_adbdma_startfifo (TYPE_3__*,int) ; 
 int /*<<< orphan*/  vortex_adbdma_stopfifo (TYPE_3__*,int) ; 
 int /*<<< orphan*/  vortex_wtdma_pausefifo (TYPE_3__*,int) ; 
 int /*<<< orphan*/  vortex_wtdma_resumefifo (TYPE_3__*,int) ; 
 int /*<<< orphan*/  vortex_wtdma_startfifo (TYPE_3__*,int) ; 
 int /*<<< orphan*/  vortex_wtdma_stopfifo (TYPE_3__*,int) ; 

__attribute__((used)) static int snd_vortex_pcm_trigger(struct snd_pcm_substream *substream, int cmd)
{
	vortex_t *chip = snd_pcm_substream_chip(substream);
	stream_t *stream = (stream_t *) substream->runtime->private_data;
	int dma = stream->dma;

	spin_lock(&chip->lock);
	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
		// do something to start the PCM engine
		//printk(KERN_INFO "vortex: start %d\n", dma);
		stream->fifo_enabled = 1;
		if (VORTEX_PCM_TYPE(substream->pcm) != VORTEX_PCM_WT) {
			vortex_adbdma_resetup(chip, dma);
			vortex_adbdma_startfifo(chip, dma);
		}
#ifndef CHIP_AU8810
		else {
			dev_info(chip->card->dev, "wt start %d\n", dma);
			vortex_wtdma_startfifo(chip, dma);
		}
#endif
		break;
	case SNDRV_PCM_TRIGGER_STOP:
		// do something to stop the PCM engine
		//printk(KERN_INFO "vortex: stop %d\n", dma);
		stream->fifo_enabled = 0;
		if (VORTEX_PCM_TYPE(substream->pcm) != VORTEX_PCM_WT)
			vortex_adbdma_stopfifo(chip, dma);
#ifndef CHIP_AU8810
		else {
			dev_info(chip->card->dev, "wt stop %d\n", dma);
			vortex_wtdma_stopfifo(chip, dma);
		}
#endif
		break;
	case SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		//printk(KERN_INFO "vortex: pause %d\n", dma);
		if (VORTEX_PCM_TYPE(substream->pcm) != VORTEX_PCM_WT)
			vortex_adbdma_pausefifo(chip, dma);
#ifndef CHIP_AU8810
		else
			vortex_wtdma_pausefifo(chip, dma);
#endif
		break;
	case SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		//printk(KERN_INFO "vortex: resume %d\n", dma);
		if (VORTEX_PCM_TYPE(substream->pcm) != VORTEX_PCM_WT)
			vortex_adbdma_resumefifo(chip, dma);
#ifndef CHIP_AU8810
		else
			vortex_wtdma_resumefifo(chip, dma);
#endif
		break;
	default:
		spin_unlock(&chip->lock);
		return -EINVAL;
	}
	spin_unlock(&chip->lock);
	return 0;
}