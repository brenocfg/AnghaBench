#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;
struct TYPE_3__ {int /*<<< orphan*/  pcd; } ;
typedef  TYPE_1__ dwc_otg_device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DWC_PRINTF (char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* dwc_otg_drvdev (struct device*) ; 
 int /*<<< orphan*/  dwc_otg_pcd_disconnect_us (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  simple_strtoul (char const*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static ssize_t disconnect_us(struct device *_dev,
			     struct device_attribute *attr,
			     const char *buf, size_t count)
{

#ifndef DWC_HOST_ONLY
        dwc_otg_device_t *otg_dev = dwc_otg_drvdev(_dev);
	uint32_t val = simple_strtoul(buf, NULL, 16);
	DWC_PRINTF("The Passed value is %04x\n", val);

	dwc_otg_pcd_disconnect_us(otg_dev->pcd, 50);

#endif /* DWC_HOST_ONLY */
	return count;
}