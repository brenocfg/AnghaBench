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
struct ssb_init_invariants {int /*<<< orphan*/  boardinfo; int /*<<< orphan*/  sprom; } ;
struct ssb_bus {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ssb_pci_get_boardinfo (struct ssb_bus*,int /*<<< orphan*/ *) ; 
 int ssb_pci_sprom_get (struct ssb_bus*,int /*<<< orphan*/ *) ; 

int ssb_pci_get_invariants(struct ssb_bus *bus,
			   struct ssb_init_invariants *iv)
{
	int err;

	err = ssb_pci_sprom_get(bus, &iv->sprom);
	if (err)
		goto out;
	ssb_pci_get_boardinfo(bus, &iv->boardinfo);

out:
	return err;
}