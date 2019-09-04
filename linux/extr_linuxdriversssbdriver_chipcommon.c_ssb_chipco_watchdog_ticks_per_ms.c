#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ssb_chipcommon {int capabilities; TYPE_2__* dev; } ;
struct ssb_bus {int dummy; } ;
struct TYPE_3__ {int revision; } ;
struct TYPE_4__ {TYPE_1__ id; struct ssb_bus* bus; } ;

/* Variables and functions */
 int SSB_CHIPCO_CAP_PMU ; 
 int ssb_chipco_alp_clock (struct ssb_chipcommon*) ; 
 int ssb_clockspeed (struct ssb_bus*) ; 

__attribute__((used)) static int ssb_chipco_watchdog_ticks_per_ms(struct ssb_chipcommon *cc)
{
	struct ssb_bus *bus = cc->dev->bus;

	if (cc->capabilities & SSB_CHIPCO_CAP_PMU) {
			/* based on 32KHz ILP clock */
			return 32;
	} else {
		if (cc->dev->id.revision < 18)
			return ssb_clockspeed(bus) / 1000;
		else
			return ssb_chipco_alp_clock(cc) / 1000;
	}
}