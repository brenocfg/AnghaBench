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
 int /*<<< orphan*/  dwc_otg_dump_dev_registers (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc_otg_dump_global_registers (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc_otg_dump_host_registers (int /*<<< orphan*/ ) ; 
 scalar_t__ dwc_otg_is_host_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*) ; 

__attribute__((used)) static ssize_t regdump_show(struct device *_dev,
			    struct device_attribute *attr, char *buf)
{
        dwc_otg_device_t *otg_dev = dwc_otg_drvdev(_dev);

	dwc_otg_dump_global_registers(otg_dev->core_if);
	if (dwc_otg_is_host_mode(otg_dev->core_if)) {
		dwc_otg_dump_host_registers(otg_dev->core_if);
	} else {
		dwc_otg_dump_dev_registers(otg_dev->core_if);

	}
	return sprintf(buf, "Register Dump\n");
}