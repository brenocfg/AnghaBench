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
typedef  int u16 ;
struct ssb_chipcommon {TYPE_1__* dev; } ;
struct ssb_bus {int chip_id; } ;
struct TYPE_2__ {struct ssb_bus* bus; } ;

/* Variables and functions */

__attribute__((used)) static u16 pmu_fast_powerup_delay(struct ssb_chipcommon *cc)
{
	struct ssb_bus *bus = cc->dev->bus;

	switch (bus->chip_id) {
	case 0x4312:
	case 0x4322:
	case 0x4328:
		return 7000;
	case 0x4325:
		/* TODO: */
	default:
		return 15000;
	}
}