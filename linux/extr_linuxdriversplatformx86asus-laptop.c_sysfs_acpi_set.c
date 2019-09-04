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
struct asus_laptop {int /*<<< orphan*/  handle; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int ENODEV ; 
 int kstrtoint (char const*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ write_acpi_int (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static ssize_t sysfs_acpi_set(struct asus_laptop *asus,
			      const char *buf, size_t count,
			      const char *method)
{
	int rv, value;

	rv = kstrtoint(buf, 0, &value);
	if (rv < 0)
		return rv;

	if (write_acpi_int(asus->handle, method, value))
		return -ENODEV;
	return count;
}