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
struct snd_ml403_ac97cr {int /*<<< orphan*/  capture_ind2_rec; int /*<<< orphan*/  capture_substream; scalar_t__ enable_capture_irq; int /*<<< orphan*/  ind_rec; int /*<<< orphan*/  playback_substream; scalar_t__ enable_irq; struct platform_device* pfdev; } ;
struct platform_device {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_INFO ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  disable_irq_nosync (int) ; 
 int platform_get_irq (struct platform_device*,int) ; 
 int /*<<< orphan*/  snd_ml403_ac97cr_capture_ind2_copy ; 
 int /*<<< orphan*/  snd_ml403_ac97cr_capture_ind2_null ; 
 int /*<<< orphan*/  snd_ml403_ac97cr_playback_ind2_copy ; 
 int /*<<< orphan*/  snd_ml403_ac97cr_playback_ind2_zero ; 
 int /*<<< orphan*/  snd_pcm_indirect2_capture_interrupt (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_indirect2_playback_interrupt (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t snd_ml403_ac97cr_irq(int irq, void *dev_id)
{
	struct snd_ml403_ac97cr *ml403_ac97cr;
	struct platform_device *pfdev;
	int cmp_irq;

	ml403_ac97cr = (struct snd_ml403_ac97cr *)dev_id;
	if (ml403_ac97cr == NULL)
		return IRQ_NONE;

	pfdev = ml403_ac97cr->pfdev;

	/* playback interrupt */
	cmp_irq = platform_get_irq(pfdev, 0);
	if (irq == cmp_irq) {
		if (ml403_ac97cr->enable_irq)
			snd_pcm_indirect2_playback_interrupt(
				ml403_ac97cr->playback_substream,
				&ml403_ac97cr->ind_rec,
				snd_ml403_ac97cr_playback_ind2_copy,
				snd_ml403_ac97cr_playback_ind2_zero);
		else
			goto __disable_irq;
	} else {
		/* record interrupt */
		cmp_irq = platform_get_irq(pfdev, 1);
		if (irq == cmp_irq) {
			if (ml403_ac97cr->enable_capture_irq)
				snd_pcm_indirect2_capture_interrupt(
					ml403_ac97cr->capture_substream,
					&ml403_ac97cr->capture_ind2_rec,
					snd_ml403_ac97cr_capture_ind2_copy,
					snd_ml403_ac97cr_capture_ind2_null);
			else
				goto __disable_irq;
		} else
			return IRQ_NONE;
	}
	return IRQ_HANDLED;

__disable_irq:
	PDEBUG(INIT_INFO, "irq(): irq %d is meant to be disabled! So, now try "
	       "to disable it _really_!\n", irq);
	disable_irq_nosync(irq);
	return IRQ_HANDLED;
}