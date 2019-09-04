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
struct notifier_block {int dummy; } ;

/* Variables and functions */
 int NOTIFY_DONE ; 
#define  SYS_DOWN 130 
#define  SYS_HALT 129 
#define  SYS_POWER_OFF 128 
 int /*<<< orphan*/  stmp3xxx_wdd ; 
 int /*<<< orphan*/  wdt_stop (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int wdt_notify_sys(struct notifier_block *nb, unsigned long code,
			  void *unused)
{
	switch (code) {
	case SYS_DOWN:	/* keep enabled, system might crash while going down */
		break;
	case SYS_HALT:	/* allow the system to actually halt */
	case SYS_POWER_OFF:
		wdt_stop(&stmp3xxx_wdd);
		break;
	}

	return NOTIFY_DONE;
}