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
typedef  void* uint32_t ;
struct max3421_hcd_platform_data {void* vbus_active_level; void* vbus_gpout; } ;
struct device {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,void*,void*) ; 
 int of_property_read_u32_array (int /*<<< orphan*/ ,char*,void**,int) ; 

__attribute__((used)) static int
max3421_of_vbus_en_pin(struct device *dev, struct max3421_hcd_platform_data *pdata)
{
	int retval;
	uint32_t value[2];

	if (!pdata)
		return -EINVAL;

	retval = of_property_read_u32_array(dev->of_node, "maxim,vbus-en-pin", value, 2);
	if (retval) {
		dev_err(dev, "device tree node property 'maxim,vbus-en-pin' is missing\n");
		return retval;
	}
	dev_info(dev, "property 'maxim,vbus-en-pin' value is <%d %d>\n", value[0], value[1]);

	pdata->vbus_gpout = value[0];
	pdata->vbus_active_level = value[1];

	return 0;
}