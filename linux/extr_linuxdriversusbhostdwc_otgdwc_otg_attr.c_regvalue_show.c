#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_4__ {int reg_offset; scalar_t__ base; } ;
struct TYPE_5__ {TYPE_1__ os_dep; } ;
typedef  TYPE_2__ dwc_otg_device_t ;

/* Variables and functions */
 int DWC_READ_REG32 (int volatile*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 TYPE_2__* dwc_otg_drvdev (struct device*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*) ; 

__attribute__((used)) static ssize_t regvalue_show(struct device *_dev,
			     struct device_attribute *attr, char *buf)
{
        dwc_otg_device_t *otg_dev = dwc_otg_drvdev(_dev);
	uint32_t val;
	volatile uint32_t *addr;

	if (otg_dev->os_dep.reg_offset != 0xFFFFFFFF && 0 != otg_dev->os_dep.base) {
		/* Calculate the address */
		addr = (uint32_t *) (otg_dev->os_dep.reg_offset +
				     (uint8_t *) otg_dev->os_dep.base);
		val = DWC_READ_REG32(addr);
		return snprintf(buf,
				sizeof("Reg@0xFFFFFFFF = 0xFFFFFFFF\n") + 1,
				"Reg@0x%06x = 0x%08x\n", otg_dev->os_dep.reg_offset,
				val);
	} else {
		dev_err(_dev, "Invalid offset (0x%0x)\n", otg_dev->os_dep.reg_offset);
		return sprintf(buf, "invalid offset\n");
	}
}