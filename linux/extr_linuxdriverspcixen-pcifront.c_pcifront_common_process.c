#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct pcifront_device {TYPE_4__* xdev; TYPE_2__* sh_info; } ;
struct pci_driver {TYPE_3__* err_handler; } ;
struct pci_dev {struct pci_driver* driver; } ;
typedef  int /*<<< orphan*/  pci_ers_result_t ;
typedef  int /*<<< orphan*/  pci_channel_state_t ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* resume ) (struct pci_dev*) ;int /*<<< orphan*/  (* slot_reset ) (struct pci_dev*) ;int /*<<< orphan*/  (* mmio_enabled ) (struct pci_dev*) ;int /*<<< orphan*/  (* error_detected ) (struct pci_dev*,int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {int bus; int devfn; int domain; } ;
struct TYPE_6__ {TYPE_1__ aer_op; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_ERS_RESULT_NONE ; 
#define  XEN_PCI_OP_aer_detected 131 
#define  XEN_PCI_OP_aer_mmio 130 
#define  XEN_PCI_OP_aer_resume 129 
#define  XEN_PCI_OP_aer_slotreset 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,int,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  pci_dbg (struct pci_dev*,char*) ; 
 int /*<<< orphan*/  pci_dev_put (struct pci_dev*) ; 
 struct pci_dev* pci_get_domain_bus_and_slot (int,int,int) ; 
 int /*<<< orphan*/  stub1 (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct pci_dev*) ; 
 int /*<<< orphan*/  stub3 (struct pci_dev*) ; 
 int /*<<< orphan*/  stub4 (struct pci_dev*) ; 

__attribute__((used)) static pci_ers_result_t pcifront_common_process(int cmd,
						struct pcifront_device *pdev,
						pci_channel_state_t state)
{
	pci_ers_result_t result;
	struct pci_driver *pdrv;
	int bus = pdev->sh_info->aer_op.bus;
	int devfn = pdev->sh_info->aer_op.devfn;
	int domain = pdev->sh_info->aer_op.domain;
	struct pci_dev *pcidev;
	int flag = 0;

	dev_dbg(&pdev->xdev->dev,
		"pcifront AER process: cmd %x (bus:%x, devfn%x)",
		cmd, bus, devfn);
	result = PCI_ERS_RESULT_NONE;

	pcidev = pci_get_domain_bus_and_slot(domain, bus, devfn);
	if (!pcidev || !pcidev->driver) {
		dev_err(&pdev->xdev->dev, "device or AER driver is NULL\n");
		pci_dev_put(pcidev);
		return result;
	}
	pdrv = pcidev->driver;

	if (pdrv) {
		if (pdrv->err_handler && pdrv->err_handler->error_detected) {
			pci_dbg(pcidev, "trying to call AER service\n");
			if (pcidev) {
				flag = 1;
				switch (cmd) {
				case XEN_PCI_OP_aer_detected:
					result = pdrv->err_handler->
						 error_detected(pcidev, state);
					break;
				case XEN_PCI_OP_aer_mmio:
					result = pdrv->err_handler->
						 mmio_enabled(pcidev);
					break;
				case XEN_PCI_OP_aer_slotreset:
					result = pdrv->err_handler->
						 slot_reset(pcidev);
					break;
				case XEN_PCI_OP_aer_resume:
					pdrv->err_handler->resume(pcidev);
					break;
				default:
					dev_err(&pdev->xdev->dev,
						"bad request in aer recovery "
						"operation!\n");

				}
			}
		}
	}
	if (!flag)
		result = PCI_ERS_RESULT_NONE;

	return result;
}