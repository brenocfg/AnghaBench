#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tb_switch {TYPE_2__* tb; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {TYPE_1__* nhi; } ;
struct TYPE_3__ {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 struct pci_dev* pci_find_pcie_root_port (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nvm_authenticate_complete(struct tb_switch *sw)
{
	struct pci_dev *root_port;

	root_port = pci_find_pcie_root_port(sw->tb->nhi->pdev);
	if (root_port)
		pm_runtime_put(&root_port->dev);
}