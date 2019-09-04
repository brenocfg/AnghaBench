#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  governor_name; } ;
struct TYPE_10__ {TYPE_1__* governor; } ;
struct TYPE_9__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (TYPE_2__*) ; 
 int /*<<< orphan*/  acerhdf_cooling_ops ; 
 int /*<<< orphan*/  acerhdf_dev_ops ; 
 TYPE_4__ acerhdf_zone_params ; 
 TYPE_2__* cl_dev ; 
 int interval ; 
 scalar_t__ kernelmode ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* thermal_cooling_device_register (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* thermal_zone_device_register (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* thz_dev ; 

__attribute__((used)) static int acerhdf_register_thermal(void)
{
	cl_dev = thermal_cooling_device_register("acerhdf-fan", NULL,
						 &acerhdf_cooling_ops);

	if (IS_ERR(cl_dev))
		return -EINVAL;

	thz_dev = thermal_zone_device_register("acerhdf", 2, 0, NULL,
					      &acerhdf_dev_ops,
					      &acerhdf_zone_params, 0,
					      (kernelmode) ? interval*1000 : 0);
	if (IS_ERR(thz_dev))
		return -EINVAL;

	if (strcmp(thz_dev->governor->name,
				acerhdf_zone_params.governor_name)) {
		pr_err("Didn't get thermal governor %s, perhaps not compiled into thermal subsystem.\n",
				acerhdf_zone_params.governor_name);
		return -EINVAL;
	}

	return 0;
}