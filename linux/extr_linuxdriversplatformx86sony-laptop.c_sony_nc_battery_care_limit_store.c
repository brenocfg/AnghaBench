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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;
struct TYPE_2__ {int handle; } ;

/* Variables and functions */
 size_t EINVAL ; 
 size_t EIO ; 
 TYPE_1__* bcare_ctl ; 
 scalar_t__ kstrtoul (char const*,int,unsigned long*) ; 
 scalar_t__ sony_call_snc_handle (int,unsigned int,unsigned int*) ; 

__attribute__((used)) static ssize_t sony_nc_battery_care_limit_store(struct device *dev,
		struct device_attribute *attr,
		const char *buffer, size_t count)
{
	unsigned int result, cmd;
	unsigned long value;

	if (count > 31)
		return -EINVAL;

	if (kstrtoul(buffer, 10, &value))
		return -EINVAL;

	/*  limit values (2 bits):
	 *  00 - none
	 *  01 - 80%
	 *  10 - 50%
	 *  11 - 100%
	 *
	 *  bit 0: 0 disable BCL, 1 enable BCL
	 *  bit 1: 1 tell to store the battery limit (see bits 6,7) too
	 *  bits 2,3: reserved
	 *  bits 4,5: store the limit into the EC
	 *  bits 6,7: store the limit into the battery
	 */
	cmd = 0;

	if (value > 0) {
		if (value <= 50)
			cmd = 0x20;

		else if (value <= 80)
			cmd = 0x10;

		else if (value <= 100)
			cmd = 0x30;

		else
			return -EINVAL;

		/*
		 * handle 0x0115 should allow storing on battery too;
		 * handle 0x0136 same as 0x0115 + health status;
		 * handle 0x013f, same as 0x0136 but no storing on the battery
		 */
		if (bcare_ctl->handle != 0x013f)
			cmd = cmd | (cmd << 2);

		cmd = (cmd | 0x1) << 0x10;
	}

	if (sony_call_snc_handle(bcare_ctl->handle, cmd | 0x0100, &result))
		return -EIO;

	return count;
}