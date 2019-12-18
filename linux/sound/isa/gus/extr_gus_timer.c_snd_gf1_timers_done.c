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
struct TYPE_2__ {int /*<<< orphan*/ * timer2; int /*<<< orphan*/ * timer1; } ;
struct snd_gus_card {TYPE_1__ gf1; int /*<<< orphan*/  card; } ;

/* Variables and functions */
 int SNDRV_GF1_HANDLER_TIMER1 ; 
 int SNDRV_GF1_HANDLER_TIMER2 ; 
 int /*<<< orphan*/  snd_device_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_gf1_set_default_handlers (struct snd_gus_card*,int) ; 

void snd_gf1_timers_done(struct snd_gus_card * gus)
{
	snd_gf1_set_default_handlers(gus, SNDRV_GF1_HANDLER_TIMER1 | SNDRV_GF1_HANDLER_TIMER2);
	if (gus->gf1.timer1) {
		snd_device_free(gus->card, gus->gf1.timer1);
		gus->gf1.timer1 = NULL;
	}
	if (gus->gf1.timer2) {
		snd_device_free(gus->card, gus->gf1.timer2);
		gus->gf1.timer2 = NULL;
	}
}