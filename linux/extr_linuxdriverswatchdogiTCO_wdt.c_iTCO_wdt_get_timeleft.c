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
struct watchdog_device {int dummy; } ;
struct iTCO_wdt_private {int iTCO_version; int /*<<< orphan*/  io_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  TCO1_STS (struct iTCO_wdt_private*) ; 
 int /*<<< orphan*/  TCO_RLD (struct iTCO_wdt_private*) ; 
 int /*<<< orphan*/  TCOv1_TMR (struct iTCO_wdt_private*) ; 
 int inb (int /*<<< orphan*/ ) ; 
 int inw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 unsigned int ticks_to_seconds (struct iTCO_wdt_private*,unsigned char) ; 
 struct iTCO_wdt_private* watchdog_get_drvdata (struct watchdog_device*) ; 

__attribute__((used)) static unsigned int iTCO_wdt_get_timeleft(struct watchdog_device *wd_dev)
{
	struct iTCO_wdt_private *p = watchdog_get_drvdata(wd_dev);
	unsigned int val16;
	unsigned char val8;
	unsigned int time_left = 0;

	/* read the TCO Timer */
	if (p->iTCO_version >= 2) {
		spin_lock(&p->io_lock);
		val16 = inw(TCO_RLD(p));
		val16 &= 0x3ff;
		spin_unlock(&p->io_lock);

		time_left = ticks_to_seconds(p, val16);
	} else if (p->iTCO_version == 1) {
		spin_lock(&p->io_lock);
		val8 = inb(TCO_RLD(p));
		val8 &= 0x3f;
		if (!(inw(TCO1_STS(p)) & 0x0008))
			val8 += (inb(TCOv1_TMR(p)) & 0x3f);
		spin_unlock(&p->io_lock);

		time_left = ticks_to_seconds(p, val8);
	}
	return time_left;
}