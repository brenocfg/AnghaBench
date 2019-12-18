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
struct snd_timer_id {int device; scalar_t__ subdevice; int /*<<< orphan*/  card; int /*<<< orphan*/  dev_sclass; int /*<<< orphan*/  dev_class; } ;
struct TYPE_4__ {int /*<<< orphan*/  ticks; int /*<<< orphan*/  resolution; } ;
struct snd_timer {TYPE_2__ hw; struct snd_azf3328* private_data; int /*<<< orphan*/  name; } ;
struct snd_azf3328 {struct snd_timer* timer; TYPE_1__* card; } ;
struct TYPE_3__ {int /*<<< orphan*/  number; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_TIMER_CLASS_CARD ; 
 int /*<<< orphan*/  SNDRV_TIMER_SCLASS_NONE ; 
 int /*<<< orphan*/  seqtimer_scaling ; 
 TYPE_2__ snd_azf3328_timer_hw ; 
 int /*<<< orphan*/  snd_azf3328_timer_stop (struct snd_timer*) ; 
 int snd_timer_new (TYPE_1__*,char*,struct snd_timer_id*,struct snd_timer**) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
snd_azf3328_timer(struct snd_azf3328 *chip, int device)
{
	struct snd_timer *timer = NULL;
	struct snd_timer_id tid;
	int err;

	tid.dev_class = SNDRV_TIMER_CLASS_CARD;
	tid.dev_sclass = SNDRV_TIMER_SCLASS_NONE;
	tid.card = chip->card->number;
	tid.device = device;
	tid.subdevice = 0;

	snd_azf3328_timer_hw.resolution *= seqtimer_scaling;
	snd_azf3328_timer_hw.ticks /= seqtimer_scaling;

	err = snd_timer_new(chip->card, "AZF3328", &tid, &timer);
	if (err < 0)
		goto out;

	strcpy(timer->name, "AZF3328 timer");
	timer->private_data = chip;
	timer->hw = snd_azf3328_timer_hw;

	chip->timer = timer;

	snd_azf3328_timer_stop(timer);

	err = 0;

out:
	return err;
}