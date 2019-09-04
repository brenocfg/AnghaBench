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
struct thermal_zone_device {struct da9062_thermal* devdata; } ;
struct da9062_thermal {int temperature; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int da9062_thermal_get_temp(struct thermal_zone_device *z,
				   int *temp)
{
	struct da9062_thermal *thermal = z->devdata;

	mutex_lock(&thermal->lock);
	*temp = thermal->temperature;
	mutex_unlock(&thermal->lock);

	return 0;
}