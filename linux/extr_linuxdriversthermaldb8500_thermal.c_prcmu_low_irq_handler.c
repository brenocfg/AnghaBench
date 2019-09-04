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
struct db8500_thsens_platform_data {TYPE_1__* trip_points; } ;
struct db8500_thermal_zone {unsigned int cur_index; int /*<<< orphan*/  therm_work; TYPE_2__* therm_dev; struct db8500_thsens_platform_data* trip_tab; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_4__ {int /*<<< orphan*/  device; } ;
struct TYPE_3__ {unsigned long temp; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 unsigned long PRCMU_DEFAULT_LOW_TEMP ; 
 int /*<<< orphan*/  THERMAL_TREND_DROPPING ; 
 int /*<<< orphan*/  db8500_thermal_update_config (struct db8500_thermal_zone*,unsigned int,int /*<<< orphan*/ ,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static irqreturn_t prcmu_low_irq_handler(int irq, void *irq_data)
{
	struct db8500_thermal_zone *pzone = irq_data;
	struct db8500_thsens_platform_data *ptrips = pzone->trip_tab;
	unsigned int idx = pzone->cur_index;
	unsigned long next_low, next_high;

	if (unlikely(idx == 0))
		/* Meaningless for thermal management, ignoring it */
		return IRQ_HANDLED;

	if (idx == 1) {
		next_high = ptrips->trip_points[0].temp;
		next_low = PRCMU_DEFAULT_LOW_TEMP;
	} else {
		next_high = ptrips->trip_points[idx-1].temp;
		next_low = ptrips->trip_points[idx-2].temp;
	}
	idx -= 1;

	db8500_thermal_update_config(pzone, idx, THERMAL_TREND_DROPPING,
		next_low, next_high);

	dev_dbg(&pzone->therm_dev->device,
		"PRCMU set max %ld, min %ld\n", next_high, next_low);

	schedule_work(&pzone->therm_work);

	return IRQ_HANDLED;
}