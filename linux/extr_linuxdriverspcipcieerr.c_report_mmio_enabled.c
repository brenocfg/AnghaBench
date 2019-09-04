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
struct pci_error_handlers {int /*<<< orphan*/  (* mmio_enabled ) (struct pci_dev*) ;} ;
struct pci_dev {int /*<<< orphan*/  dev; TYPE_1__* driver; } ;
struct aer_broadcast_data {int /*<<< orphan*/  result; } ;
typedef  int /*<<< orphan*/  pci_ers_result_t ;
struct TYPE_2__ {struct pci_error_handlers* err_handler; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  merge_result (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct pci_dev*) ; 

__attribute__((used)) static int report_mmio_enabled(struct pci_dev *dev, void *data)
{
	pci_ers_result_t vote;
	const struct pci_error_handlers *err_handler;
	struct aer_broadcast_data *result_data;

	result_data = (struct aer_broadcast_data *) data;

	device_lock(&dev->dev);
	if (!dev->driver ||
		!dev->driver->err_handler ||
		!dev->driver->err_handler->mmio_enabled)
		goto out;

	err_handler = dev->driver->err_handler;
	vote = err_handler->mmio_enabled(dev);
	result_data->result = merge_result(result_data->result, vote);
out:
	device_unlock(&dev->dev);
	return 0;
}