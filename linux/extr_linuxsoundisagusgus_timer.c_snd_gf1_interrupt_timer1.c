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
struct snd_timer {int /*<<< orphan*/  sticks; } ;
struct TYPE_2__ {struct snd_timer* timer1; } ;
struct snd_gus_card {TYPE_1__ gf1; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_timer_interrupt (struct snd_timer*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void snd_gf1_interrupt_timer1(struct snd_gus_card * gus)
{
	struct snd_timer *timer = gus->gf1.timer1;

	if (timer == NULL)
		return;
	snd_timer_interrupt(timer, timer->sticks);
}