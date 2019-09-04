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
struct pci_device_id {scalar_t__ vendor; scalar_t__ device; } ;
struct ipr_chip_t {scalar_t__ vendor; scalar_t__ device; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct ipr_chip_t const*) ; 
 struct ipr_chip_t const* ipr_chip ; 

__attribute__((used)) static const struct ipr_chip_t *
ipr_get_chip_info(const struct pci_device_id *dev_id)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(ipr_chip); i++)
		if (ipr_chip[i].vendor == dev_id->vendor &&
		    ipr_chip[i].device == dev_id->device)
			return &ipr_chip[i];
	return NULL;
}