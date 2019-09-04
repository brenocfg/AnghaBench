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
typedef  int u32 ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct cxacru_data {int* card_info; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int ARRAY_SIZE (char**) ; 
 size_t CXINF_LINE_STARTABLE ; 
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  to_usb_interface (struct device*) ; 
 struct cxacru_data* to_usbatm_driver_data (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static ssize_t adsl_state_show(struct device *dev,
	struct device_attribute *attr, char *buf)
{
	static char *str[] = { "running", "stopped" };
	struct cxacru_data *instance = to_usbatm_driver_data(
			to_usb_interface(dev));
	u32 value;

	if (instance == NULL)
		return -ENODEV;

	value = instance->card_info[CXINF_LINE_STARTABLE];
	if (unlikely(value >= ARRAY_SIZE(str)))
		return snprintf(buf, PAGE_SIZE, "%u\n", value);
	return snprintf(buf, PAGE_SIZE, "%s\n", str[value]);
}