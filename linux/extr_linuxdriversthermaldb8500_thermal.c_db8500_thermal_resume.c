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
struct platform_device {int dummy; } ;
struct db8500_thsens_platform_data {TYPE_1__* trip_points; } ;
struct db8500_thermal_zone {struct db8500_thsens_platform_data* trip_tab; } ;
struct TYPE_2__ {unsigned long temp; } ;

/* Variables and functions */
 unsigned long PRCMU_DEFAULT_LOW_TEMP ; 
 int /*<<< orphan*/  THERMAL_TREND_STABLE ; 
 int /*<<< orphan*/  db8500_thermal_update_config (struct db8500_thermal_zone*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,unsigned long) ; 
 struct db8500_thermal_zone* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int db8500_thermal_resume(struct platform_device *pdev)
{
	struct db8500_thermal_zone *pzone = platform_get_drvdata(pdev);
	struct db8500_thsens_platform_data *ptrips = pzone->trip_tab;
	unsigned long dft_low, dft_high;

	dft_low = PRCMU_DEFAULT_LOW_TEMP;
	dft_high = ptrips->trip_points[0].temp;

	db8500_thermal_update_config(pzone, 0, THERMAL_TREND_STABLE,
		dft_low, dft_high);

	return 0;
}