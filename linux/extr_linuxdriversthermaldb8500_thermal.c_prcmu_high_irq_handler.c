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
struct db8500_thsens_platform_data {int num_trips; TYPE_2__* trip_points; } ;
struct db8500_thermal_zone {unsigned int cur_index; int cur_temp_pseudo; int /*<<< orphan*/  therm_work; TYPE_1__* therm_dev; struct db8500_thsens_platform_data* trip_tab; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_4__ {unsigned long temp; } ;
struct TYPE_3__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  THERMAL_TREND_RAISING ; 
 int /*<<< orphan*/  db8500_thermal_update_config (struct db8500_thermal_zone*,unsigned int,int /*<<< orphan*/ ,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t prcmu_high_irq_handler(int irq, void *irq_data)
{
	struct db8500_thermal_zone *pzone = irq_data;
	struct db8500_thsens_platform_data *ptrips = pzone->trip_tab;
	unsigned int idx = pzone->cur_index;
	unsigned long next_low, next_high;

	if (idx < ptrips->num_trips - 1) {
		next_high = ptrips->trip_points[idx+1].temp;
		next_low = ptrips->trip_points[idx].temp;
		idx += 1;

		db8500_thermal_update_config(pzone, idx, THERMAL_TREND_RAISING,
			next_low, next_high);

		dev_dbg(&pzone->therm_dev->device,
		"PRCMU set max %ld, min %ld\n", next_high, next_low);
	} else if (idx == ptrips->num_trips - 1)
		pzone->cur_temp_pseudo = ptrips->trip_points[idx].temp + 1;

	schedule_work(&pzone->therm_work);

	return IRQ_HANDLED;
}