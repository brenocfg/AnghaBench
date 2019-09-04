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
struct iproc_msi {int /*<<< orphan*/  inner_domain; int /*<<< orphan*/  msi_domain; int /*<<< orphan*/  nr_msi_vecs; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  iproc_msi_domain_info ; 
 int /*<<< orphan*/  irq_domain_add_linear (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct iproc_msi*) ; 
 int /*<<< orphan*/  irq_domain_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msi_domain_ops ; 
 int /*<<< orphan*/  of_node_to_fwnode (struct device_node*) ; 
 int /*<<< orphan*/  pci_msi_create_irq_domain (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iproc_msi_alloc_domains(struct device_node *node,
				   struct iproc_msi *msi)
{
	msi->inner_domain = irq_domain_add_linear(NULL, msi->nr_msi_vecs,
						  &msi_domain_ops, msi);
	if (!msi->inner_domain)
		return -ENOMEM;

	msi->msi_domain = pci_msi_create_irq_domain(of_node_to_fwnode(node),
						    &iproc_msi_domain_info,
						    msi->inner_domain);
	if (!msi->msi_domain) {
		irq_domain_remove(msi->inner_domain);
		return -ENOMEM;
	}

	return 0;
}