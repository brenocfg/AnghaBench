#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct gasket_sysfs_mapping {int attribute_count; struct gasket_sysfs_attribute* attributes; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
struct TYPE_5__ {TYPE_1__ attr; } ;
struct gasket_sysfs_attribute {TYPE_2__ attr; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
struct device_attribute {TYPE_3__ attr; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ) ; 
 struct gasket_sysfs_mapping* get_mapping (struct device*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct gasket_sysfs_attribute *
gasket_sysfs_get_attr(struct device *device, struct device_attribute *attr)
{
	int i;
	int num_attrs;
	struct gasket_sysfs_mapping *mapping = get_mapping(device);
	struct gasket_sysfs_attribute *attrs = NULL;

	if (!mapping)
		return NULL;

	attrs = mapping->attributes;
	num_attrs = mapping->attribute_count;
	for (i = 0; i < num_attrs; ++i) {
		if (!strcmp(attrs[i].attr.attr.name, attr->attr.name))
			return &attrs[i];
	}

	dev_err(device, "Unable to find match for device_attribute %s\n",
		attr->attr.name);
	return NULL;
}