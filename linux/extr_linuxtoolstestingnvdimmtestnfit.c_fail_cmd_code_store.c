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
 unsigned long* dimm_fail_cmd_code ; 
 int dimm_name_to_id (struct device*) ; 
 int kstrtol (char const*,int /*<<< orphan*/ ,unsigned long*) ; 

__attribute__((used)) static ssize_t fail_cmd_code_store(struct device *dev, struct device_attribute *attr,
		const char *buf, size_t size)
{
	int dimm = dimm_name_to_id(dev);
	unsigned long val;
	ssize_t rc;

	if (dimm < 0)
		return dimm;

	rc = kstrtol(buf, 0, &val);
	if (rc)
		return rc;

	dimm_fail_cmd_code[dimm] = val;
	return size;
}