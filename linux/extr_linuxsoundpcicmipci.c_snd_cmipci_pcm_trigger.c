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
struct cmipci_pcm {unsigned int ch; int running; int /*<<< orphan*/  is_dac; int /*<<< orphan*/  needs_silencing; } ;
struct cmipci {unsigned int ctrl; int /*<<< orphan*/  reg_lock; TYPE_1__* card; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned int CM_CH0_INT_EN ; 
 unsigned int CM_CHEN0 ; 
 unsigned int CM_PAUSE0 ; 
 int /*<<< orphan*/  CM_REG_FUNCTRL0 ; 
 int /*<<< orphan*/  CM_REG_INT_HLDCLR ; 
 unsigned int CM_RST_CH0 ; 
 int EINVAL ; 
#define  SNDRV_PCM_TRIGGER_PAUSE_PUSH 133 
#define  SNDRV_PCM_TRIGGER_PAUSE_RELEASE 132 
#define  SNDRV_PCM_TRIGGER_RESUME 131 
#define  SNDRV_PCM_TRIGGER_START 130 
#define  SNDRV_PCM_TRIGGER_STOP 129 
#define  SNDRV_PCM_TRIGGER_SUSPEND 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  snd_cmipci_clear_bit (struct cmipci*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  snd_cmipci_set_bit (struct cmipci*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  snd_cmipci_write (struct cmipci*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_cmipci_pcm_trigger(struct cmipci *cm, struct cmipci_pcm *rec,
				  int cmd)
{
	unsigned int inthld, chen, reset, pause;
	int result = 0;

	inthld = CM_CH0_INT_EN << rec->ch;
	chen = CM_CHEN0 << rec->ch;
	reset = CM_RST_CH0 << rec->ch;
	pause = CM_PAUSE0 << rec->ch;

	spin_lock(&cm->reg_lock);
	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
		rec->running = 1;
		/* set interrupt */
		snd_cmipci_set_bit(cm, CM_REG_INT_HLDCLR, inthld);
		cm->ctrl |= chen;
		/* enable channel */
		snd_cmipci_write(cm, CM_REG_FUNCTRL0, cm->ctrl);
		dev_dbg(cm->card->dev, "functrl0 = %08x\n", cm->ctrl);
		break;
	case SNDRV_PCM_TRIGGER_STOP:
		rec->running = 0;
		/* disable interrupt */
		snd_cmipci_clear_bit(cm, CM_REG_INT_HLDCLR, inthld);
		/* reset */
		cm->ctrl &= ~chen;
		snd_cmipci_write(cm, CM_REG_FUNCTRL0, cm->ctrl | reset);
		snd_cmipci_write(cm, CM_REG_FUNCTRL0, cm->ctrl & ~reset);
		rec->needs_silencing = rec->is_dac;
		break;
	case SNDRV_PCM_TRIGGER_PAUSE_PUSH:
	case SNDRV_PCM_TRIGGER_SUSPEND:
		cm->ctrl |= pause;
		snd_cmipci_write(cm, CM_REG_FUNCTRL0, cm->ctrl);
		break;
	case SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
	case SNDRV_PCM_TRIGGER_RESUME:
		cm->ctrl &= ~pause;
		snd_cmipci_write(cm, CM_REG_FUNCTRL0, cm->ctrl);
		break;
	default:
		result = -EINVAL;
		break;
	}
	spin_unlock(&cm->reg_lock);
	return result;
}