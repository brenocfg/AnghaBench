#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ssb_chipcommon {int ticks_per_ms; int max_timer_ms; TYPE_3__* dev; int /*<<< orphan*/  status; int /*<<< orphan*/  gpio_lock; } ;
struct TYPE_4__ {int revision; } ;
struct TYPE_6__ {TYPE_2__* bus; TYPE_1__ id; int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {scalar_t__ bustype; } ;

/* Variables and functions */
 scalar_t__ SSB_BUSTYPE_SSB ; 
 int /*<<< orphan*/  SSB_CHIPCO_CHIPSTAT ; 
 int /*<<< orphan*/  SSB_CHIPCO_GPIOPULLDOWN ; 
 int /*<<< orphan*/  SSB_CHIPCO_GPIOPULLUP ; 
 int /*<<< orphan*/  SSB_CLKMODE_FAST ; 
 int /*<<< orphan*/  calc_fast_powerup_delay (struct ssb_chipcommon*) ; 
 int /*<<< orphan*/  chipco_powercontrol_init (struct ssb_chipcommon*) ; 
 int /*<<< orphan*/  chipco_read32 (struct ssb_chipcommon*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chipco_write32 (struct ssb_chipcommon*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ssb_chipco_set_clockmode (struct ssb_chipcommon*,int /*<<< orphan*/ ) ; 
 int ssb_chipco_watchdog_get_max_timer (struct ssb_chipcommon*) ; 
 int ssb_chipco_watchdog_ticks_per_ms (struct ssb_chipcommon*) ; 
 int /*<<< orphan*/  ssb_pmu_init (struct ssb_chipcommon*) ; 

void ssb_chipcommon_init(struct ssb_chipcommon *cc)
{
	if (!cc->dev)
		return; /* We don't have a ChipCommon */

	spin_lock_init(&cc->gpio_lock);

	if (cc->dev->id.revision >= 11)
		cc->status = chipco_read32(cc, SSB_CHIPCO_CHIPSTAT);
	dev_dbg(cc->dev->dev, "chipcommon status is 0x%x\n", cc->status);

	if (cc->dev->id.revision >= 20) {
		chipco_write32(cc, SSB_CHIPCO_GPIOPULLUP, 0);
		chipco_write32(cc, SSB_CHIPCO_GPIOPULLDOWN, 0);
	}

	ssb_pmu_init(cc);
	chipco_powercontrol_init(cc);
	ssb_chipco_set_clockmode(cc, SSB_CLKMODE_FAST);
	calc_fast_powerup_delay(cc);

	if (cc->dev->bus->bustype == SSB_BUSTYPE_SSB) {
		cc->ticks_per_ms = ssb_chipco_watchdog_ticks_per_ms(cc);
		cc->max_timer_ms = ssb_chipco_watchdog_get_max_timer(cc) / cc->ticks_per_ms;
	}
}