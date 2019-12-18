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
struct snd_timer_id {int /*<<< orphan*/  device; scalar_t__ subdevice; int /*<<< orphan*/  card; int /*<<< orphan*/  dev_sclass; int /*<<< orphan*/  dev_class; } ;
struct snd_timer {int /*<<< orphan*/  hw; int /*<<< orphan*/  private_free; struct snd_gus_card* private_data; int /*<<< orphan*/  name; } ;
struct TYPE_3__ {struct snd_timer* timer2; struct snd_timer* timer1; int /*<<< orphan*/  interrupt_handler_timer2; int /*<<< orphan*/  interrupt_handler_timer1; } ;
struct snd_gus_card {TYPE_1__ gf1; TYPE_2__* card; int /*<<< orphan*/  timer_dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  number; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_TIMER_CLASS_CARD ; 
 int /*<<< orphan*/  SNDRV_TIMER_SCLASS_NONE ; 
 int /*<<< orphan*/  snd_gf1_interrupt_timer1 ; 
 int /*<<< orphan*/  snd_gf1_interrupt_timer2 ; 
 int /*<<< orphan*/  snd_gf1_timer1 ; 
 int /*<<< orphan*/  snd_gf1_timer1_free ; 
 int /*<<< orphan*/  snd_gf1_timer2 ; 
 int /*<<< orphan*/  snd_gf1_timer2_free ; 
 scalar_t__ snd_timer_new (TYPE_2__*,char*,struct snd_timer_id*,struct snd_timer**) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

void snd_gf1_timers_init(struct snd_gus_card * gus)
{
	struct snd_timer *timer;
	struct snd_timer_id tid;

	if (gus->gf1.timer1 != NULL || gus->gf1.timer2 != NULL)
		return;

	gus->gf1.interrupt_handler_timer1 = snd_gf1_interrupt_timer1;
	gus->gf1.interrupt_handler_timer2 = snd_gf1_interrupt_timer2;

	tid.dev_class = SNDRV_TIMER_CLASS_CARD;
	tid.dev_sclass = SNDRV_TIMER_SCLASS_NONE;
	tid.card = gus->card->number;
	tid.device = gus->timer_dev;
	tid.subdevice = 0;

	if (snd_timer_new(gus->card, "GF1 timer", &tid, &timer) >= 0) {
		strcpy(timer->name, "GF1 timer #1");
		timer->private_data = gus;
		timer->private_free = snd_gf1_timer1_free;
		timer->hw = snd_gf1_timer1;
	}
	gus->gf1.timer1 = timer;

	tid.device++;

	if (snd_timer_new(gus->card, "GF1 timer", &tid, &timer) >= 0) {
		strcpy(timer->name, "GF1 timer #2");
		timer->private_data = gus;
		timer->private_free = snd_gf1_timer2_free;
		timer->hw = snd_gf1_timer2;
	}
	gus->gf1.timer2 = timer;
}