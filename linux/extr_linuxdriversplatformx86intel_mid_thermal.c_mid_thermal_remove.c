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
struct platform_info {TYPE_1__** tzd; } ;
struct platform_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  devdata; } ;

/* Variables and functions */
 int MSIC_THERMAL_SENSORS ; 
 int configure_adc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 struct platform_info* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  thermal_zone_device_unregister (TYPE_1__*) ; 

__attribute__((used)) static int mid_thermal_remove(struct platform_device *pdev)
{
	int i;
	struct platform_info *pinfo = platform_get_drvdata(pdev);

	for (i = 0; i < MSIC_THERMAL_SENSORS; i++) {
		kfree(pinfo->tzd[i]->devdata);
		thermal_zone_device_unregister(pinfo->tzd[i]);
	}

	/* Stop the ADC */
	return configure_adc(0);
}