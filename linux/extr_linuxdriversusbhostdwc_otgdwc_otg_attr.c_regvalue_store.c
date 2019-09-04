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
typedef  int /*<<< orphan*/  uint32_t ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;
struct TYPE_4__ {int reg_offset; scalar_t__ base; } ;
struct TYPE_5__ {TYPE_1__ os_dep; } ;
typedef  TYPE_2__ dwc_otg_device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DWC_WRITE_REG32 (int /*<<< orphan*/  volatile*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 TYPE_2__* dwc_otg_drvdev (struct device*) ; 
 int /*<<< orphan*/  simple_strtoul (char const*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static ssize_t regvalue_store(struct device *_dev,
			      struct device_attribute *attr,
			      const char *buf, size_t count)
{
        dwc_otg_device_t *otg_dev = dwc_otg_drvdev(_dev);
	volatile uint32_t *addr;
	uint32_t val = simple_strtoul(buf, NULL, 16);
	//dev_dbg(_dev, "Offset=0x%08x Val=0x%08x\n", otg_dev->reg_offset, val);
	if (otg_dev->os_dep.reg_offset != 0xFFFFFFFF && 0 != otg_dev->os_dep.base) {
		/* Calculate the address */
		addr = (uint32_t *) (otg_dev->os_dep.reg_offset +
				     (uint8_t *) otg_dev->os_dep.base);
		DWC_WRITE_REG32(addr, val);
	} else {
		dev_err(_dev, "Invalid Register Offset (0x%08x)\n",
			otg_dev->os_dep.reg_offset);
	}
	return count;
}