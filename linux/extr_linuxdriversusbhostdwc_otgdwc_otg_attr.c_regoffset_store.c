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
typedef  int /*<<< orphan*/  uint32_t ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_4__ {int /*<<< orphan*/  reg_offset; } ;
struct TYPE_5__ {TYPE_1__ os_dep; } ;
typedef  TYPE_2__ dwc_otg_device_t ;

/* Variables and functions */
 TYPE_2__* dwc_otg_drvdev (struct device*) ; 
 int /*<<< orphan*/  simple_strtoul (char const*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static ssize_t regoffset_store(struct device *_dev,
			       struct device_attribute *attr,
			       const char *buf, size_t count)
{
        dwc_otg_device_t *otg_dev = dwc_otg_drvdev(_dev);
	uint32_t offset = simple_strtoul(buf, NULL, 16);
#if defined(LM_INTERFACE) || defined(PLATFORM_INTERFACE)
	if (offset < SZ_256K) {
#elif  defined(PCI_INTERFACE)
	if (offset < 0x00040000) {
#endif
		otg_dev->os_dep.reg_offset = offset;
	}