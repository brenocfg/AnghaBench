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
struct gasket_sysfs_attribute {int dummy; } ;
struct gasket_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/ * page_table; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
struct device_attribute {TYPE_1__ attr; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
typedef  enum sysfs_attribute_type { ____Placeholder_sysfs_attribute_type } sysfs_attribute_type ;

/* Variables and functions */
#define  ATTR_KERNEL_HIB_NUM_ACTIVE_PAGES 130 
#define  ATTR_KERNEL_HIB_PAGE_TABLE_SIZE 129 
#define  ATTR_KERNEL_HIB_SIMPLE_PAGE_TABLE_SIZE 128 
 int ENODEV ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  gasket_page_table_num_active_pages (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gasket_page_table_num_entries (int /*<<< orphan*/ ) ; 
 struct gasket_sysfs_attribute* gasket_sysfs_get_attr (struct device*,struct device_attribute*) ; 
 struct gasket_dev* gasket_sysfs_get_device_data (struct device*) ; 
 int /*<<< orphan*/  gasket_sysfs_put_attr (struct device*,struct gasket_sysfs_attribute*) ; 
 int /*<<< orphan*/  gasket_sysfs_put_device_data (struct device*,struct gasket_dev*) ; 
 int scnprintf (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t sysfs_show(struct device *device, struct device_attribute *attr,
			  char *buf)
{
	int ret;
	struct gasket_dev *gasket_dev;
	struct gasket_sysfs_attribute *gasket_attr;
	enum sysfs_attribute_type type;

	gasket_dev = gasket_sysfs_get_device_data(device);
	if (!gasket_dev) {
		dev_err(device, "No Apex device sysfs mapping found\n");
		return -ENODEV;
	}

	gasket_attr = gasket_sysfs_get_attr(device, attr);
	if (!gasket_attr) {
		dev_err(device, "No Apex device sysfs attr data found\n");
		gasket_sysfs_put_device_data(device, gasket_dev);
		return -ENODEV;
	}

	type = (enum sysfs_attribute_type)gasket_sysfs_get_attr(device, attr);
	switch (type) {
	case ATTR_KERNEL_HIB_PAGE_TABLE_SIZE:
		ret = scnprintf(buf, PAGE_SIZE, "%u\n",
				gasket_page_table_num_entries(
					gasket_dev->page_table[0]));
		break;
	case ATTR_KERNEL_HIB_SIMPLE_PAGE_TABLE_SIZE:
		ret = scnprintf(buf, PAGE_SIZE, "%u\n",
				gasket_page_table_num_entries(
					gasket_dev->page_table[0]));
		break;
	case ATTR_KERNEL_HIB_NUM_ACTIVE_PAGES:
		ret = scnprintf(buf, PAGE_SIZE, "%u\n",
				gasket_page_table_num_active_pages(
					gasket_dev->page_table[0]));
		break;
	default:
		dev_dbg(gasket_dev->dev, "Unknown attribute: %s\n",
			attr->attr.name);
		ret = 0;
		break;
	}

	gasket_sysfs_put_attr(device, gasket_attr);
	gasket_sysfs_put_device_data(device, gasket_dev);
	return ret;
}