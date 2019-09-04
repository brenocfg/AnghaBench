#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ expires; } ;
struct brcmf_sdio {int wd_active; TYPE_2__ timer; TYPE_1__* sdiodev; } ;
struct TYPE_5__ {scalar_t__ state; } ;

/* Variables and functions */
 scalar_t__ BRCMF_SDIOD_DATA ; 
 scalar_t__ BRCMF_WD_POLL ; 
 int /*<<< orphan*/  add_timer (TYPE_2__*) ; 
 int /*<<< orphan*/  del_timer_sync (TYPE_2__*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (TYPE_2__*,scalar_t__) ; 

void brcmf_sdio_wd_timer(struct brcmf_sdio *bus, bool active)
{
	/* Totally stop the timer */
	if (!active && bus->wd_active) {
		del_timer_sync(&bus->timer);
		bus->wd_active = false;
		return;
	}

	/* don't start the wd until fw is loaded */
	if (bus->sdiodev->state != BRCMF_SDIOD_DATA)
		return;

	if (active) {
		if (!bus->wd_active) {
			/* Create timer again when watchdog period is
			   dynamically changed or in the first instance
			 */
			bus->timer.expires = jiffies + BRCMF_WD_POLL;
			add_timer(&bus->timer);
			bus->wd_active = true;
		} else {
			/* Re arm the timer, at last watchdog period */
			mod_timer(&bus->timer, jiffies + BRCMF_WD_POLL);
		}
	}
}