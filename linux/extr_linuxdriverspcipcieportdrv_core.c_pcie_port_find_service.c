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
typedef  int /*<<< orphan*/  u32 ;
struct portdrv_service_data {struct pcie_port_service_driver* drv; int /*<<< orphan*/  service; } ;
struct pcie_port_service_driver {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_for_each_child (int /*<<< orphan*/ *,struct portdrv_service_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  find_service_iter ; 

struct pcie_port_service_driver *pcie_port_find_service(struct pci_dev *dev,
							u32 service)
{
	struct pcie_port_service_driver *drv;
	struct portdrv_service_data pdrvs;

	pdrvs.drv = NULL;
	pdrvs.service = service;
	device_for_each_child(&dev->dev, &pdrvs, find_service_iter);

	drv = pdrvs.drv;
	return drv;
}