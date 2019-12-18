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
struct atiixp_modem {int /*<<< orphan*/  reg_lock; } ;
struct atiixp_dma {int running; TYPE_2__* ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* flush_dma ) (struct atiixp_modem*) ;int /*<<< orphan*/  (* enable_transfer ) (struct atiixp_modem*,int) ;} ;
struct TYPE_3__ {struct atiixp_dma* private_data; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SNDRV_PCM_TRIGGER_START 129 
#define  SNDRV_PCM_TRIGGER_STOP 128 
 scalar_t__ snd_BUG_ON (int) ; 
 int /*<<< orphan*/  snd_atiixp_check_bus_busy (struct atiixp_modem*) ; 
 struct atiixp_modem* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct atiixp_modem*,int) ; 
 int /*<<< orphan*/  stub2 (struct atiixp_modem*,int) ; 
 int /*<<< orphan*/  stub3 (struct atiixp_modem*) ; 

__attribute__((used)) static int snd_atiixp_pcm_trigger(struct snd_pcm_substream *substream, int cmd)
{
	struct atiixp_modem *chip = snd_pcm_substream_chip(substream);
	struct atiixp_dma *dma = substream->runtime->private_data;
	int err = 0;

	if (snd_BUG_ON(!dma->ops->enable_transfer ||
		       !dma->ops->flush_dma))
		return -EINVAL;

	spin_lock(&chip->reg_lock);
	switch(cmd) {
	case SNDRV_PCM_TRIGGER_START:
		dma->ops->enable_transfer(chip, 1);
		dma->running = 1;
		break;
	case SNDRV_PCM_TRIGGER_STOP:
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