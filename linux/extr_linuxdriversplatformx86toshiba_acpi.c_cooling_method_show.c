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
struct toshiba_acpi_dev {int max_cooling_method; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 struct toshiba_acpi_dev* dev_get_drvdata (struct device*) ; 
 int sprintf (char*,char*,int,int) ; 
 int toshiba_cooling_method_get (struct toshiba_acpi_dev*,int*) ; 

__attribute__((used)) static ssize_t cooling_method_show(struct device *dev,
				   struct device_attribute *attr, char *buf)
{
	struct toshiba_acpi_dev *toshiba = dev_get_drvdata(dev);
	int state;
	int ret;

	ret = toshiba_cooling_method_get(toshiba, &state);
	if (ret < 0)
		return ret;

	return sprintf(buf, "%d %d\n", state, toshiba->max_cooling_method);
}