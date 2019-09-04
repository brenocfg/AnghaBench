#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  driver_attr_irq_handler_state ; 
 int /*<<< orphan*/  driver_attr_irq_handlers ; 
 int /*<<< orphan*/  driver_attr_new_slot ; 
 int /*<<< orphan*/  driver_attr_permissive ; 
 int /*<<< orphan*/  driver_attr_quirks ; 
 int /*<<< orphan*/  driver_attr_remove_slot ; 
 int /*<<< orphan*/  driver_attr_slots ; 
 int /*<<< orphan*/  driver_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_unregister_driver (TYPE_1__*) ; 
 TYPE_1__ xen_pcibk_pci_driver ; 

__attribute__((used)) static void pcistub_exit(void)
{
	driver_remove_file(&xen_pcibk_pci_driver.driver, &driver_attr_new_slot);
	driver_remove_file(&xen_pcibk_pci_driver.driver,
			   &driver_attr_remove_slot);
	driver_remove_file(&xen_pcibk_pci_driver.driver, &driver_attr_slots);
	driver_remove_file(&xen_pcibk_pci_driver.driver, &driver_attr_quirks);
	driver_remove_file(&xen_pcibk_pci_driver.driver,
			   &driver_attr_permissive);
	driver_remove_file(&xen_pcibk_pci_driver.driver,
			   &driver_attr_irq_handlers);
	driver_remove_file(&xen_pcibk_pci_driver.driver,
			   &driver_attr_irq_handler_state);
	pci_unregister_driver(&xen_pcibk_pci_driver);
}