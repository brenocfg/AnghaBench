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
struct _pcie_device {int /*<<< orphan*/  list; } ;
struct MPT3SAS_ADAPTER {int /*<<< orphan*/  pcie_device_lock; int /*<<< orphan*/  pcie_device_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pcie_device_get (struct _pcie_device*) ; 
 int /*<<< orphan*/  pcie_device_put (struct _pcie_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void pcie_device_make_active(struct MPT3SAS_ADAPTER *ioc,
		struct _pcie_device *pcie_device)
{
	unsigned long flags;

	spin_lock_irqsave(&ioc->pcie_device_lock, flags);

	if (!list_empty(&pcie_device->list)) {
		list_del_init(&pcie_device->list);
		pcie_device_put(pcie_device);
	}
	pcie_device_get(pcie_device);
	list_add_tail(&pcie_device->list, &ioc->pcie_device_list);

	spin_unlock_irqrestore(&ioc->pcie_device_lock, flags);
}