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
struct snd_timer_id {scalar_t__ subdevice; scalar_t__ device; int /*<<< orphan*/  card; int /*<<< orphan*/  dev_sclass; int /*<<< orphan*/  dev_class; } ;
struct snd_timer {int /*<<< orphan*/  hw; struct snd_cs4231* private_data; int /*<<< orphan*/  name; } ;
struct snd_cs4231 {struct snd_timer* timer; } ;
struct snd_card {int /*<<< orphan*/  number; struct snd_cs4231* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_TIMER_CLASS_CARD ; 
 int /*<<< orphan*/  SNDRV_TIMER_SCLASS_NONE ; 
 int /*<<< orphan*/  snd_cs4231_timer_table ; 
 int snd_timer_new (struct snd_card*,char*,struct snd_timer_id*,struct snd_timer**) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int snd_cs4231_timer(struct snd_card *card)
{
	struct snd_cs4231 *chip = card->private_data;
	struct snd_timer *timer;
	struct snd_timer_id tid;
	int err;

	/* Timer initialization */
	tid.dev_class = SNDRV_TIMER_CLASS_CARD;
	tid.dev_sclass = SNDRV_TIMER_SCLASS_NONE;
	tid.card = card->number;
	tid.device = 0;
	tid.subdevice = 0;
	err = snd_timer_new(card, "CS4231", &tid, &timer);
	if (err < 0)
		return err;
	strcpy(timer->name, "CS4231");
	timer->private_data = chip;
	timer->hw = snd_cs4231_timer_table;
	chip->timer = timer;

	return 0;
}