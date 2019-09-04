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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int isl1208_i2c_get_atr (int /*<<< orphan*/ ) ; 
 int sprintf (char*,char*,int,int) ; 
 int /*<<< orphan*/  to_i2c_client (struct device*) ; 

__attribute__((used)) static ssize_t
isl1208_sysfs_show_atrim(struct device *dev,
			 struct device_attribute *attr, char *buf)
{
	int atr = isl1208_i2c_get_atr(to_i2c_client(dev));
	if (atr < 0)
		return atr;

	return sprintf(buf, "%d.%.2d pF\n", atr >> 2, (atr & 0x3) * 25);
}