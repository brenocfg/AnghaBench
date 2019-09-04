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
struct asd_ha_struct {int /*<<< orphan*/  pcidev; } ;

/* Variables and functions */
 int asd_chip_hardrst (struct asd_ha_struct*) ; 
 int /*<<< orphan*/  asd_disable_ints (struct asd_ha_struct*) ; 
 int asd_init_seqs (struct asd_ha_struct*) ; 
 int /*<<< orphan*/  asd_printk (char*,int /*<<< orphan*/ ) ; 
 int asd_start_seqs (struct asd_ha_struct*) ; 
 int /*<<< orphan*/  pci_name (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int asd_init_chip(struct asd_ha_struct *asd_ha)
{
	int err;

	err = asd_chip_hardrst(asd_ha);
	if (err) {
		asd_printk("couldn't hard reset %s\n",
			    pci_name(asd_ha->pcidev));
		goto out;
	}

	asd_disable_ints(asd_ha);

	err = asd_init_seqs(asd_ha);
	if (err) {
		asd_printk("couldn't init seqs for %s\n",
			   pci_name(asd_ha->pcidev));
		goto out;
	}

	err = asd_start_seqs(asd_ha);
	if (err) {
		asd_printk("couldn't start seqs for %s\n",
			   pci_name(asd_ha->pcidev));
		goto out;
	}
out:
	return err;
}