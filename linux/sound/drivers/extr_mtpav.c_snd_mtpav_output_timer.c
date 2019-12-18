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
struct timer_list {int dummy; } ;
struct mtpav_port {int mode; scalar_t__ output; } ;
struct mtpav {int num_ports; int /*<<< orphan*/  spinlock; struct mtpav_port* ports; int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int MTPAV_MODE_OUTPUT_TRIGGERED ; 
 int MTPAV_PIDX_BROADCAST ; 
 struct mtpav* chip ; 
 struct mtpav* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  snd_mtpav_output_port_write (struct mtpav*,struct mtpav_port*,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  timer ; 

__attribute__((used)) static void snd_mtpav_output_timer(struct timer_list *t)
{
	unsigned long flags;
	struct mtpav *chip = from_timer(chip, t, timer);
	int p;

	spin_lock_irqsave(&chip->spinlock, flags);
	/* reprogram timer */
	mod_timer(&chip->timer, 1 + jiffies);
	/* process each port */
	for (p = 0; p <= chip->num_ports * 2 + MTPAV_PIDX_BROADCAST; p++) {
		struct mtpav_port *portp = &chip->ports[p];
		if ((portp->mode & MTPAV_MODE_OUTPUT_TRIGGERED) && portp->output)
			snd_mtpav_output_port_write(chip, portp, portp->output);
	}
	spin_unlock_irqrestore(&chip->spinlock, flags);
}