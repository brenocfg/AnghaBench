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
struct snd_timer {int /*<<< orphan*/  sticks; } ;
struct snd_opl3 {struct snd_timer* timer2; struct snd_timer* timer1; int /*<<< orphan*/  l_port; } ;
struct snd_hwdep {struct snd_opl3* private_data; } ;

/* Variables and functions */
 unsigned char inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_timer_interrupt (struct snd_timer*,int /*<<< orphan*/ ) ; 

void snd_opl3_interrupt(struct snd_hwdep * hw)
{
	unsigned char status;
	struct snd_opl3 *opl3;
	struct snd_timer *timer;

	if (hw == NULL)
		return;

	opl3 = hw->private_data;
	status = inb(opl3->l_port);
#if 0
	snd_printk(KERN_DEBUG "AdLib IRQ status = 0x%x\n", status);
#endif
	if (!(status & 0x80))
		return;

	if (status & 0x40) {
		timer = opl3->timer1;
		snd_timer_interrupt(timer, timer->sticks);
	}
	if (status & 0x20) {
		timer = opl3->timer2;
		snd_timer_interrupt(timer, timer->sticks);
	}
}