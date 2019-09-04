#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct thermal_zone_device {int dummy; } ;
struct thermal_cooling_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  THERMAL_NO_LIMIT ; 
 int /*<<< orphan*/  THERMAL_WEIGHT_DEFAULT ; 
 struct thermal_cooling_device* cl_dev ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 scalar_t__ thermal_zone_bind_cooling_device (struct thermal_zone_device*,int /*<<< orphan*/ ,struct thermal_cooling_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int acerhdf_bind(struct thermal_zone_device *thermal,
			struct thermal_cooling_device *cdev)
{
	/* if the cooling device is the one from acerhdf bind it */
	if (cdev != cl_dev)
		return 0;

	if (thermal_zone_bind_cooling_device(thermal, 0, cdev,
			THERMAL_NO_LIMIT, THERMAL_NO_LIMIT,
			THERMAL_WEIGHT_DEFAULT)) {
		pr_err("error binding cooling dev\n");
		return -EINVAL;
	}
	return 0;
}