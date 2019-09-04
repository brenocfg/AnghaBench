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
struct snd_timer_id {int device; scalar_t__ subdevice; int /*<<< orphan*/  card; int /*<<< orphan*/  dev_sclass; int /*<<< orphan*/  dev_class; } ;
struct snd_timer {int /*<<< orphan*/  hw; struct snd_ad1816a* private_data; int /*<<< orphan*/  name; } ;
struct snd_ad1816a {struct snd_timer* timer; TYPE_1__* card; } ;
struct TYPE_2__ {int /*<<< orphan*/  number; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_TIMER_CLASS_CARD ; 
 int /*<<< orphan*/  SNDRV_TIMER_SCLASS_NONE ; 
 int /*<<< orphan*/  snd_ad1816a_chip_id (struct snd_ad1816a*) ; 
 int /*<<< orphan*/  snd_ad1816a_timer_table ; 
 int snd_timer_new (TYPE_1__*,char*,struct snd_timer_id*,struct snd_timer**) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int snd_ad1816a_timer(struct snd_ad1816a *chip, int device)
{
	struct snd_timer *timer;
	struct snd_timer_id tid;
	int error;

	tid.dev_class = SNDRV_TIMER_CLASS_CARD;
	tid.dev_sclass = SNDRV_TIMER_SCLASS_NONE;
	tid.card = chip->card->number;
	tid.device = device;
	tid.subdevice = 0;
	if ((error = snd_timer_new(chip->card, "AD1816A", &tid, &timer)) < 0)
		return error;
	strcpy(timer->name, snd_ad1816a_chip_id(chip));
	timer->private_data = chip;
	chip->timer = timer;
	timer->hw = snd_ad1816a_timer_table;
	return 0;
}