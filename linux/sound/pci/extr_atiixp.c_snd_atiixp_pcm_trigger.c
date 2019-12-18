#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_pcm_substream {TYPE_1__* runtime; } ;
struct atiixp_dma {int running; int suspended; TYPE_2__* ops; int /*<<< orphan*/  saved_curptr; } ;
struct atiixp {int /*<<< orphan*/  reg_lock; scalar_t__ remap_addr; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* flush_dma ) (struct atiixp*) ;int /*<<< orphan*/  (* enable_transfer ) (struct atiixp*,int) ;scalar_t__ dt_cur; } ;
struct TYPE_3__ {struct atiixp_dma* private_data; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SNDRV_PCM_TRIGGER_PAUSE_PUSH 133 
#define  SNDRV_PCM_TRIGGER_PAUSE_RELEASE 132 
#define  SNDRV_PCM_TRIGGER_RESUME 131 
#define  SNDRV_PCM_TRIGGER_START 130 
#define  SNDRV_PCM_TRIGGER_STOP 129 
#define  SNDRV_PCM_TRIGGER_SUSPEND 128 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int /*<<< orphan*/  snd_atiixp_check_bus_busy (struct atiixp*) ; 
 struct atiixp* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct atiixp*,int) ; 
 int /*<<< orphan*/  stub2 (struct atiixp*,int) ; 
 int /*<<< orphan*/  stub3 (struct atiixp*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int snd_atiixp_pcm_trigger(struct snd_pcm_substream *substream, int cmd)
{
	struct atiixp *chip = snd_pcm_substream_chip(substream);
	struct atiixp_dma *dma = substream->runtime->private_data;
	int err = 0;

	if (snd_BUG_ON(!dma->ops->enable_transfer ||
		       !dma->ops->flush_dma))
		return -EINVAL;

	spin_lock(&chip->reg_lock);
	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
	case SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
	case SNDRV_PCM_TRIGGER_RESUME:
		if (dma->running && dma->suspended &&
		    cmd == SNDRV_PCM_TRIGGER_RESUME)
			writel(dma->saved_curptr, chip->remap_addr +
			       dma->ops->dt_cur);
		dma->ops->enable_transfer(chip, 1);
		dma->running = 1;
		dma->suspended = 0;
		break;
	case SNDRV_PCM_TRIGGER_STOP:
	case SNDRV_PCM_TRIGGER_PAUSE_PUSH:
	case SNDRV_PCM_TRIGGER_SUSPEND:
		dma->suspended = cmd == SNDRV_PCM_TRIGGER_SUSPEND;
		if (dma->running && dma->suspended)
			dma->saved_curptr = readl(chip->remap_addr +
						  dma->ops->dt_cur);
		dma->ops->enable_transfer(chip, 0);
		dma->running = 0;
		break;
	default:
		err = -EINVAL;
		break;
	}
	if (! err) {
		snd_atiixp_check_bus_busy(chip);
		if (cmd == SNDRV_PCM_TRIGGER_STOP) {
			dma->ops->flush_dma(chip);
			snd_atiixp_check_bus_busy(chip);
		}
	}
	spin_unlock(&chip->reg_lock);
	return err;
}