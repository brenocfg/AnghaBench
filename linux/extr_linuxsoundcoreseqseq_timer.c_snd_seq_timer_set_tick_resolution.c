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
struct TYPE_2__ {int resolution; } ;
struct snd_seq_timer {int tempo; int ppq; TYPE_1__ tick; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_seq_timer_update_tick (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void snd_seq_timer_set_tick_resolution(struct snd_seq_timer *tmr)
{
	if (tmr->tempo < 1000000)
		tmr->tick.resolution = (tmr->tempo * 1000) / tmr->ppq;
	else {
		/* might overflow.. */
		unsigned int s;
		s = tmr->tempo % tmr->ppq;
		s = (s * 1000) / tmr->ppq;
		tmr->tick.resolution = (tmr->tempo / tmr->ppq) * 1000;
		tmr->tick.resolution += s;
	}
	if (tmr->tick.resolution <= 0)
		tmr->tick.resolution = 1;
	snd_seq_timer_update_tick(&tmr->tick, 0);
}