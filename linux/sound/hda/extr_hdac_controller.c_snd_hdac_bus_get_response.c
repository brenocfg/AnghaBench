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
struct TYPE_2__ {unsigned int* res; int /*<<< orphan*/ * cmds; } ;
struct hdac_bus {int /*<<< orphan*/  reg_lock; TYPE_1__ rirb; scalar_t__ polling_mode; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  cond_resched () ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  snd_hdac_bus_update_rirb (struct hdac_bus*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 

int snd_hdac_bus_get_response(struct hdac_bus *bus, unsigned int addr,
			      unsigned int *res)
{
	unsigned long timeout;
	unsigned long loopcounter;

	timeout = jiffies + msecs_to_jiffies(1000);

	for (loopcounter = 0;; loopcounter++) {
		spin_lock_irq(&bus->reg_lock);
		if (bus->polling_mode)
			snd_hdac_bus_update_rirb(bus);
		if (!bus->rirb.cmds[addr]) {
			if (res)
				*res = bus->rirb.res[addr]; /* the last value */
			spin_unlock_irq(&bus->reg_lock);
			return 0;
		}
		spin_unlock_irq(&bus->reg_lock);
		if (time_after(jiffies, timeout))
			break;
		if (loopcounter > 3000)
			msleep(2); /* temporary workaround */
		else {
			udelay(10);
			cond_resched();
		}
	}

	return -EIO;
}