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
struct panel_drv_data {int vmirror; int /*<<< orphan*/  hmirror; int /*<<< orphan*/  spi; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 struct panel_drv_data* dev_get_drvdata (struct device*) ; 
 int kstrtoint (char const*,int /*<<< orphan*/ ,int*) ; 
 int tpo_td043_write_mirror (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ssize_t tpo_td043_vmirror_store(struct device *dev,
	struct device_attribute *attr, const char *buf, size_t count)
{
	struct panel_drv_data *ddata = dev_get_drvdata(dev);
	int val;
	int ret;

	ret = kstrtoint(buf, 0, &val);
	if (ret < 0)
		return ret;

	val = !!val;

	ret = tpo_td043_write_mirror(ddata->spi, ddata->hmirror, val);
	if (ret < 0)
		return ret;

	ddata->vmirror = val;

	return count;
}