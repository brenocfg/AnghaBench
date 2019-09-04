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
struct TYPE_2__ {int /*<<< orphan*/  tz; } ;
struct armada_drvdata {scalar_t__ type; TYPE_1__ data; } ;

/* Variables and functions */
 scalar_t__ LEGACY ; 
 struct armada_drvdata* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  thermal_zone_device_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int armada_thermal_exit(struct platform_device *pdev)
{
	struct armada_drvdata *drvdata = platform_get_drvdata(pdev);

	if (drvdata->type == LEGACY)
		thermal_zone_device_unregister(drvdata->data.tz);

	return 0;
}