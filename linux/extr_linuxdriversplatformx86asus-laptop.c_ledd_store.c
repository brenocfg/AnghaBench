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
typedef  scalar_t__ u32 ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct asus_laptop {scalar_t__ ledd_status; int /*<<< orphan*/  handle; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  METHOD_LEDD ; 
 struct asus_laptop* dev_get_drvdata (struct device*) ; 
 int kstrtoint (char const*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 scalar_t__ write_acpi_int (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ssize_t ledd_store(struct device *dev, struct device_attribute *attr,
			  const char *buf, size_t count)
{
	struct asus_laptop *asus = dev_get_drvdata(dev);
	int rv, value;

	rv = kstrtoint(buf, 0, &value);
	if (rv < 0)
		return rv;

	if (write_acpi_int(asus->handle, METHOD_LEDD, value)) {
		pr_warn("LED display write failed\n");
		return -ENODEV;
	}

	asus->ledd_status = (u32) value;
	return count;
}