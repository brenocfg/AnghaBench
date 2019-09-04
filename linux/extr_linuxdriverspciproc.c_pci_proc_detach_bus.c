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
struct pci_bus {int /*<<< orphan*/  procdir; } ;

/* Variables and functions */
 int /*<<< orphan*/  proc_remove (int /*<<< orphan*/ ) ; 

int pci_proc_detach_bus(struct pci_bus *bus)
{
	proc_remove(bus->procdir);
	return 0;
}