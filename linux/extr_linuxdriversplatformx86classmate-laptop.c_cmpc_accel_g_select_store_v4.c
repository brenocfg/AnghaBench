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
struct input_dev {int /*<<< orphan*/  dev; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct cmpc_accel {unsigned long g_select; } ;
struct acpi_device {int /*<<< orphan*/  handle; int /*<<< orphan*/  dev; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  cmpc_accel_set_g_select_v4 (int /*<<< orphan*/ ,unsigned long) ; 
 void* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int kstrtoul (char const*,int /*<<< orphan*/ ,unsigned long*) ; 
 int strnlen (char const*,size_t) ; 
 struct acpi_device* to_acpi_device (struct device*) ; 

__attribute__((used)) static ssize_t cmpc_accel_g_select_store_v4(struct device *dev,
					    struct device_attribute *attr,
					    const char *buf, size_t count)
{
	struct acpi_device *acpi;
	struct input_dev *inputdev;
	struct cmpc_accel *accel;
	unsigned long g_select;
	int r;

	acpi = to_acpi_device(dev);
	inputdev = dev_get_drvdata(&acpi->dev);
	accel = dev_get_drvdata(&inputdev->dev);

	r = kstrtoul(buf, 0, &g_select);
	if (r)
		return r;

	/* 0 means 1.5g, 1 means 6g, everything else is wrong */
	if (g_select != 0 && g_select != 1)
		return -EINVAL;

	accel->g_select = g_select;
	cmpc_accel_set_g_select_v4(acpi->handle, g_select);

	return strnlen(buf, count);
}