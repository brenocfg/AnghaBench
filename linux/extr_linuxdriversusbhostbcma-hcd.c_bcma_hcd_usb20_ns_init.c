#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct device {int /*<<< orphan*/  of_node; } ;
struct bcma_hcd_device {struct bcma_device* core; } ;
struct bcma_device {struct device dev; TYPE_1__* bus; } ;
struct bcma_chipinfo {scalar_t__ id; } ;
struct TYPE_2__ {struct bcma_chipinfo chipinfo; } ;

/* Variables and functions */
 scalar_t__ BCMA_CHIP_ID_BCM4707 ; 
 scalar_t__ BCMA_CHIP_ID_BCM53018 ; 
 int /*<<< orphan*/  bcma_core_enable (struct bcma_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcma_hcd_usb20_ns_init_hc (struct bcma_device*) ; 
 int /*<<< orphan*/  of_platform_default_populate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct device*) ; 

__attribute__((used)) static int bcma_hcd_usb20_ns_init(struct bcma_hcd_device *bcma_hcd)
{
	struct bcma_device *core = bcma_hcd->core;
	struct bcma_chipinfo *ci = &core->bus->chipinfo;
	struct device *dev = &core->dev;

	bcma_core_enable(core, 0);

	if (ci->id == BCMA_CHIP_ID_BCM4707 ||
	    ci->id == BCMA_CHIP_ID_BCM53018)
		bcma_hcd_usb20_ns_init_hc(core);

	of_platform_default_populate(dev->of_node, NULL, dev);

	return 0;
}