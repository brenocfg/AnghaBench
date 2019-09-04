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
struct asus_wmi {int dummy; } ;

/* Variables and functions */
 int asus_hwmon_agfn_fan_speed_read (struct asus_wmi*,int,int*) ; 

__attribute__((used)) static int asus_hwmon_get_fan_number(struct asus_wmi *asus, int *num_fans)
{
	int status;
	int speed = 0;

	*num_fans = 0;

	status = asus_hwmon_agfn_fan_speed_read(asus, 1, &speed);
	if (!status)
		*num_fans = 1;

	return 0;
}