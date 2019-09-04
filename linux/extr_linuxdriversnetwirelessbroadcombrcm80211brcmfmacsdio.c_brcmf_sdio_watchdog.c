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
struct brcmf_sdio {int /*<<< orphan*/  timer; scalar_t__ wd_active; int /*<<< orphan*/  watchdog_wait; scalar_t__ watchdog_tsk; } ;

/* Variables and functions */
 scalar_t__ BRCMF_WD_POLL ; 
 struct brcmf_sdio* bus ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 struct brcmf_sdio* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  timer ; 

__attribute__((used)) static void
brcmf_sdio_watchdog(struct timer_list *t)
{
	struct brcmf_sdio *bus = from_timer(bus, t, timer);

	if (bus->watchdog_tsk) {
		complete(&bus->watchdog_wait);
		/* Reschedule the watchdog */
		if (bus->wd_active)
			mod_timer(&bus->timer,
				  jiffies + BRCMF_WD_POLL);
	}
}