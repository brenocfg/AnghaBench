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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_3__ {int /*<<< orphan*/  core_if; } ;
typedef  TYPE_1__ dwc_otg_device_t ;

/* Variables and functions */
 TYPE_1__* dwc_otg_drvdev (struct device*) ; 
 int dwc_otg_get_srpstatus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t srp_show(struct device *_dev,
			struct device_attribute *attr, char *buf)
{
#ifndef DWC_HOST_ONLY
        dwc_otg_device_t *otg_dev = dwc_otg_drvdev(_dev);
	return sprintf(buf, "SesReqScs = 0x%x\n",
		       dwc_otg_get_srpstatus(otg_dev->core_if));
#else
	return sprintf(buf, "Host Only Mode!\n");
#endif
}