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
struct TYPE_2__ {int /*<<< orphan*/  work; } ;
struct pci_epf_test {int linkup_notifier; int msix_available; TYPE_1__ cmd_handler; int /*<<< orphan*/  test_reg_bar; } ;
struct pci_epf_header {int dummy; } ;
struct device {int dummy; } ;
struct pci_epf {int /*<<< orphan*/  msix_interrupts; int /*<<< orphan*/  func_no; int /*<<< orphan*/  msi_interrupts; struct device dev; struct pci_epc* epc; struct pci_epf_header* header; } ;
struct pci_epc {int features; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  EPC_FEATURE_GET_BAR (int) ; 
 int EPC_FEATURE_MSIX_AVAILABLE ; 
 int EPC_FEATURE_NO_LINKUP_NOTIFIER ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct pci_epf_test* epf_get_drvdata (struct pci_epf*) ; 
 int /*<<< orphan*/  kpcitest_workqueue ; 
 int pci_epc_set_msi (struct pci_epc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pci_epc_set_msix (struct pci_epc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pci_epc_write_header (struct pci_epc*,int /*<<< orphan*/ ,struct pci_epf_header*) ; 
 int pci_epf_test_alloc_space (struct pci_epf*) ; 
 int pci_epf_test_set_bar (struct pci_epf*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pci_epf_test_bind(struct pci_epf *epf)
{
	int ret;
	struct pci_epf_test *epf_test = epf_get_drvdata(epf);
	struct pci_epf_header *header = epf->header;
	struct pci_epc *epc = epf->epc;
	struct device *dev = &epf->dev;

	if (WARN_ON_ONCE(!epc))
		return -EINVAL;

	if (epc->features & EPC_FEATURE_NO_LINKUP_NOTIFIER)
		epf_test->linkup_notifier = false;
	else
		epf_test->linkup_notifier = true;

	epf_test->msix_available = epc->features & EPC_FEATURE_MSIX_AVAILABLE;

	epf_test->test_reg_bar = EPC_FEATURE_GET_BAR(epc->features);

	ret = pci_epc_write_header(epc, epf->func_no, header);
	if (ret) {
		dev_err(dev, "Configuration header write failed\n");
		return ret;
	}

	ret = pci_epf_test_alloc_space(epf);
	if (ret)
		return ret;

	ret = pci_epf_test_set_bar(epf);
	if (ret)
		return ret;

	ret = pci_epc_set_msi(epc, epf->func_no, epf->msi_interrupts);
	if (ret) {
		dev_err(dev, "MSI configuration failed\n");
		return ret;
	}

	if (epf_test->msix_available) {
		ret = pci_epc_set_msix(epc, epf->func_no, epf->msix_interrupts);
		if (ret) {
			dev_err(dev, "MSI-X configuration failed\n");
			return ret;
		}
	}

	if (!epf_test->linkup_notifier)
		queue_work(kpcitest_workqueue, &epf_test->cmd_handler.work);

	return 0;
}