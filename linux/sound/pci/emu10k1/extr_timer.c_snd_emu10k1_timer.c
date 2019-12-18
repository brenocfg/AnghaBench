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
struct snd_timer {int /*<<< orphan*/  hw; struct snd_emu10k1* private_data; int /*<<< orphan*/  name; } ;
struct snd_emu10k1 {struct snd_timer* timer; TYPE_1__* card; } ;
struct TYPE_2__ {int /*<<< orphan*/  number; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_TIMER_CLASS_CARD ; 
 int /*<<< orphan*/  SNDRV_TIMER_SCLASS_NONE ; 
 int /*<<< orphan*/  snd_emu10k1_timer_hw ; 
 int snd_timer_new (TYPE_1__*,char*,struct snd_timer_id*,struct snd_timer**) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

int snd_emu10k1_timer(struct snd_emu10k1 *emu, int device)
{
	struct snd_timer *timer = NULL;
	struct snd_timer_id tid;
	int err;

	tid.dev_class = SNDRV_TIMER_CLASS_CARD;
	tid.dev_sclass = SNDRV_TIMER_SCLASS_NONE;
	tid.card = emu->card->number;
	tid.device = device;
	tid.subdevice = 0;
	if ((err = snd_timer_new(emu->card, "EMU10K1", &tid, &timer)) >= 0) {
		strcpy(timer->name, "EMU10K1 timer");
		timer->private_data = emu;
		timer->hw = snd_emu10k1_timer_hw;
	}
	emu->timer = timer;
	return err;
}