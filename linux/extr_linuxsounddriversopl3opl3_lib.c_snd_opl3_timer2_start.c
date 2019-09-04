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
struct snd_timer {unsigned int sticks; } ;
struct snd_opl3 {unsigned char timer_enable; int /*<<< orphan*/  timer_lock; int /*<<< orphan*/  (* command ) (struct snd_opl3*,int,unsigned char) ;} ;

/* Variables and functions */
 int OPL3_LEFT ; 
 int OPL3_REG_TIMER2 ; 
 int OPL3_REG_TIMER_CONTROL ; 
 unsigned char OPL3_TIMER2_MASK ; 
 unsigned char OPL3_TIMER2_START ; 
 struct snd_opl3* snd_timer_chip (struct snd_timer*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct snd_opl3*,int,int) ; 
 int /*<<< orphan*/  stub2 (struct snd_opl3*,int,unsigned char) ; 

__attribute__((used)) static int snd_opl3_timer2_start(struct snd_timer * timer)
{
	unsigned long flags;
	unsigned char tmp;
	unsigned int ticks;
	struct snd_opl3 *opl3;

	opl3 = snd_timer_chip(timer);
	spin_lock_irqsave(&opl3->timer_lock, flags);
	ticks = timer->sticks;
	tmp = (opl3->timer_enable | OPL3_TIMER2_START) & ~OPL3_TIMER2_MASK;
	opl3->timer_enable = tmp;
	opl3->command(opl3, OPL3_LEFT | OPL3_REG_TIMER2, 256 - ticks);	/* timer 1 count */
	opl3->command(opl3, OPL3_LEFT | OPL3_REG_TIMER_CONTROL, tmp);	/* enable timer 1 IRQ */
	spin_unlock_irqrestore(&opl3->timer_lock, flags);
	return 0;
}