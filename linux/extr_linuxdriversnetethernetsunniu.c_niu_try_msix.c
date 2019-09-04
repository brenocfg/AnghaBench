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
typedef  int u8 ;
struct pci_dev {int dummy; } ;
struct niu_parent {int num_ports; int* rxchan_per_port; int* txchan_per_port; } ;
struct niu {int port; int num_ldg; TYPE_1__* ldg; int /*<<< orphan*/  flags; struct pci_dev* pdev; struct niu_parent* parent; } ;
struct msix_entry {int entry; scalar_t__ vector; } ;
struct TYPE_2__ {scalar_t__ irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  NIU_FLAGS_MSIX ; 
 int NIU_NUM_LDG ; 
 int pci_enable_msix_range (struct pci_dev*,struct msix_entry*,int,int) ; 

__attribute__((used)) static void niu_try_msix(struct niu *np, u8 *ldg_num_map)
{
	struct msix_entry msi_vec[NIU_NUM_LDG];
	struct niu_parent *parent = np->parent;
	struct pci_dev *pdev = np->pdev;
	int i, num_irqs;
	u8 first_ldg;

	first_ldg = (NIU_NUM_LDG / parent->num_ports) * np->port;
	for (i = 0; i < (NIU_NUM_LDG / parent->num_ports); i++)
		ldg_num_map[i] = first_ldg + i;

	num_irqs = (parent->rxchan_per_port[np->port] +
		    parent->txchan_per_port[np->port] +
		    (np->port == 0 ? 3 : 1));
	BUG_ON(num_irqs > (NIU_NUM_LDG / parent->num_ports));

	for (i = 0; i < num_irqs; i++) {
		msi_vec[i].vector = 0;
		msi_vec[i].entry = i;
	}

	num_irqs = pci_enable_msix_range(pdev, msi_vec, 1, num_irqs);
	if (num_irqs < 0) {
		np->flags &= ~NIU_FLAGS_MSIX;
		return;
	}

	np->flags |= NIU_FLAGS_MSIX;
	for (i = 0; i < num_irqs; i++)
		np->ldg[i].irq = msi_vec[i].vector;
	np->num_ldg = num_irqs;
}