#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct snd_pcm_substream {TYPE_1__* runtime; } ;
struct cs5535audio_dma {TYPE_2__* ops; } ;
struct cs5535audio {int /*<<< orphan*/  reg_lock; TYPE_3__* card; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* disable_dma ) (struct cs5535audio*) ;int /*<<< orphan*/  (* enable_dma ) (struct cs5535audio*) ;int /*<<< orphan*/  (* pause_dma ) (struct cs5535audio*) ;} ;
struct TYPE_4__ {struct cs5535audio_dma* private_data; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SNDRV_PCM_TRIGGER_PAUSE_PUSH 133 
#define  SNDRV_PCM_TRIGGER_PAUSE_RELEASE 132 
#define  SNDRV_PCM_TRIGGER_RESUME 131 
#define  SNDRV_PCM_TRIGGER_START 130 
#define  SNDRV_PCM_TRIGGER_STOP 129 
#define  SNDRV_PCM_TRIGGER_SUSPEND 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct cs5535audio* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct cs5535audio*) ; 
 int /*<<< orphan*/  stub2 (struct cs5535audio*) ; 
 int /*<<< orphan*/  stub3 (struct cs5535audio*) ; 
 int /*<<< orphan*/  stub4 (struct cs5535audio*) ; 
 int /*<<< orphan*/  stub5 (struct cs5535audio*) ; 
 int /*<<< orphan*/  stub6 (struct cs5535audio*) ; 

__attribute__((used)) static int snd_cs5535audio_trigger(struct snd_pcm_substream *substream, int cmd)
{
	struct cs5535audio *cs5535au = snd_pcm_substream_chip(substream);
	struct cs5535audio_dma *dma = substream->runtime->private_data;
	int err = 0;

	spin_lock(&cs5535au->reg_lock);
	switch (cmd) {
	case SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		dma->ops->pause_dma(cs5535au);
		break;
	case SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		dma->ops->enable_dma(cs5535au);
		break;
	case SNDRV_PCM_TRIGGER_START:
		dma->ops->enable_dma(cs5535au);
		break;
	case SNDRV_PCM_TRIGGER_RESUME:
		dma->ops->enable_dma(cs5535au);
		break;
	case SNDRV_PCM_TRIGGER_STOP:
		dma->ops->disable_dma(cs5535au);
		break;
	case SNDRV_PCM_TRIGGER_SUSPEND:
		dma->ops->disable_dma(cs5535au);
		break;
	default:
		dev_err(cs5535au->card->dev, "unhandled trigger\n");
		err = -EINVAL;
		break;
	}
	spin_unlock(&cs5535au->reg_lock);
	return err;
}