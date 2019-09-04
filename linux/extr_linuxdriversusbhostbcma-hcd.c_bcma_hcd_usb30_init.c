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
struct device {int /*<<< orphan*/  of_node; } ;
struct bcma_hcd_device {struct bcma_device* core; } ;
struct bcma_device {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  bcma_core_enable (struct bcma_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_platform_default_populate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct device*) ; 

__attribute__((used)) static int bcma_hcd_usb30_init(struct bcma_hcd_device *bcma_hcd)
{
	struct bcma_device *core = bcma_hcd->core;
	struct device *dev = &core->dev;

	bcma_core_enable(core, 0);

	of_platform_default_populate(dev->of_node, NULL, dev);

	return 0;
}