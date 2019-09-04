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
struct regmap {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 unsigned int SKY81452_OCP ; 
 unsigned int SKY81452_OTMP ; 
 int /*<<< orphan*/  SKY81452_REG4 ; 
 struct regmap* bl_get_data (int /*<<< orphan*/ ) ; 
 int regmap_read (struct regmap*,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  to_backlight_device (struct device*) ; 

__attribute__((used)) static ssize_t sky81452_bl_show_fault(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	struct regmap *regmap = bl_get_data(to_backlight_device(dev));
	unsigned int value = 0;
	int ret;

	ret = regmap_read(regmap, SKY81452_REG4, &value);
	if (ret < 0)
		return ret;

	*buf = 0;

	if (value & SKY81452_OCP)
		strcat(buf, "over-current ");

	if (value & SKY81452_OTMP)
		strcat(buf, "over-temperature");

	strcat(buf, "\n");
	return strlen(buf);
}