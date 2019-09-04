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
typedef  int u32 ;
struct tsens_device {int num_sensors; TYPE_1__* ops; TYPE_2__* sensor; int /*<<< orphan*/  dev; } ;
struct thermal_zone_device {int dummy; } ;
struct TYPE_4__ {int id; struct thermal_zone_device* tzd; struct tsens_device* tmdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* enable ) (struct tsens_device*,int) ;} ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct thermal_zone_device*) ; 
 int* devm_kcalloc (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 struct thermal_zone_device* devm_thermal_zone_of_sensor_register (int /*<<< orphan*/ ,int,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct tsens_device*,int) ; 
 int /*<<< orphan*/  tsens_of_ops ; 

__attribute__((used)) static int tsens_register(struct tsens_device *tmdev)
{
	int i;
	struct thermal_zone_device *tzd;
	u32 *hw_id, n = tmdev->num_sensors;

	hw_id = devm_kcalloc(tmdev->dev, n, sizeof(u32), GFP_KERNEL);
	if (!hw_id)
		return -ENOMEM;

	for (i = 0;  i < tmdev->num_sensors; i++) {
		tmdev->sensor[i].tmdev = tmdev;
		tmdev->sensor[i].id = i;
		tzd = devm_thermal_zone_of_sensor_register(tmdev->dev, i,
							   &tmdev->sensor[i],
							   &tsens_of_ops);
		if (IS_ERR(tzd))
			continue;
		tmdev->sensor[i].tzd = tzd;
		if (tmdev->ops->enable)
			tmdev->ops->enable(tmdev, i);
	}
	return 0;
}