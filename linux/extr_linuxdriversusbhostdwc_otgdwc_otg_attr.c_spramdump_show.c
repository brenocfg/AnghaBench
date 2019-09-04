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
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*) ; 

__attribute__((used)) static ssize_t spramdump_show(struct device *_dev,
			      struct device_attribute *attr, char *buf)
{
#if 0
	dwc_otg_device_t *otg_dev = dwc_otg_drvdev(_dev);

	dwc_otg_dump_spram(otg_dev->core_if);
#endif

	return sprintf(buf, "SPRAM Dump\n");
}