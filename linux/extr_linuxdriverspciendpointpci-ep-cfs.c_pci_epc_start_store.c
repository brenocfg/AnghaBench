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
struct pci_epc_group {int start; struct pci_epc* epc; } ;
struct pci_epc {int /*<<< orphan*/  dev; } ;
struct config_item {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int kstrtobool (char const*,int*) ; 
 int pci_epc_start (struct pci_epc*) ; 
 int /*<<< orphan*/  pci_epc_stop (struct pci_epc*) ; 
 struct pci_epc_group* to_pci_epc_group (struct config_item*) ; 

__attribute__((used)) static ssize_t pci_epc_start_store(struct config_item *item, const char *page,
				   size_t len)
{
	int ret;
	bool start;
	struct pci_epc *epc;
	struct pci_epc_group *epc_group = to_pci_epc_group(item);

	epc = epc_group->epc;

	ret = kstrtobool(page, &start);
	if (ret)
		return ret;

	if (!start) {
		pci_epc_stop(epc);
		return len;
	}

	ret = pci_epc_start(epc);
	if (ret) {
		dev_err(&epc->dev, "failed to start endpoint controller\n");
		return -EINVAL;
	}

	epc_group->start = start;

	return len;
}