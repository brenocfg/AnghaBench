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
struct pnv_php_slot {int /*<<< orphan*/  dn; int /*<<< orphan*/  bus; } ;
struct pci_controller {int dummy; } ;

/* Variables and functions */
 struct pci_controller* pci_bus_to_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_traverse_device_nodes (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pci_controller*) ; 
 int /*<<< orphan*/  pnv_php_add_one_pdn ; 

__attribute__((used)) static void pnv_php_add_pdns(struct pnv_php_slot *slot)
{
	struct pci_controller *hose = pci_bus_to_host(slot->bus);

	pci_traverse_device_nodes(slot->dn, pnv_php_add_one_pdn, hose);
}