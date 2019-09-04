#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct cxacru_data {TYPE_2__* usbatm; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_4__ {TYPE_1__* atm_dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  esi; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_usb_interface (struct device*) ; 
 struct cxacru_data* to_usbatm_driver_data (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t mac_address_show(struct device *dev,
	struct device_attribute *attr, char *buf)
{
	struct cxacru_data *instance = to_usbatm_driver_data(
			to_usb_interface(dev));

	if (instance == NULL || instance->usbatm->atm_dev == NULL)
		return -ENODEV;

	return snprintf(buf, PAGE_SIZE, "%pM\n",
		instance->usbatm->atm_dev->esi);
}