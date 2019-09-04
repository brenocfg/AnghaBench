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
struct platform_device_info {char const* name; int /*<<< orphan*/  dma_mask; int /*<<< orphan*/  id; TYPE_1__* parent; } ;
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
typedef  int /*<<< orphan*/  pdevinfo ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int /*<<< orphan*/  PLATFORM_DEVID_NONE ; 
 int /*<<< orphan*/  memset (struct platform_device_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  of_dma_configure (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 struct platform_device* platform_device_register_full (struct platform_device_info*) ; 

__attribute__((used)) static struct platform_device *
vchiq_register_child(struct platform_device *pdev, const char *name)
{
	struct platform_device_info pdevinfo;
	struct platform_device *new_dev;

	memset(&pdevinfo, 0, sizeof(pdevinfo));

	pdevinfo.parent = &pdev->dev;
	pdevinfo.name = name;
	pdevinfo.id = PLATFORM_DEVID_NONE;
	pdevinfo.dma_mask = DMA_BIT_MASK(32);

	new_dev = platform_device_register_full(&pdevinfo);
	if (!new_dev)
		return NULL;

	/*
	 * We want the dma-ranges etc to be copied from the parent VCHIQ device
	 * to be passed on to the children too.
	 */
	of_dma_configure(&new_dev->dev, pdev->dev.of_node, true);

	return new_dev;
}