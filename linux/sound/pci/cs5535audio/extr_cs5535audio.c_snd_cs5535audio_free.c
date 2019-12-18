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
struct cs5535audio {scalar_t__ irq; int /*<<< orphan*/  pci; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_D3hot ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct cs5535audio*) ; 
 int /*<<< orphan*/  kfree (struct cs5535audio*) ; 
 int /*<<< orphan*/  pci_disable_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_regions (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_power_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  synchronize_irq (scalar_t__) ; 

__attribute__((used)) static int snd_cs5535audio_free(struct cs5535audio *cs5535au)
{
	synchronize_irq(cs5535au->irq);
	pci_set_power_state(cs5535au->pci, PCI_D3hot);

	if (cs5535au->irq >= 0)
		free_irq(cs5535au->irq, cs5535au);

	pci_release_regions(cs5535au->pci);
	pci_disable_device(cs5535au->pci);
	kfree(cs5535au);
	return 0;
}