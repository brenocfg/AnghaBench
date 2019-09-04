#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_3__ {int capabilities; scalar_t__ dev; } ;
struct ssb_bus {int chip_id; TYPE_1__ chipco; int /*<<< orphan*/  extif; } ;

/* Variables and functions */
 int SSB_CHIPCO_CAP_PMU ; 
 scalar_t__ SSB_PLLTYPE_3 ; 
 scalar_t__ ssb_calc_clock_rate (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ssb_chipco_get_clockcontrol (TYPE_1__*,scalar_t__*,scalar_t__*,scalar_t__*) ; 
 scalar_t__ ssb_extif_available (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ssb_extif_get_clockcontrol (int /*<<< orphan*/ *,scalar_t__*,scalar_t__*,scalar_t__*) ; 
 scalar_t__ ssb_pmu_get_controlclock (TYPE_1__*) ; 

u32 ssb_clockspeed(struct ssb_bus *bus)
{
	u32 rate;
	u32 plltype;
	u32 clkctl_n, clkctl_m;

	if (bus->chipco.capabilities & SSB_CHIPCO_CAP_PMU)
		return ssb_pmu_get_controlclock(&bus->chipco);

	if (ssb_extif_available(&bus->extif))
		ssb_extif_get_clockcontrol(&bus->extif, &plltype,
					   &clkctl_n, &clkctl_m);
	else if (bus->chipco.dev)
		ssb_chipco_get_clockcontrol(&bus->chipco, &plltype,
					    &clkctl_n, &clkctl_m);
	else
		return 0;

	if (bus->chip_id == 0x5365) {
		rate = 100000000;
	} else {
		rate = ssb_calc_clock_rate(plltype, clkctl_n, clkctl_m);
		if (plltype == SSB_PLLTYPE_3) /* 25Mhz, 2 dividers */
			rate /= 2;
	}

	return rate;
}