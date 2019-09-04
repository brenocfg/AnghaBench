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
typedef  int /*<<< orphan*/  u16 ;
struct pci_dev {TYPE_1__* bus; } ;
struct TYPE_2__ {struct pci_dev* self; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_acs_enabled (struct pci_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ pci_is_root_bus (TYPE_1__*) ; 

bool pci_acs_path_enabled(struct pci_dev *start,
			  struct pci_dev *end, u16 acs_flags)
{
	struct pci_dev *pdev, *parent = start;

	do {
		pdev = parent;

		if (!pci_acs_enabled(pdev, acs_flags))
			return false;

		if (pci_is_root_bus(pdev->bus))
			return (end == NULL);

		parent = pdev->bus->self;
	} while (pdev != end);

	return true;
}