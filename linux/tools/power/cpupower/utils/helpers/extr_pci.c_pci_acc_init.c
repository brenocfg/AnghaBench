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
struct pci_filter {int domain; int bus; int slot; int func; int vendor; int device; } ;
struct pci_dev {struct pci_dev* next; } ;
struct pci_access {struct pci_dev* devices; } ;

/* Variables and functions */
 struct pci_access* pci_alloc () ; 
 int /*<<< orphan*/  pci_cleanup (struct pci_access*) ; 
 int /*<<< orphan*/  pci_filter_init (struct pci_access*,struct pci_filter*) ; 
 scalar_t__ pci_filter_match (struct pci_filter*,struct pci_dev*) ; 
 int /*<<< orphan*/  pci_init (struct pci_access*) ; 
 int /*<<< orphan*/  pci_scan_bus (struct pci_access*) ; 

struct pci_dev *pci_acc_init(struct pci_access **pacc, int domain, int bus,
			     int slot, int func, int vendor, int dev)
{
	struct pci_filter filter_nb_link;
	struct pci_dev *device;

	*pacc = pci_alloc();
	if (*pacc == NULL)
		return NULL;

	pci_filter_init(*pacc, &filter_nb_link);
	filter_nb_link.domain	= domain;
	filter_nb_link.bus	= bus;
	filter_nb_link.slot	= slot;
	filter_nb_link.func	= func;
	filter_nb_link.vendor	= vendor;
	filter_nb_link.device	= dev;

	pci_init(*pacc);
	pci_scan_bus(*pacc);

	for (device = (*pacc)->devices; device; device = device->next) {
		if (pci_filter_match(&filter_nb_link, device))
			return device;
	}
	pci_cleanup(*pacc);
	return NULL;
}