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
struct thermal_zone_device {struct spear_thermal_dev* devdata; } ;
struct spear_thermal_dev {int /*<<< orphan*/  thermal_base; } ;

/* Variables and functions */
 int MD_FACTOR ; 
 int readl_relaxed (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int thermal_get_temp(struct thermal_zone_device *thermal,
				int *temp)
{
	struct spear_thermal_dev *stdev = thermal->devdata;

	/*
	 * Data are ready to be read after 628 usec from POWERDOWN signal
	 * (PDN) = 1
	 */
	*temp = (readl_relaxed(stdev->thermal_base) & 0x7F) * MD_FACTOR;
	return 0;
}