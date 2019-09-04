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
typedef  int ssize_t ;
struct TYPE_2__ {scalar_t__ old_ec_model; } ;

/* Variables and functions */
 int ENODEV ; 
 int get_wireless_state_ec_standard () ; 
 TYPE_1__* quirks ; 
 int sprintf (char*,char*,int) ; 
 int threeg_s ; 

__attribute__((used)) static ssize_t show_threeg(struct device *dev,
	struct device_attribute *attr, char *buf)
{

	int ret;

	/* old msi ec not support 3G */
	if (quirks->old_ec_model)
		return -ENODEV;

	ret = get_wireless_state_ec_standard();
	if (ret < 0)
		return ret;

	return sprintf(buf, "%i\n", threeg_s);
}