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
struct pci_saved_state {int dummy; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct pci_saved_state*) ; 
 int pci_load_saved_state (struct pci_dev*,struct pci_saved_state*) ; 

int pci_load_and_free_saved_state(struct pci_dev *dev,
				  struct pci_saved_state **state)
{
	int ret = pci_load_saved_state(dev, *state);
	kfree(*state);
	*state = NULL;
	return ret;
}