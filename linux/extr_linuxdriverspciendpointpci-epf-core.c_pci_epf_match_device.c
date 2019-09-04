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
struct pci_epf_device_id {scalar_t__* name; } ;
struct pci_epf {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ strcmp (int /*<<< orphan*/ ,scalar_t__*) ; 

const struct pci_epf_device_id *
pci_epf_match_device(const struct pci_epf_device_id *id, struct pci_epf *epf)
{
	if (!id || !epf)
		return NULL;

	while (*id->name) {
		if (strcmp(epf->name, id->name) == 0)
			return id;
		id++;
	}

	return NULL;
}