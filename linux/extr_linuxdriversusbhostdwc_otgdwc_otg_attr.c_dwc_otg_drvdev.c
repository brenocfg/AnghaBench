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
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  dwc_otg_device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DWC_OTG_GETDRVDEV (int /*<<< orphan*/ *,struct device*) ; 

__attribute__((used)) static dwc_otg_device_t *dwc_otg_drvdev(struct device *_dev)
{
        dwc_otg_device_t *otg_dev;
        DWC_OTG_GETDRVDEV(otg_dev, _dev);
        return otg_dev;
}