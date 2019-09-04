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
struct ds2781_device_info {int dummy; } ;

/* Variables and functions */
 int ds2781_battery_io (struct ds2781_device_info*,char*,int,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int w1_ds2781_read(struct ds2781_device_info *dev_info, char *buf,
		int addr, size_t count)
{
	return ds2781_battery_io(dev_info, buf, addr, count, 0);
}