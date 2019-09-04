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
struct hv_pcibus_device {TYPE_1__* mem_config; int /*<<< orphan*/  hdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  IORESOURCE_BUSY ; 
 int /*<<< orphan*/  PCI_CONFIG_MMIO_LENGTH ; 
 int vmbus_allocate_mmio (TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int hv_allocate_config_window(struct hv_pcibus_device *hbus)
{
	int ret;

	/*
	 * Set up a region of MMIO space to use for accessing configuration
	 * space.
	 */
	ret = vmbus_allocate_mmio(&hbus->mem_config, hbus->hdev, 0, -1,
				  PCI_CONFIG_MMIO_LENGTH, 0x1000, false);
	if (ret)
		return ret;

	/*
	 * vmbus_allocate_mmio() gets used for allocating both device endpoint
	 * resource claims (those which cannot be overlapped) and the ranges
	 * which are valid for the children of this bus, which are intended
	 * to be overlapped by those children.  Set the flag on this claim
	 * meaning that this region can't be overlapped.
	 */

	hbus->mem_config->flags |= IORESOURCE_BUSY;

	return 0;
}